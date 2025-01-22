[rapor.md](https://github.com/user-attachments/files/18504681/rapor.md)
# Tek ve Çok Katmanlı Yapay Sinir Ağları

Tek ve çok katmanlı yapay sinir ağları, giriş verilerini işleyerek belirli bir çıktı üretmek üzere tasarlanmış matematiksel modellerdir. Tek katmanlı ağlar temel problemler için yeterli olurken, çok katmanlı ağlar daha karmaşık problemlerde kullanılır.

## Single Neuron (Tek Nöron) Modeli
Bir yapay nöron, biyolojik nöronun çalışma prensibini taklit eden matematiksel bir modeldir. Tek bir nöron, giriş değerlerini alır, ağırlıklarla çarpar, bir aktivasyon fonksiyonundan geçirir ve bir çıkış üretir.

### Girişler (Inputs)
- **Girişler (Inputs)**: x₁, x₂, ..., xₙ
- **Ağırlıklar (Weights)**: Her giriş xᵢ, bir ağırlık wᵢ ile çarpılır.
- **Net Giriş (Weighted Sum)**: Net giriş, tüm ağırlıklandırılmış girişlerin toplamıdır:

```
z = Σ(wᵢ * xᵢ) + b
```

Burada b, bias (sapma) terimidir.

### Aktivasyon Fonksiyonu
z değerine aktivasyon fonksiyonu uygulanarak çıkış hesaplanır:

```
y = f(z)
```

Aktivasyon fonksiyonları doğrusal veya doğrusal olmayan türde olabilir:
- **Doğrusal**: f(z) = z
- **Sigmoid**: f(z) = 1 / (1 + e⁻ᶻ)
- **Adım Fonksiyonu (Step)**: f(z) = 1, z ≥ 0; aksi halde f(z) = 0.

### Two Classes Single Layer için kodlar
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
			MessageBox::Show("Ogrenme Basariyla Tamamlandi");
			drawLine(Color::Red, w, 1, 2);
			break;
		}
	}

	if (iteration >= maxEpoch) {
		MessageBox::Show("Maximum donguye ulasildi!");
		isClassSelectionValid();
	}
}
 ```

![1](1.png)

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
		MessageBox::Show("Ogrenme Basariyla Tamamlandi");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], normalizeDrawMultiplier, 2);
	}
	else MessageBox::Show("Maximum donguye ulasildi!");

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

![2](2.png)

## Multi Neuron (Çok Nöron) Modeli
Çok nöronlu bir model, birden fazla nöronun aynı katmanda çalıştığı yapıdır. Her nöron, giriş verilerini bağımsız olarak işler ve genellikle farklı bir sınıfa veya çıktı değerine karşılık gelir.

### Girişler ve Çıkışlar
- **Girişler (Inputs)**: x₁, x₂, ..., xₙ tüm nöronlar için ortak girişlerdir.
- **Çıkışlar (Outputs)**: Her nöron, kendi ağırlıklarına ve aktivasyon fonksiyonuna bağlı olarak bir çıktı üretir:

```
yⱼ = fⱼ(Σ(wⱼᵢ * xᵢ) + bⱼ)
```

Burada:
- j: Nöronun indeksidir.
- wⱼᵢ: j. nöronun i. giriş için ağırlığıdır.
- bⱼ: j. nöronun bias terimidir.
- fⱼ: j. nöronun aktivasyon fonksiyonudur.

### Öğrenme Süreci
Çok nöronlu modelde her nöronun ağırlıkları bağımsız olarak öğrenilir. Genellikle, "One-vs-All" (OvA) yaklaşımı kullanılır:
- Her nöron, bir sınıfı diğerlerinden ayırmaya çalışır.
- Hata fonksiyonu tüm nöronlar için ayrı ayrı hesaplanır ve minimize edilir.

### Kullanım Alanları
- **Çok Sınıflı Sınıflandırma (Multi-Class Classification)**: Birden fazla sınıfı ayırt edebilen yapılar.
- **Regression (Doğrusal Olmayan Regresyon)**: Karmaşık çıktılar üretebilen sistemler.

### Multi Classes Single Layer için kodlar
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
		MessageBox::Show("Ogrenme Basariyla Tamamlandi");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], 1, 2);
	}
	else MessageBox::Show("Maximum donguye ulasildi!");

	for (int i = 0; i < classSize; i++) delete[] w[i];

	delete[] w;
}
```
![3](3.png)
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
		MessageBox::Show("Ogrenme Basariyla Tamamlandi");
		for (int c = 0; c < classSize; c++) drawLine(SetColor(c), w[c], normalizeDrawMultiplier, 2);
	}
	else MessageBox::Show("Maximum donguye ulasildi!");

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
![4](4.png)

## Multi-Layer Neural Networks (Çok Katmanlı Ağlar)
Çok katmanlı yapay sinir ağları, birden fazla gizli katman içeren ve daha karmaşık problemlerde kullanılan modellerdir. Bu ağlar doğrusal olmayan problemlerde yüksek performans gösterir.

### Yapısı
- **Giriş Katmanı**: Veri ağın girişine aktarılır.
- **Gizli Katmanlar (Hidden Layers)**: Her katman, bir önceki katmandan gelen çıktıları işler ve bir sonraki katmana aktarır.
- **Çıkış Katmanı**: Son katman, ağın nihai çıktısını üretir.

Her nöron, önceki katmandan gelen verileri işler:

```
zₖ = Σ(wₖⱼ * yⱼ) + bₖ
```

### Aktivasyon Fonksiyonları
Çok katmanlı ağlarda aktivasyon fonksiyonları, ağın doğrusal olmayan öğrenme yeteneğini artırır:
- **ReLU (Rectified Linear Unit)**: f(z) = max(0, z)
- **Tanh**: f(z) = (eᶻ - e⁻ᶻ) / (eᶻ + e⁻ᶻ)
- **Softmax**: Çok sınıflı sınıflandırmalarda kullanılır:

```
fᵢ(z) = eᶻⁱ / Σ(eᶻʲ)
```

### Öğrenme Süreci
Çok katmanlı ağlarda, öğrenme işlemi genellikle "Backpropagation" (geri yayılım) algoritmasıyla gerçekleştirilir. Bu algoritma, hata fonksiyonunu minimize etmek için ağırlıkları günceller.

### Kullanım Alanları
- Görüntü işleme, doğal dil işleme ve zaman serisi analizleri gibi karmaşık problemlerde kullanılır.
- Derin öğrenme (Deep Learning) modellerinin temelini oluşturur.

## Sınırlamaları
- Hesaplama maliyeti yüksektir.
- Büyük veri setlerine ihtiyaç duyar.
- Aşırı öğrenme (overfitting) riski taşır.

## Avantajları
- Karmaşık problemlerde yüksek doğruluk sağlar.
- Doğrusal olmayan problemlerde etkili çözümler sunar.

### Multi Classes Multi Layer için kodlar
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
		std::cerr << "Örnek sayısı ve hedef sayısı aynı değil!" << std::endl;
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
![5](5.png)

### Proje esnasında ortak kullanılan fonksiyonlar
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
