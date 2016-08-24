#include "head.h"
#include "data.h"
#include "net.h"

void train(){
}

int main(){
	double **X;
	vector<Layer> layers;

	if (!readTrain(X)) return 1;
	if (!readNet(layers)) return 1;
	buildNet(layers);

	train();

	release(X);
	return 0;
}
