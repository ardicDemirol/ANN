#include <math.h>
#include "Resource.h"
#include <iostream>
#include <map>
#include <utility>
#include <algorithm> 
#include <random>    

#define EULER 2.71828182845904523536

double YPoint(int x, double* w, int multiplier = 1);
double sigmoid(double net);
double thresholdOut(double out);
double getY(double* weight, double x1, double x2);

double getError(double target, double result);
double getErrorDelta(double target, double result);
double sigmoidDerivative(double net);


void updateWeights(double* weights, double x1, double x2, double delta, double learning_rate);
void normalizeData(Samples* data, int size);
void shuffleData(Samples* data, int size);
