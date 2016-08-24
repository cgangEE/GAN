#ifndef _NET_H_
#define _NET_H_

#include "head.h"

struct Layer{
	string name;	
	string type;
	vector<string> bottom;
	string top;
};

string getBufValue(char *buf, const char *key);
bool readNet(vector<Layer> &layers);
void buildNet(vector<Layer> &layers);

#endif
