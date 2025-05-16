# Single and Multi-Layer Artificial Neural Networks

Single and multi-layer artificial neural networks are mathematical models designed to process input data and produce a specific output. Single-layer networks are suitable for basic problems, while multi-layer networks are used for more complex tasks.

## Single Neuron Model

An artificial neuron is a mathematical model that mimics the working principle of a biological neuron. A single neuron receives input values, multiplies them by weights, and passes the result through an activation function to produce an output.

### Inputs

- **Inputs**: x₁, x₂, ..., xₙ
- **Weights**: Each input xᵢ is multiplied by a weight wᵢ.
- **Weighted Sum (Net Input)**: The net input is the sum of all weighted inputs:

```
z = Σ(wᵢ * xᵢ) + b
```

Here, b is the bias term.

### Activation Function

The output is calculated by applying the activation function to the value of z:

```
y = f(z)
```

Activation functions can be linear or non-linear:
- **Linear**: f(z) = z
- **Sigmoid**: f(z) = 1 / (1 + e⁻ᶻ)
- **Step Function**: f(z) = 1, z ≥ 0; otherwise f(z) = 0.

### Codes for Two Classes Single Layer
#### Perceptron Rule

```c++
void binaryToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
{
	drawRandomWeights();
	int iteration = 0;

	while (iteration < maxEpoch)
	{
		iteration++;
		allCorrect = true;

		for (int i = 0; i < size; i++)
		{
			double y = getY(w, p[i].x1, p[i].x2);
			double out = thresholdOut(y);

			double error = getError(p[i].id, out);

			if (fabs(error) >= 1e-6)
			{
				allCorrect = false;
				updateWeights(w, p[i].x1, p[i].x2, error, learningRate);
			}
		}

		if (allCorrect) {
			MessageBox::Show("Learning Completed Successfully");
			drawLine(Color::Red, w, 1, 2);
			break;
		}
	}

	if (iteration >= maxEpoch) {
		MessageBox::Show("Maximum number of epochs reached!");
		isClassSelectionValid();
	}
}
```

