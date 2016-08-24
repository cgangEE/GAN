#ifndef _DATA_H_
#define _DATA_H_
#include "head.h"

void strToDouble(char *buf, double *x);

double *loadZ();
double *loadX(double **X, int idx);

bool readTrain(double ** &X);
void release(double **X);
#endif
