#include "head.h"
#include "data.h"
#include "net.h"

void train(){

	for (int iter = 0; iter <= MAX_ITER; ++iter){
		

	}
}

int main(){
	double **X;
	vector<Layer> layers;


	if (!readTrain(X)) return 1;
	if (!readNet(layers)) return 1;
	buildNet(layers);

	train();

	release(X);
	release(layers);
	return 0;
}
