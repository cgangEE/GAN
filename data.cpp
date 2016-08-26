#include "data.h"

void loadZ(double *z){

}

double *loadZ(){
	double *ret = (double *)malloc(sizeof(double)*N*N);
	for (int i=0; i<N*N; ++i)
		ret[i] = rand()%256;
	return ret;
}

double *loadX(double **X, int idx){
	return X[idx];
}

void strToDouble(char *buf, double *x){
	int len = strlen(buf);
	int num = 0;
	int idx = 0;
	bool first = true;

	while (len>0 && buf[len]<20) --len;

	for (int i=0; i<=len; ++i)
		if (i == len || buf[i] == ','){
			if (first){
				first = false;
				num = 0;
				continue;
			}
			x[idx++] = num;
			num = 0;
		}
		else if (isdigit(buf[i]))
			num = num * 10 + buf[i] - '0';
}

bool readTrain(double ** &X){
	const char *fileName = "train.csv";
	FILE *fTrain = fopen(fileName, "r");
	if (fTrain == NULL){
		fprintf(stderr, "open file<%s> failed\n", fileName);
		return false;
	}

	char *buf = (char *) malloc(sizeof(char) * BUF_SIZE);
	X = (double **) malloc(sizeof(double*) * M);

	fgets(buf, BUF_SIZE,  fTrain);
	for (int i=0; i<M; ++i){
		fgets(buf, BUF_SIZE,  fTrain);
		X[i] = (double *) malloc(sizeof(double) * N * N);
		strToDouble(buf, X[i]);
	}
	return true;
}

void release(double **X){
	for (int i=0; i<M; ++i)
		if (X[i] != NULL)
			free(X[i]);
	if (X!=NULL) 
		free(X);
}

