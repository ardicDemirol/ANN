#pragma once
#include <Windows.h>
#include "Resource.h"
#include <time.h>
#include "Process.h"
#include <iostream>
#include "MultiLayerPerceptron.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class MyForm : public Form
{
public:
#pragma region Windows Form Designer generated code

	MyForm(void)
	{
		InitializeComponent();
		AttachConsoleWindow();
		size = size1 = size2 = size3 = size4 = size5 = size6 = 0;
		allCorrect = false;
		learningRate = 0.1;
		maxEpoch = 1000000;
		classSize = 0;
		color = Color::Transparent;
		centerX = pictureBox1->Width / 2;
		centerY = pictureBox1->Height / 2;
		normalizeDrawMultiplier = 30;
		hiddenLayerSize = 5;

	}

protected:
	~MyForm()
	{
		if (components) delete components;
		delete w;
		w = nullptr;
	}
private:
	MenuStrip^ menuStrip1;
	ToolStripMenuItem^ processToolStripMenuItem;
	ToolStripMenuItem^ initialToolStripMenuItem;
	ToolStripMenuItem^ randomlyToolStripMenuItem;
	ToolStripMenuItem^ trainToolStripMenuItem;
	ToolStripMenuItem^ binaryToolStripMenuItem;
	ToolStripMenuItem^ continuouslyToolStripMenuItem;
	ToolStripMenuItem^ exitToolStripMenuItem;
	ToolStripMenuItem^ multiclassToolStripMenuItem;
	ToolStripMenuItem^ binaryToolStripMenuItem1;
	ToolStripMenuItem^ continuouslyToolStripMenuItem1;
	PictureBox^ pictureBox1;
	CheckBox^ check_Class1;
	CheckBox^ check_Class2;
	CheckBox^ check_Class3;
	CheckBox^ check_Class4;
	CheckBox^ check_Class5;
	CheckBox^ check_Class6;

	Label^ label1;
	Label^ label2;
	Label^ label3;

	TextBox^ textBox1;
	Button^ button2;
	System::ComponentModel::Container^ components;

	Samples* p;
	double* w;
	int		size, size1, size2, size3, size4, size5, size6, classSize;
	int		maxEpoch;
	double	learningRate;
	bool	allCorrect;
	int centerX, centerY;
	int normalizeDrawMultiplier;
	int hiddenLayerSize;
	Color color;


	void InitializeComponent(void)
	{
		this->menuStrip1 = (gcnew MenuStrip());
		this->processToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->initialToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->randomlyToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->trainToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->binaryToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->continuouslyToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->multiclassToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->binaryToolStripMenuItem1 = (gcnew ToolStripMenuItem());
		this->continuouslyToolStripMenuItem1 = (gcnew ToolStripMenuItem());
		this->exitToolStripMenuItem = (gcnew ToolStripMenuItem());
		this->pictureBox1 = (gcnew PictureBox());
		this->check_Class1 = (gcnew CheckBox());
		this->check_Class2 = (gcnew CheckBox());
		this->check_Class3 = (gcnew CheckBox());
		this->check_Class4 = (gcnew CheckBox());
		this->check_Class5 = (gcnew CheckBox());
		this->check_Class6 = (gcnew CheckBox());
		this->label1 = (gcnew Label());
		this->label2 = (gcnew Label());
		this->textBox1 = (gcnew TextBox());
		this->label3 = (gcnew Label());
		this->button2 = (gcnew Button());
		this->menuStrip1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		this->SuspendLayout();
		// 
		// menuStrip1
		// 
		this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
		this->menuStrip1->Items->AddRange(gcnew cli::array< ToolStripItem^  >(1) { this->processToolStripMenuItem });
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1211, 30);
		this->menuStrip1->TabIndex = 0;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// processToolStripMenuItem
		// 
		this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<ToolStripItem^>(4) {
			this->initialToolStripMenuItem,
				this->trainToolStripMenuItem, this->multiclassToolStripMenuItem, this->exitToolStripMenuItem
		});
		this->processToolStripMenuItem->Name = L"processToolStripMenuItem";
		this->processToolStripMenuItem->Size = System::Drawing::Size(73, 26);
		this->processToolStripMenuItem->Text = L"process";
		// 
	   // trainToolStripMenuItem
	   // 
		this->trainToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->binaryToolStripMenuItem,
				this->continuouslyToolStripMenuItem
		});
		this->trainToolStripMenuItem->Name = L"trainToolStripMenuItem";
		this->trainToolStripMenuItem->Size = System::Drawing::Size(208, 26);
		this->trainToolStripMenuItem->Text = L"Doubleclass Train";
		this->trainToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::trainToolStripMenuItem_Click);
		// 
		// binaryToolStripMenuItem
		// 
		this->binaryToolStripMenuItem->Name = L"binaryToolStripMenuItem";
		this->binaryToolStripMenuItem->Size = System::Drawing::Size(177, 26);
		this->binaryToolStripMenuItem->Text = L"Binary";
		this->binaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::binaryToolStripMenuItem_Click);
		
		// 
		// multiclassToolStripMenuItem
		// 
		this->multiclassToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->binaryToolStripMenuItem1,
				this->continuouslyToolStripMenuItem1
		});
		this->multiclassToolStripMenuItem->Name = L"multiclassToolStripMenuItem";
		this->multiclassToolStripMenuItem->Size = System::Drawing::Size(208, 26);
		this->multiclassToolStripMenuItem->Text = L"Multiclass Train";
		
		// exitToolStripMenuItem
		// 
		this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
		this->exitToolStripMenuItem->Size = System::Drawing::Size(208, 26);
		this->exitToolStripMenuItem->Text = L"exit";
		this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
		// 
		// pictureBox1
		// 
		this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
		this->pictureBox1->Location = System::Drawing::Point(13, 32);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(827, 393);
		this->pictureBox1->TabIndex = 1;
		this->pictureBox1->TabStop = false;
		this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
		this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseClick);
		// 
		// check_Class1
		// 
		this->check_Class1->AutoSize = true;
		this->check_Class1->Checked = true;
		this->check_Class1->CheckState = System::Windows::Forms::CheckState::Checked;
		this->check_Class1->Location = System::Drawing::Point(886, 45);
		this->check_Class1->Name = L"check_Class1";
		this->check_Class1->Size = System::Drawing::Size(71, 20);
		this->check_Class1->TabIndex = 2;
		this->check_Class1->Text = L"class 1";
		this->check_Class1->UseVisualStyleBackColor = true;
		// 
		// check_Class2
		// 
		this->check_Class2->AutoSize = true;
		this->check_Class2->Location = System::Drawing::Point(886, 71);
		this->check_Class2->Name = L"check_Class2";
		this->check_Class2->Size = System::Drawing::Size(71, 20);
		this->check_Class2->TabIndex = 3;
		this->check_Class2->Text = L"class 2";
		this->check_Class2->UseVisualStyleBackColor = true;
		// 
		// check_Class3
		// 
		this->check_Class3->AutoSize = true;
		this->check_Class3->Location = System::Drawing::Point(886, 97);
		this->check_Class3->Name = L"check_Class3";
		this->check_Class3->Size = System::Drawing::Size(71, 20);
		this->check_Class3->TabIndex = 4;
		this->check_Class3->Text = L"class 3";
		this->check_Class3->UseVisualStyleBackColor = true;
		// 
		// check_Class4
		// 
		this->check_Class4->AutoSize = true;
		this->check_Class4->Location = System::Drawing::Point(886, 123);
		this->check_Class4->Name = L"check_Class4";
		this->check_Class4->Size = System::Drawing::Size(71, 20);
		this->check_Class4->TabIndex = 5;
		this->check_Class4->Text = L"class 4";
		this->check_Class4->UseVisualStyleBackColor = true;
		// 
		// check_Class5
		// 
		this->check_Class5->AutoSize = true;
		this->check_Class5->Location = System::Drawing::Point(886, 149);
		this->check_Class5->Name = L"check_Class5";
		this->check_Class5->Size = System::Drawing::Size(71, 20);
		this->check_Class5->TabIndex = 6;
		this->check_Class5->Text = L"class 5";
		this->check_Class5->UseVisualStyleBackColor = true;
		this->check_Class5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
		// 
		// check_Class6
		// 
		this->check_Class6->AutoSize = true;
		this->check_Class6->Location = System::Drawing::Point(886, 175);
		this->check_Class6->Name = L"check_Class6";
		this->check_Class6->Size = System::Drawing::Size(71, 20);
		this->check_Class6->TabIndex = 7;
		this->check_Class6->Text = L"class 6";
		this->check_Class6->UseVisualStyleBackColor = true;
		this->check_Class6->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(896, 284);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(44, 16);
		this->label1->TabIndex = 8;
		this->label1->Text = L"label1";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(896, 315);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(44, 16);
		this->label2->TabIndex = 9;
		this->label2->Text = L"label2";
		// 
		// textBox1
		// 
		this->textBox1->Location = System::Drawing::Point(1127, 45);
		this->textBox1->Name = L"textBox1";
		this->textBox1->Size = System::Drawing::Size(55, 22);
		this->textBox1->TabIndex = 10;
		this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(1029, 48);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(92, 16);
		this->label3->TabIndex = 11;
		this->label3->Text = L"Class Number";
		// 
		// button2
		// 
		this->button2->ForeColor = System::Drawing::Color::CornflowerBlue;
		this->button2->Location = System::Drawing::Point(1106, 393);
		this->button2->Name = L"button2";
		this->button2->Size = System::Drawing::Size(75, 23);
		this->button2->TabIndex = 13;
		this->button2->Text = L"Reset";
		this->button2->UseVisualStyleBackColor = true;
		this->button2->Click += gcnew System::EventHandler(this, &MyForm::resetButton_Click);
		// 
		// MyForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1211, 437);
		this->Controls->Add(this->button2);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->textBox1);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->check_Class6);
		this->Controls->Add(this->check_Class5);
		this->Controls->Add(this->check_Class4);
		this->Controls->Add(this->check_Class3);
		this->Controls->Add(this->check_Class2);
		this->Controls->Add(this->check_Class1);
		this->Controls->Add(this->pictureBox1);
		this->Controls->Add(this->menuStrip1);
		this->Name = L"MyForm";
		this->Text = L"MyForm";
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}