![1](https://github.com/user-attachments/assets/c18f0f5d-ae3e-497d-aa65-de90b6e0f2ea)

#### Delta Rule

```c++
void continuouslyToolStripMenuItem1_Click(Object^ sender, EventArgs^ e) {
	double** w = initializeWeights(classSize);
	double* delta = new double[classSize];

	normalizeData(p, size);
	shuffle_data(p, size);
	drawNormalizedPoints(p);

	int iteration = 0;
	bool allCorrect = false;
	double threshold = 0.01;

	while (iteration < maxEpoch) {
		iteration++;
		double sumError = 0;

		for (int i = 0; i < size; i++) {
			for (int c = 0; c < classSize; c++) {
				int target = (p[i].id == c) ? 1 : 0;

				double _net = getY(w[c], p[i].x1, p[i].x2);
				double fnet = sigmoid(_net);

				delta[c] = (target - fnet) * sigmoidDerivative(_net);

				updateWeights(w[c], p[i].x1, p[i].x2, delta[c], learningRate);

				sumError += pow(target - fnet, 2);
			}
		}

		sumError /= (size * classSize);

		if (sumError < threshold) {
			allCorrect = true;
			break;
		}
	}

	if (allCorrect) {
		MessageBox::Show("Learning Completed Successfully");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], normalizeDrawMultiplier, 2);
	}
	else MessageBox::Show("Maximum number of epochs reached!");

	for (int c = 0; c < classSize; c++) {
		if (w[c] != nullptr) {
			delete[] w[c];
			w[c] = nullptr;
		}
	}
	delete[] w;
	delete[] delta;
}
```

![2](https://github.com/user-attachments/assets/846d4d85-6a40-4c48-892f-fd3cff998daf)

---

## Multi Neuron Model

A multi-neuron model is a structure where multiple neurons operate in the same layer. Each neuron processes the input data independently and usually produces an output for a different class or value.

### Inputs and Outputs

- **Inputs**: x₁, x₂, ..., xₙ are common inputs for all neurons.
- **Outputs**: Each neuron produces an output depending on its weights and activation function:

```
yⱼ = fⱼ(Σ(wⱼᵢ * xᵢ) + bⱼ)
```

Here:
- j: Index of the neuron.
- wⱼᵢ: Weight of the j-th neuron for the i-th input.
- bⱼ: Bias term of the j-th neuron.
- fⱼ: Activation function of the j-th neuron.

### Learning Process

In the multi-neuron model, the weights of each neuron are learned independently. Typically, the "One-vs-All" (OvA) approach is used:
- Each neuron tries to distinguish one class from the others.
- The error function is calculated and minimized separately for each neuron.

### Application Areas

- **Multi-Class Classification**: Structures that can distinguish more than one class.
- **Nonlinear Regression**: Systems that can produce complex outputs.

### Codes for Multi Classes Single Layer
#### Perceptron Rule

```c++
void binaryToolStripMenuItem1_Click(Object^ sender, EventArgs^ e) {
	int iteration = 0;
	double** w = initializeWeights(classSize);

	bool allCorrect = false;
	while (!allCorrect && iteration < maxEpoch) {
		iteration++;
		allCorrect = true;

		for (int i = 0; i < size; i++) {
			int actual_class = p[i].id;

			for (int c = 0; c < classSize; c++) {
				double out = sigmoid(getY(w[c], p[i].x1, p[i].x2));
				int target = (actual_class == c) ? 1 : 0;
				double error = target - out;

				if (fabs(error) > 0.0001) {
					allCorrect = false;
					updateWeights(w[c], p[i].x1, p[i].x2, error, learningRate);
				}
			}
		}
	}

	if (allCorrect) {
		MessageBox::Show("Learning Completed Successfully");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], 1, 2);
	}
	else MessageBox::Show("Maximum number of epochs reached!");

	for (int i = 0; i < classSize; i++) delete[] w[i];

	delete[] w;
}
```

![3](https://github.com/user-attachments/assets/8366285b-d02c-45c7-a481-d9cc96418494)

#### Delta Rule

```c++
void continuouslyToolStripMenuItem1_Click(Object^ sender, EventArgs^ e) {
	double** w = initializeWeights(classSize);
	double* delta = new double[classSize];

	normalizeData(p, size);
	shuffle_data(p, size);
	drawNormalizedPoints(p);

	int iteration = 0;
	bool allCorrect = false;
	double threshold = 0.01;

	while (iteration < maxEpoch) {
		iteration++;
		double sumError = 0;

		for (int i = 0; i < size; i++) {
			for (int c = 0; c < classSize; c++) {
				int target = (p[i].id == c) ? 1 : 0;

				double _net = getY(w[c], p[i].x1, p[i].x2);
				double fnet = sigmoid(_net);

				delta[c] = (target - fnet) * sigmoidDerivative(_net);

				updateWeights(w[c], p[i].x1, p[i].x2, delta[c], learningRate);

				sumError += pow(target - fnet, 2);
			}
		}

		sumError /= (size * classSize);

		if (sumError < threshold) {
			allCorrect = true;
			break;
		}
	}

	if (allCorrect) {
		MessageBox::Show("Learning Completed Successfully");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], normalizeDrawMultiplier, 2);
	}
	else MessageBox::Show("Maximum number of epochs reached!");

	for (int c = 0; c < classSize; c++) {
		if (w[c] != nullptr) {
			delete[] w[c];
			w[c] = nullptr;
		}
	}
	delete[] w;
	delete[] delta;
}
```

![4](https://github.com/user-attachments/assets/18661666-f809-4473-88e6-910eec523070)

---

## Multi-Layer Neural Networks

Multi-layer artificial neural networks are models containing more than one hidden layer and are used in more complex problems. These networks perform well in nonlinear problems.

### Structure

- **Input Layer**: Data is transferred to the network.
- **Hidden Layers**: Each layer processes the outputs from the previous layer and passes them to the next layer.
- **Output Layer**: The last layer produces the final output of the network.

Each neuron processes the data from the previous layer:

```
zₖ = Σ(wₖⱼ * yⱼ) + bₖ
```

### Activation Functions

Activation functions in multi-layer networks increase the nonlinear learning capability of the network:
- **ReLU (Rectified Linear Unit)**: f(z) = max(0, z)
- **Tanh**: f(z) = (eᶻ - e⁻ᶻ) / (eᶻ + e⁻ᶻ)
- **Softmax**: Used in multi-class classification:

```
fᵢ(z) = eᶻⁱ / Σ(eᶻʲ)
```

### Learning Process

In multi-layer networks, the learning process is usually carried out with the "Backpropagation" algorithm. This algorithm updates the weights to minimize the error function.

### Application Areas

- Used in complex problems such as image processing, natural language processing, and time series analysis.
- Forms the basis of deep learning models.

## Limitations

- High computational cost.
- Requires large datasets.
- Risk of overfitting.

## Advantages

- High accuracy in complex problems.
- Effective solutions for nonlinear problems.

### Codes for Multi Classes Multi Layer

```c++
void multiLayer_Click(Object^ sender, EventArgs^ e)
{
	MultiLayerPerceptron* mlp = new MultiLayerPerceptron(classSize, hiddenLayerSize, classSize, learningRate); 

	std::vector<Samples> samples;
	for (int j = 0; j < size; j++) {
		Samples s = { p[j].x1, p[j].x2, p[j].id };
		samples.push_back(s);
	}

	std::vector<std::vector<double>> targets;
	for (int j = 0; j < size; j++) {
		if (p[j].id < 0 || p[j].id >= 3) {
			continue;
		}

		std::vector<double> target(classSize, 0.0);
		target[p[j].id] = 1.0;
		targets.push_back(target);
	}

	if (samples.size() != targets.size()) {
		std::cerr << "Sample count and target count do not match!" << std::endl;
		delete mlp;
		return;
	}

	mlp->train(samples, targets, maxEpoch);

	int width = pictureBox1->Width;
	int height = pictureBox1->Height;
	int step = 5;

	Graphics^ g = pictureBox1->CreateGraphics();

	for (int x = 0; x < width; x += step) {
		for (int y = 0; y < height; y += step) {
			double rawX = x - width / 2.0;
			double rawY = height / 2.0 - y;

			Samples sample = { rawX / normalizeDrawMultiplier, rawY / normalizeDrawMultiplier, -1 };

			std::vector<double> output = mlp->forward(sample);

			int predictedClass = std::distance(output.begin(), std::max_element(output.begin(), output.end()));

			Color color;
			int alpha = 128; 
			switch (predictedClass) {
			case 0: color = Color::FromArgb(alpha, Color::LightGray); break;
			case 1: color = Color::FromArgb(alpha, Color::Red); break;
			case 2: color = Color::FromArgb(alpha, Color::Purple); break;
			case 3: color = Color::FromArgb(alpha, Color::Green); break;
			case 4: color = Color::FromArgb(alpha, Color::Brown); break;
			case 5: color = Color::FromArgb(alpha, Color::Yellow); break;
			default: color = Color::FromArgb(alpha, Color::White); break;
			}

			SolidBrush^ brush = gcnew SolidBrush(color);
			g->FillRectangle(brush, x, y, step, step);
		}
	}

	delete g;
	delete mlp;
}

MultiLayerPerceptron(int inputSize, int hiddenSize, int outputSize, double learningRate) {
    this->inputSize = inputSize;
    this->hiddenSize = hiddenSize;
    this->outputSize = outputSize;
    this->learningRate = learningRate;

    srand(static_cast<unsigned>(time(0)));

    weightsInputHidden.resize(inputSize, std::vector<double>(hiddenSize));
    for (int i = 0; i < inputSize; ++i)
        for (int j = 0; j < hiddenSize; ++j)
            weightsInputHidden[i][j] = randomWeight();

    weightsHiddenOutput.resize(hiddenSize, std::vector<double>(outputSize));
    for (int i = 0; i < hiddenSize; ++i)
        for (int j = 0; j < outputSize; ++j)
            weightsHiddenOutput[i][j] = randomWeight();
}

std::vector<double> forward(const Samples& sample) {
    hiddenLayer.resize(hiddenSize);
    for (int j = 0; j < hiddenSize; ++j) {
        hiddenLayer[j] = 0.0;
        for (int i = 0; i < inputSize; ++i)
            hiddenLayer[j] += (i == 0 ? sample.x1 : sample.x2) * weightsInputHidden[i][j];
        hiddenLayer[j] = sigmoid(hiddenLayer[j]);
    }

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
    std::vector<double> outputError(outputSize);
    for (int k = 0; k < outputSize; ++k)
        outputError[k] = (target[k] - outputLayer[k]) * sigmoidDerivative(outputLayer[k]);

    std::vector<double> hiddenError(hiddenSize);
    for (int j = 0; j < hiddenSize; ++j) {
        hiddenError[j] = 0.0;
        for (int k = 0; k < outputSize; ++k)
            hiddenError[j] += outputError[k] * weightsHiddenOutput[j][k];
        hiddenError[j] *= sigmoidDerivative(hiddenLayer[j]);
    }

    for (int j = 0; j < hiddenSize; ++j)
        for (int k = 0; k < outputSize; ++k)
            weightsHiddenOutput[j][k] += learningRate * outputError[k] * hiddenLayer[j];

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
```

![5](https://github.com/user-attachments/assets/619874d2-c11d-4b82-93d3-955d3b9cf0b6)

---

### Commonly Used Functions in the Project

#### YPoint

```c++
double YPoint(int x, double* w, int multiplier)
{
	if (w[1] == 0) w[1] = 0.001;
	return ((double)(-1 * (double)multiplier * w[2] - w[0] * x) / (double)(w[1]));
}
```

#### sigmoid

```c++
double sigmoid(double net) 
{
	return 1.0 / (1.0 + exp(-net));
}
```

#### sigmoidDerivative

```c++
double sigmoidDerivative(double net)
{
	return sigmoid(net) * (1 - sigmoid(net));
}
```

#### thresholdOut

```c++
double thresholdOut(double out)
{
	return out > 0.5 ? 1 : 0;
}
```

#### getError

```c++
double getError(double target, double result){
	return target - result;
}
```

#### getErrorDelta

```c++
double getErrorDelta(double target, double result) 	
{
	return (0.5 * pow(target - result, 2));
}
```

#### getY

```c++
double getY(double* weight, double x1, double x2)
{
	return (weight[0] * x1) + (weight[1] * x2) + weight[2];
}
```

#### updateWeights

```c++
void updateWeights(double* weights, double x1, double x2, double delta, double learning_rate)
{
	weights[0] += (learning_rate * delta * x1);
	weights[1] += (learning_rate * delta * x2);
	weights[2] += (learning_rate * delta);
}
```

#### normalizeData

```c++
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
```

#### shuffleData

```c++
void shuffleData(Samples* data, int size) {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(data, data + size, g);
}
```
