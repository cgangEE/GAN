#include "net.h"

string getBufValue(char *buf, const char *key){
	buf = strchr(buf, ':');
	return string(buf+1);
}

vector<int> strToInt(string dim){
	vector<int> ret;
	int num = 0;
	for (int i=0; i<=dim.size(); ++i){
		if (i == dim.size() || dim[i] == ','){
			ret.push_back(num);
			num = 0;
		}
		else if (isdigit(dim[i]))
			num = num * 10 + dim[i] - '0';
	}
	return ret;
}

bool readNet(vector<Layer> &layers){
	const char *fileName = "net.prototxt";
	FILE *fNet = fopen(fileName, "r");
	if (fNet == NULL){
		fprintf(stderr, "open file<%s> failed!\n", fileName);
		return false;
	}

	char *buf = (char *)malloc(sizeof(char) * BUF_SIZE);
	while (fgets(buf, BUF_SIZE, fNet) != NULL){
		int len = strlen(buf);
		while (len>0 && buf[len]<20) buf[len--] = 0;
		if (strchr(buf, '{') != NULL)
			layers.push_back(Layer());
		else if (strstr(buf, "name") != NULL)
			layers.back().name = getBufValue(buf, "name");
		else if (strstr(buf, "type") != NULL)
			layers.back().type = getBufValue(buf, "type");
		else if (strstr(buf, "bottom") != NULL)
			layers.back().bottom.push_back(getBufValue(buf, "bottom"));
		else if (strstr(buf, "top") != NULL)
			layers.back().top = getBufValue(buf, "top");

		else if (strstr(buf, "dim") != NULL){
			layers.back().dim= strToInt(getBufValue(buf, "dim"));
		}
		else if (strstr(buf, "kernel_size") != NULL){
			layers.back().kernel_size = 
				strToInt(getBufValue(buf, "kernel_size"))[0];
		} 
		else if (strstr(buf, "num_output") != NULL){
			layers.back().num_output = 
				strToInt(getBufValue(buf, "num_output"))[0];
		} 
	}

	return true;
}


void buildNet(vector<Layer> &layers){
	for (int i=0; i<layers.size(); ++i){
		vector<int> &dim = layers[i].dim;

		if (layers[i].type == "data"){
			layers[i].topBlob = (double *) 
				malloc(sizeof(double) * dim[0] * dim[1] * dim[2]);

		} else if (layers[i].type == "convolution") {

			for (int k=0; k<layers[i].bottom.size(); ++k)
				for (int j=0; j<i; ++j)
					if (layers[i].bottom[k] == layers[j].name){
						layers[i].bottomId.push_back(j);
						layers[j].topId = i;
					}
			
			layers[i].layer = (double *)
				malloc(sizeof(double) * layers[i].num_output *
						layers[i].kernel_size * layers[i].kernel_size);

			int k = layers[i].bottomId[0];

			layers[i].dim.push_back(layers[i].num_output);
			layers[i].dim.push_back(layers[k].dim[1]);
			layers[i].dim.push_back(layers[k].dim[2]);

			layers[i].topBlob = (double *)
				malloc(sizeof(double) * layers[i].num_output 
						* layers[k].dim[1] * layers[k].dim[2]);
		}
	}
}

void release(vector<Layer> &layers){
	for (int i=0; i<layers.size(); ++i){
		if (layers[i].layer != NULL)
			free(layers[i].layer);
		if (layers[i].topBlob != NULL)
			free(layers[i].topBlob);
	}
}
