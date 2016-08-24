#include "net.h"

string getBufValue(char *buf, const char *key){
	buf = strchr(buf, ':');
	return string(buf+1);
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
		if (strchr(buf, '{') != NULL){
			layers.push_back(Layer());
		} else if (strstr(buf, "name") != NULL){
			layers.back().name = getBufValue(buf, "name");
		} else if (strstr(buf, "type") != NULL){
			layers.back().type = getBufValue(buf, "type");
		} else if (strstr(buf, "bottom") != NULL){
			layers.back().bottom.push_back(getBufValue(buf, "bottom"));
		} else if (strstr(buf, "top") != NULL){
			layers.back().top = getBufValue(buf, "top");
		}
	}

	return true;
}


void buildNet(vector<Layer> &layers){
	for (int i=0; i<layers.size(); ++i){
		if (layers[i].type == "data"){
			
		} else if (layers[i].type == "convolution") {
		}
	}
}

