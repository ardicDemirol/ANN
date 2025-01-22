#include "Process.h"
#include <vector>
#include <cmath>

double YPoint(int x, double* w, int multiplier)
{
	if (w[1] == 0) w[1] = 0.001;
	return ((double)(-1 * (double)multiplier * w[2] - w[0] * x) / (double)(w[1]));
}

double sigmoid(double net) // 0 - 1 
{
	return 1.0 / (1.0 + exp(-net));
}

double sigmoidDerivative(double net)
{
	return sigmoid(net) * (1 - sigmoid(net));
}

double thresholdOut(double out)
{
	return out > 0.5 ? 1 : 0;
}

double getError(double target, double result) 
{
	return target - result;
}


double getErrorDelta(double target, double result)
{
	return (0.5 * pow(target - result, 2));
}

double getY(double* weight, double x1, double x2)
{
	return (weight[0] * x1) + (weight[1] * x2) + weight[2];
}


void updateWeights(double* weights, double x1, double x2, double delta, double learning_rate)
{
	weights[0] += (learning_rate * delta * x1);
	weights[1] += (learning_rate * delta * x2);
	weights[2] += (learning_rate * delta);
}



void normalizeData(Samples* data, int size)
{
	double sum_x1 = 0.0, sum_x2 = 0.0;

	for (int i = 0; i < size; i++) {
		sum_x1 += data[i].x1;
		sum_x2 += data[i].x2;
	}
	double mean_x1 = sum_x1 / size;
	double mean_x2 = sum_x2 / size;

	double sum_square_x1 = 0.0, sum_square_x2 = 0.0;
	for (int i = 0; i < size; i++) {
		sum_square_x1 += pow(data[i].x1 - mean_x1, 2);
		sum_square_x2 += pow(data[i].x2 - mean_x2, 2);
	}
	double std_x1 = sqrt(sum_square_x1 / size);
	double std_x2 = sqrt(sum_square_x2 / size);

	for (int i = 0; i < size; i++) {
		data[i].x1 = (data[i].x1 - mean_x1) / std_x1;
		data[i].x2 = (data[i].x2 - mean_x2) / std_x2;
	}

}



void shuffleData(Samples* data, int size) {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(data, data + size, g);
}
