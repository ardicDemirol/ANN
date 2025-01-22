#include "Process.h"
#include <vector>

class MultiLayerPerceptron {

private:
	int inputSize, hiddenSize, outputSize;
	double learningRate;
	std::vector<std::vector<double>> weightsInputHidden;
	std::vector<std::vector<double>> weightsHiddenOutput;
	std::vector<double> hiddenLayer;
	std::vector<double> outputLayer;

	static double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
	static double sigmoidDerivative(double x) { return x * (1.0 - x); }
	static double randomWeight() { return ((double)rand() / RAND_MAX) * 2 - 1; }

public:
	MultiLayerPerceptron(int inputSize, int hiddenSize, int outputSize, double learningRate) {
		this->inputSize = inputSize;
		this->hiddenSize = hiddenSize;
		this->outputSize = outputSize;
		this->learningRate = learningRate;

		srand(static_cast<unsigned>(time(0)));

		// giriþ ve gizli katman arasýnda rastgele aðýrlýklar oluþturur.
		weightsInputHidden.resize(inputSize, std::vector<double>(hiddenSize));
		for (int i = 0; i < inputSize; ++i)
			for (int j = 0; j < hiddenSize; ++j)
				weightsInputHidden[i][j] = randomWeight();

		// gizli katman ve çýkýþ arasýnda rastgele aððýrlýklar oluþturur.
		weightsHiddenOutput.resize(hiddenSize, std::vector<double>(outputSize));
		for (int i = 0; i < hiddenSize; ++i)
			for (int j = 0; j < outputSize; ++j)
				weightsHiddenOutput[i][j] = randomWeight();
	}


	std::vector<double> forward(const Samples& sample) {
		// I ->  Gizli katmandaki her bir nöronun aktivasyon deðerini hesaplar
		hiddenLayer.resize(hiddenSize);
		for (int j = 0; j < hiddenSize; ++j) {
			hiddenLayer[j] = 0.0;
			for (int i = 0; i < inputSize; ++i)
				hiddenLayer[j] += (i == 0 ? sample.x1 : sample.x2) * weightsInputHidden[i][j];
			hiddenLayer[j] = sigmoid(hiddenLayer[j]);
		}

		// II -> Çýkýþ katmanýndaki her bir nöronun aktivasyon deðerini hesaplamak.
		outputLayer.resize(outputSize);
		for (int k = 0; k < outputSize; ++k) {
			outputLayer[k] = 0.0;
			for (int j = 0; j < hiddenSize; ++j)
				outputLayer[k] += hiddenLayer[j] * weightsHiddenOutput[j][k];
			outputLayer[k] = sigmoid(outputLayer[k]);
		}

		return outputLayer;
	}

	void backward(const Samples& sample, const std::vector<double>& target) {
		// Çýkýþ katmanýndaki her bir nöronun hatasýný hesaplar.
		std::vector<double> outputError(outputSize);
		for (int k = 0; k < outputSize; ++k)
			outputError[k] = (target[k] - outputLayer[k]) * sigmoidDerivative(outputLayer[k]);


		// III -> Çýkýþ katmanýndan gelen hatalarý kullanarak gizli katman hatalarýný hesaplar.
		std::vector<double> hiddenError(hiddenSize);
		for (int j = 0; j < hiddenSize; ++j) {
			hiddenError[j] = 0.0;
			for (int k = 0; k < outputSize; ++k)
				hiddenError[j] += outputError[k] * weightsHiddenOutput[j][k];
			hiddenError[j] *= sigmoidDerivative(hiddenLayer[j]);  // hiddenError[j], her gizli nöronun hatasýný temsil eder.
		}



		//  Gizli katmandan çýkýþ katmanýna olan baðlantýlarýn aðýrlýklarýný günceller.
		for (int j = 0; j < hiddenSize; ++j)
			for (int k = 0; k < outputSize; ++k)
				weightsHiddenOutput[j][k] += learningRate * outputError[k] * hiddenLayer[j];

		
		// Giriþ katmanýndan gizli katmana olan baðlantýlarýn aðýrlýklarýný günceller.
		for (int j = 0; j < hiddenSize; ++j) {
			weightsInputHidden[0][j] += learningRate * hiddenError[j] * sample.x1;
			weightsInputHidden[1][j] += learningRate * hiddenError[j] * sample.x2;
		}
	}


	void train(const std::vector<Samples>& samples, const std::vector<std::vector<double>>& targets, int epochs) {
		for (int epoch = 0; epoch < epochs; ++epoch) {
			double totalError = 0.0;
			for (size_t i = 0; i < samples.size(); ++i) {
				std::vector<double> output = forward(samples[i]);

				for (size_t k = 0; k < targets[i].size(); ++k)
					totalError += 0.5 * std::pow(targets[i][k] - output[k], 2);

				if (totalError < 0.1) break;

				backward(samples[i], targets[i]);
			}

			if (epoch % 100 == 0 || epoch == epochs - 1)
				std::cout << "Epoch " << epoch << ", Total Error: " << totalError << std::endl;
		}
	}
};