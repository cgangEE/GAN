#ifndef _NET_H_
#define _NET_H_

#include "head.h"

struct Layer{
	string name;	
	string type;
	vector<string> bottom;
	string top;
	vector<int> dim;
	int kernel_size;
	int num_output;

	vector<int> bottomId;
	int topId;

	double *layer;
	double *topBlob;
};


string getBufValue(char *buf, const char *key);
bool readNet(vector<Layer> &layers);
void buildNet(vector<Layer> &layers);
void release(vector<Layer> &layers);

#endif