#pragma endregion


	void binaryToolStripMenuItem_Click(Object^ sender, EventArgs^ e)
	{
		MultiLayerPerceptron* mlp = new MultiLayerPerceptron(2, hiddenLayerSize, classSize, learningRate); 

		std::vector<Samples> samples;
		for (int j = 0; j < size; j++) {
			Samples s = { p[j].x1, p[j].x2, p[j].id };
			samples.push_back(s);
		}

		std::vector<std::vector<double>> targets;
		for (int j = 0; j < size; j++) {
			if (p[j].id < 0 || p[j].id >= classSize) continue;

			std::vector<double> target(classSize, 0.0);
			target[p[j].id] = 1.0;
			targets.push_back(target);
		}

		if (samples.size() != targets.size()) {
			std::cerr << "Örnek sayýsý ve hedef sayýsý ayný deðil!" << std::endl;
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


	void addSample(int classId, MouseEventArgs^ e, Color color) {
		std::pair<double, double> coordinates = CalculateCoordinates(e);
		updateSamplesArray(coordinates.first, coordinates.second, classId);
		updateLabels();
		drawPoint(e, color);
	}

	void updateSamplesArray(double x1, double x2, int classId) {
		Samples* temp = p;
		int newSize = ++size;
		p = new Samples[newSize];

		for (int i = 0; i < newSize - 1; i++) {
			p[i].x1 = temp[i].x1;
			p[i].x2 = temp[i].x2;
			p[i].id = temp[i].id;
		}

		p[newSize - 1].x1 = x1;
		p[newSize - 1].x2 = x2;
		p[newSize - 1].id = classId;

		if (classId == CLASS1) size1++;
		else if (classId == CLASS2) size2++;
		else if (classId == CLASS3) size3++;
		else if (classId == CLASS4) size4++;
		else if (classId == CLASS5) size5++;
		else if (classId == CLASS6) size6++;

		if (temp != nullptr) delete[] temp;
	}

	void drawPoint(MouseEventArgs^ e, Color color) {
		Pen^ pen = gcnew Pen(color, 3.0f);
		pictureBox1_MouseClickPaint(e, pen);
	}


#pragma region MyRegion

	std::pair<double, double> CalculateCoordinates(MouseEventArgs^ e) {
		int temp_x = System::Convert::ToInt32(e->X);
		int temp_y = System::Convert::ToInt32(e->Y);
		double x1 = static_cast<double>(temp_x - (pictureBox1->Width >> 1));
		double x2 = static_cast<double>((pictureBox1->Height >> 1) - temp_y);
		return { x1, x2 };
	}

	void pictureBox1_Paint(Object^ sender, PaintEventArgs^ e) {
		Pen^ pen = gcnew Pen(Color::Black, 3.0f);
		e->Graphics->DrawLine(pen, centerX, 0, centerX, pictureBox1->Height);
		e->Graphics->DrawLine(pen, 0, centerY, pictureBox1->Width, centerY);
	}

	void pictureBox1_MouseClick(Object^ sender, MouseEventArgs^ e) {
		if (isClassSelectionValid())
		{
			if (check_Class1->Checked) addSample(CLASS1, e, Color::Black);
			else if (check_Class2->Checked) addSample(CLASS2, e, Color::Red);
			else if (check_Class3->Checked) addSample(CLASS3, e, Color::Purple);
			else if (check_Class4->Checked) addSample(CLASS4, e, Color::Green);
			else if (check_Class5->Checked) addSample(CLASS5, e, Color::Brown);
			else if (check_Class6->Checked) addSample(CLASS6, e, Color::Yellow);
		}
	}

	void pictureBox1_MouseClickPaint(MouseEventArgs^ e, Pen^ pen) {
		int temp_x, temp_y;
		temp_x = (System::Convert::ToInt32(e->X)); // e holds the coordinate of where the mouse was clicked 
		temp_y = (System::Convert::ToInt32(e->Y));
		pictureBox1->CreateGraphics()->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
		pictureBox1->CreateGraphics()->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
	}

	bool isClassSelectionValid() {
		int selectedCount = 0;
		if (check_Class1->Checked) selectedCount++;
		if (check_Class2->Checked) selectedCount++;
		if (check_Class3->Checked) selectedCount++;
		if (check_Class4->Checked) selectedCount++;
		if (check_Class5->Checked) selectedCount++;
		if (check_Class6->Checked) selectedCount++;

		if (selectedCount > 1) {
			MessageBox::Show("Ayni anda 1'den fazla class seçemezsiniz!");
			check_Class1->Checked = false;
			check_Class2->Checked = false;
			check_Class3->Checked = false;
			check_Class4->Checked = false;
			check_Class5->Checked = false;
			check_Class6->Checked = false;
			return false;
		}
		return selectedCount == 1;
	}

	void textBox1_TextChanged(Object^ sender, EventArgs^ e) {
		if (String::IsNullOrEmpty(textBox1->Text)) {
			classSize = 2;
			return;
		}

		if (System::Text::RegularExpressions::Regex::IsMatch(textBox1->Text, "^[0-9]+$")) {
			classSize = System::Convert::ToInt32(textBox1->Text);
		}
		else {
			MessageBox::Show("Please enter a valid number.", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			textBox1->Text = "";
		}
	}

	void resetButton_Click(Object^ sender, EventArgs^ e) {
		size = size1 = size2 = size3 = size4 = size5 = size6 = 0;
		allCorrect = false;
		delete[] p;
		p = nullptr;
		delete[] w;
		w = nullptr;
		pictureBox1->Refresh();
	}

	void updateLabels() {
		label1->Text = "x1: " + Convert::ToString(p[size - 1].x1) + " x2: " + Convert::ToString(p[size - 1].x2) + " id: " + p[size - 1].id;
		label2->Text = "Samples Total: " + Convert::ToString(size);
	}


	void exitToolStripMenuItem_Click(Object^ sender, EventArgs^ e) { Application::Exit(); }
	void checkBox1_CheckedChanged(Object^ sender, EventArgs^ e) {}
	void checkBox2_CheckedChanged(Object^ sender, EventArgs^ e) {}
	void trainToolStripMenuItem_Click(Object^ sender, EventArgs^ e) {}

	void AttachConsoleWindow() {
		AllocConsole();
		FILE* stream;
		if (freopen_s(&stream, "CONOUT$", "w", stdout) != 0) {
			MessageBox::Show("Failed to redirect stdout");
		}
		if (freopen_s(&stream, "CONOUT$", "w", stderr) != 0) {
			MessageBox::Show("Failed to redirect stderr");
		}
	}

#pragma endregion


};
