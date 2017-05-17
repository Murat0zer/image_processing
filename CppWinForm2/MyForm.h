#pragma once
#include "Resim.h"
#include "islemler.h"
namespace CppWinForm2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPageCemberCiz;
	private: System::Windows::Forms::TabPage^  tabPageFilterHisogram;
	private: System::Windows::Forms::Label^  labelDosyaYolu;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	public: System::Windows::Forms::PictureBox^  pictureBoxCember;
	private: System::Windows::Forms::Button^  bmpIntensityButton;
	private: System::Windows::Forms::Label^  yaricap_label;
	private: System::Windows::Forms::Label^  Y_label;
	private: System::Windows::Forms::Button^  buttonCemberCiz;
	private: System::Windows::Forms::Label^  X_label;
	private: System::Windows::Forms::TextBox^  yariCap_textBox;
	private: System::Windows::Forms::TextBox^  YKord_textBox;
	private: System::Windows::Forms::TextBox^  Xkord_textBox;
	private: System::Windows::Forms::Button^  buttonResimSec;
	private: System::Windows::Forms::Button^  buttonHistogram;
	private: System::Windows::Forms::Button^  buttonGaussian;
	private: System::Windows::Forms::Button^  buttonMedian;
	private: System::Windows::Forms::Button^  buttonMean;
	private: System::Windows::Forms::PictureBox^  pBoxFHNew;
	private: System::Windows::Forms::PictureBox^  pBoxFHOriginal;
	private: System::Windows::Forms::Label^  labelDosyaYoluFH;
	private: System::Windows::Forms::Label^  labelKaydetFH;
	private: System::Windows::Forms::TextBox^  textBoxKayitYoluFH;
	private: System::Windows::Forms::Button^  buttonBmpIntensityFH;
	private: System::Windows::Forms::Button^  buttonResimSecFH;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxMatris;
	private: System::Windows::Forms::TextBox^  textBoxSigma;
	private: System::Windows::Forms::Label^  labelSigma;

	private: System::Windows::Forms::Button^  buttonBlackWhite;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartHistogram;
	private: System::Windows::Forms::TabPage^  tabPageSegmentation;
	private: System::Windows::Forms::PictureBox^  pictureBoxOklit;

	private: System::Windows::Forms::PictureBox^  pictureBoxSegmentOrj;
	private: System::Windows::Forms::RadioButton^  radioButtonMahalonobis;
	private: System::Windows::Forms::RadioButton^  radioButtonOklit;
	private: System::Windows::Forms::Label^  labelDosyaYoluSegment;
	private: System::Windows::Forms::TextBox^  textBoxSegment;



	private: System::Windows::Forms::Button^  buttonResimSecSegment;


	private: System::Windows::Forms::PictureBox^  pictureBoxMahalonois;

	private: System::Windows::Forms::RadioButton^  radioButtonRGB;
	private: System::Windows::Forms::RadioButton^  radioButtonIntensity;
	private: System::Windows::Forms::TextBox^  textBoxRenkAdet;
	private: System::Windows::Forms::Label^  labelRenkAdet;

	private: System::Windows::Forms::Button^  buttonProcess;



	private: System::Windows::Forms::Panel^  panelRadioButtonImageMode;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartSegMahalonobis;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartSegOklit;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chartSegOrj;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  labelTimer;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Button^  buttonCannyHough;
	private: System::Windows::Forms::Label^  labelDosyaYoluCanny;

	private: System::Windows::Forms::TextBox^  textBoxDosyaYoluCanny;
	private: System::Windows::Forms::Button^  buttonResimSecCanny;
	private: System::Windows::Forms::PictureBox^  pictureBoxCannyNew;

	private: System::Windows::Forms::PictureBox^  pictureBoxCannyGradient;

	private: System::Windows::Forms::PictureBox^  pictureBoxCannyOrj;



	private: System::ComponentModel::IContainer^  components;
private: System::Windows::Forms::TextBox^  textBoxTLow;
private: System::Windows::Forms::TextBox^  textBoxTHigh;



	private: System::Windows::Forms::TextBox^  textBoxT2;


	public:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series14 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea6 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series15 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series16 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series17 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series18 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea7 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series19 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series20 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series21 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series22 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea8 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend8 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series23 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series24 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series25 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series26 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPageCemberCiz = (gcnew System::Windows::Forms::TabPage());
			this->labelDosyaYolu = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBoxCember = (gcnew System::Windows::Forms::PictureBox());
			this->bmpIntensityButton = (gcnew System::Windows::Forms::Button());
			this->yaricap_label = (gcnew System::Windows::Forms::Label());
			this->Y_label = (gcnew System::Windows::Forms::Label());
			this->buttonCemberCiz = (gcnew System::Windows::Forms::Button());
			this->X_label = (gcnew System::Windows::Forms::Label());
			this->yariCap_textBox = (gcnew System::Windows::Forms::TextBox());
			this->YKord_textBox = (gcnew System::Windows::Forms::TextBox());
			this->Xkord_textBox = (gcnew System::Windows::Forms::TextBox());
			this->buttonResimSec = (gcnew System::Windows::Forms::Button());
			this->tabPageFilterHisogram = (gcnew System::Windows::Forms::TabPage());
			this->chartHistogram = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->buttonBlackWhite = (gcnew System::Windows::Forms::Button());
			this->labelSigma = (gcnew System::Windows::Forms::Label());
			this->textBoxSigma = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxMatris = (gcnew System::Windows::Forms::TextBox());
			this->labelDosyaYoluFH = (gcnew System::Windows::Forms::Label());
			this->labelKaydetFH = (gcnew System::Windows::Forms::Label());
			this->textBoxKayitYoluFH = (gcnew System::Windows::Forms::TextBox());
			this->buttonBmpIntensityFH = (gcnew System::Windows::Forms::Button());
			this->buttonResimSecFH = (gcnew System::Windows::Forms::Button());
			this->buttonHistogram = (gcnew System::Windows::Forms::Button());
			this->buttonGaussian = (gcnew System::Windows::Forms::Button());
			this->buttonMedian = (gcnew System::Windows::Forms::Button());
			this->buttonMean = (gcnew System::Windows::Forms::Button());
			this->pBoxFHNew = (gcnew System::Windows::Forms::PictureBox());
			this->pBoxFHOriginal = (gcnew System::Windows::Forms::PictureBox());
			this->tabPageSegmentation = (gcnew System::Windows::Forms::TabPage());
			this->labelTimer = (gcnew System::Windows::Forms::Label());
			this->chartSegMahalonobis = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chartSegOklit = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chartSegOrj = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->buttonProcess = (gcnew System::Windows::Forms::Button());
			this->panelRadioButtonImageMode = (gcnew System::Windows::Forms::Panel());
			this->radioButtonIntensity = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonRGB = (gcnew System::Windows::Forms::RadioButton());
			this->textBoxRenkAdet = (gcnew System::Windows::Forms::TextBox());
			this->labelRenkAdet = (gcnew System::Windows::Forms::Label());
			this->pictureBoxMahalonois = (gcnew System::Windows::Forms::PictureBox());
			this->labelDosyaYoluSegment = (gcnew System::Windows::Forms::Label());
			this->textBoxSegment = (gcnew System::Windows::Forms::TextBox());
			this->buttonResimSecSegment = (gcnew System::Windows::Forms::Button());
			this->radioButtonMahalonobis = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonOklit = (gcnew System::Windows::Forms::RadioButton());
			this->pictureBoxOklit = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxSegmentOrj = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->textBoxTHigh = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTLow = (gcnew System::Windows::Forms::TextBox());
			this->pictureBoxCannyNew = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxCannyGradient = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxCannyOrj = (gcnew System::Windows::Forms::PictureBox());
			this->buttonCannyHough = (gcnew System::Windows::Forms::Button());
			this->labelDosyaYoluCanny = (gcnew System::Windows::Forms::Label());
			this->textBoxDosyaYoluCanny = (gcnew System::Windows::Forms::TextBox());
			this->buttonResimSecCanny = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1->SuspendLayout();
			this->tabPageCemberCiz->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCember))->BeginInit();
			this->tabPageFilterHisogram->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartHistogram))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBoxFHNew))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBoxFHOriginal))->BeginInit();
			this->tabPageSegmentation->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegMahalonobis))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegOklit))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegOrj))->BeginInit();
			this->panelRadioButtonImageMode->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxMahalonois))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxOklit))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxSegmentOrj))->BeginInit();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyNew))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyGradient))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyOrj))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPageCemberCiz);
			this->tabControl1->Controls->Add(this->tabPageFilterHisogram);
			this->tabControl1->Controls->Add(this->tabPageSegmentation);
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->tabControl1->Location = System::Drawing::Point(5, 3);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1260, 731);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPageCemberCiz
			// 
			this->tabPageCemberCiz->BackColor = System::Drawing::Color::Lavender;
			this->tabPageCemberCiz->Controls->Add(this->labelDosyaYolu);
			this->tabPageCemberCiz->Controls->Add(this->label1);
			this->tabPageCemberCiz->Controls->Add(this->textBox1);
			this->tabPageCemberCiz->Controls->Add(this->pictureBoxCember);
			this->tabPageCemberCiz->Controls->Add(this->bmpIntensityButton);
			this->tabPageCemberCiz->Controls->Add(this->yaricap_label);
			this->tabPageCemberCiz->Controls->Add(this->Y_label);
			this->tabPageCemberCiz->Controls->Add(this->buttonCemberCiz);
			this->tabPageCemberCiz->Controls->Add(this->X_label);
			this->tabPageCemberCiz->Controls->Add(this->yariCap_textBox);
			this->tabPageCemberCiz->Controls->Add(this->YKord_textBox);
			this->tabPageCemberCiz->Controls->Add(this->Xkord_textBox);
			this->tabPageCemberCiz->Controls->Add(this->buttonResimSec);
			this->tabPageCemberCiz->Location = System::Drawing::Point(4, 24);
			this->tabPageCemberCiz->Name = L"tabPageCemberCiz";
			this->tabPageCemberCiz->Padding = System::Windows::Forms::Padding(3);
			this->tabPageCemberCiz->Size = System::Drawing::Size(1252, 703);
			this->tabPageCemberCiz->TabIndex = 0;
			this->tabPageCemberCiz->Text = L"Çember Çiz";
			// 
			// labelDosyaYolu
			// 
			this->labelDosyaYolu->Location = System::Drawing::Point(629, 476);
			this->labelDosyaYolu->Name = L"labelDosyaYolu";
			this->labelDosyaYolu->Size = System::Drawing::Size(333, 23);
			this->labelDosyaYolu->TabIndex = 27;
			this->labelDosyaYolu->Text = L"Resim sec";
			this->labelDosyaYolu->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(574, 512);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 15);
			this->label1->TabIndex = 26;
			this->label1->Text = L"Kaydet";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(629, 506);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(333, 21);
			this->textBox1->TabIndex = 25;
			this->textBox1->Text = L"Dosya Yolu";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// pictureBoxCember
			// 
			this->pictureBoxCember->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxCember->Location = System::Drawing::Point(5, 6);
			this->pictureBoxCember->Name = L"pictureBoxCember";
			this->pictureBoxCember->Size = System::Drawing::Size(1240, 458);
			this->pictureBoxCember->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxCember->TabIndex = 24;
			this->pictureBoxCember->TabStop = false;
			// 
			// bmpIntensityButton
			// 
			this->bmpIntensityButton->Location = System::Drawing::Point(968, 549);
			this->bmpIntensityButton->Name = L"bmpIntensityButton";
			this->bmpIntensityButton->Size = System::Drawing::Size(98, 50);
			this->bmpIntensityButton->TabIndex = 23;
			this->bmpIntensityButton->Text = L"BMP-Intensity";
			this->bmpIntensityButton->UseVisualStyleBackColor = true;
			this->bmpIntensityButton->Click += gcnew System::EventHandler(this, &MyForm::bmpIntensityButton_Click);
			// 
			// yaricap_label
			// 
			this->yaricap_label->AutoSize = true;
			this->yaricap_label->Location = System::Drawing::Point(315, 558);
			this->yaricap_label->Name = L"yaricap_label";
			this->yaricap_label->Size = System::Drawing::Size(48, 15);
			this->yaricap_label->TabIndex = 22;
			this->yaricap_label->Text = L"Yarýçap";
			// 
			// Y_label
			// 
			this->Y_label->AutoSize = true;
			this->Y_label->Location = System::Drawing::Point(315, 512);
			this->Y_label->Name = L"Y_label";
			this->Y_label->Size = System::Drawing::Size(64, 15);
			this->Y_label->TabIndex = 21;
			this->Y_label->Text = L"Y kordinatý";
			// 
			// buttonCemberCiz
			// 
			this->buttonCemberCiz->Location = System::Drawing::Point(115, 476);
			this->buttonCemberCiz->Name = L"buttonCemberCiz";
			this->buttonCemberCiz->Size = System::Drawing::Size(172, 123);
			this->buttonCemberCiz->TabIndex = 20;
			this->buttonCemberCiz->Text = L"Çember Çiz";
			this->buttonCemberCiz->UseVisualStyleBackColor = true;
			this->buttonCemberCiz->Click += gcnew System::EventHandler(this, &MyForm::buttonCemberCiz_Click_1);
			// 
			// X_label
			// 
			this->X_label->AutoSize = true;
			this->X_label->Location = System::Drawing::Point(315, 469);
			this->X_label->Name = L"X_label";
			this->X_label->Size = System::Drawing::Size(65, 15);
			this->X_label->TabIndex = 19;
			this->X_label->Text = L"X kordinatý";
			// 
			// yariCap_textBox
			// 
			this->yariCap_textBox->Location = System::Drawing::Point(318, 574);
			this->yariCap_textBox->Name = L"yariCap_textBox";
			this->yariCap_textBox->Size = System::Drawing::Size(42, 21);
			this->yariCap_textBox->TabIndex = 18;
			// 
			// YKord_textBox
			// 
			this->YKord_textBox->Location = System::Drawing::Point(318, 528);
			this->YKord_textBox->Name = L"YKord_textBox";
			this->YKord_textBox->Size = System::Drawing::Size(42, 21);
			this->YKord_textBox->TabIndex = 17;
			// 
			// Xkord_textBox
			// 
			this->Xkord_textBox->Location = System::Drawing::Point(318, 485);
			this->Xkord_textBox->Name = L"Xkord_textBox";
			this->Xkord_textBox->Size = System::Drawing::Size(42, 21);
			this->Xkord_textBox->TabIndex = 16;
			// 
			// buttonResimSec
			// 
			this->buttonResimSec->Location = System::Drawing::Point(968, 476);
			this->buttonResimSec->Name = L"buttonResimSec";
			this->buttonResimSec->Size = System::Drawing::Size(93, 50);
			this->buttonResimSec->TabIndex = 15;
			this->buttonResimSec->Text = L"Resim Seç";
			this->buttonResimSec->UseVisualStyleBackColor = true;
			this->buttonResimSec->Click += gcnew System::EventHandler(this, &MyForm::buttonResimSec_Click_1);
			// 
			// tabPageFilterHisogram
			// 
			this->tabPageFilterHisogram->BackColor = System::Drawing::Color::Lavender;
			this->tabPageFilterHisogram->Controls->Add(this->chartHistogram);
			this->tabPageFilterHisogram->Controls->Add(this->buttonBlackWhite);
			this->tabPageFilterHisogram->Controls->Add(this->labelSigma);
			this->tabPageFilterHisogram->Controls->Add(this->textBoxSigma);
			this->tabPageFilterHisogram->Controls->Add(this->label2);
			this->tabPageFilterHisogram->Controls->Add(this->textBoxMatris);
			this->tabPageFilterHisogram->Controls->Add(this->labelDosyaYoluFH);
			this->tabPageFilterHisogram->Controls->Add(this->labelKaydetFH);
			this->tabPageFilterHisogram->Controls->Add(this->textBoxKayitYoluFH);
			this->tabPageFilterHisogram->Controls->Add(this->buttonBmpIntensityFH);
			this->tabPageFilterHisogram->Controls->Add(this->buttonResimSecFH);
			this->tabPageFilterHisogram->Controls->Add(this->buttonHistogram);
			this->tabPageFilterHisogram->Controls->Add(this->buttonGaussian);
			this->tabPageFilterHisogram->Controls->Add(this->buttonMedian);
			this->tabPageFilterHisogram->Controls->Add(this->buttonMean);
			this->tabPageFilterHisogram->Controls->Add(this->pBoxFHNew);
			this->tabPageFilterHisogram->Controls->Add(this->pBoxFHOriginal);
			this->tabPageFilterHisogram->Location = System::Drawing::Point(4, 24);
			this->tabPageFilterHisogram->Name = L"tabPageFilterHisogram";
			this->tabPageFilterHisogram->Padding = System::Windows::Forms::Padding(3);
			this->tabPageFilterHisogram->Size = System::Drawing::Size(1252, 703);
			this->tabPageFilterHisogram->TabIndex = 1;
			this->tabPageFilterHisogram->Text = L"Filters-Histogram";
			// 
			// chartHistogram
			// 
			chartArea5->Name = L"ChartArea1";
			this->chartHistogram->ChartAreas->Add(chartArea5);
			legend5->Name = L"Legend1";
			this->chartHistogram->Legends->Add(legend5);
			this->chartHistogram->Location = System::Drawing::Point(512, 360);
			this->chartHistogram->Name = L"chartHistogram";
			series14->ChartArea = L"ChartArea1";
			series14->IsVisibleInLegend = false;
			series14->Legend = L"Legend1";
			series14->Name = L"intensity";
			this->chartHistogram->Series->Add(series14);
			this->chartHistogram->Size = System::Drawing::Size(731, 253);
			this->chartHistogram->TabIndex = 40;
			this->chartHistogram->Text = L"chartHistogram";
			title2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			title2->Name = L"histogram";
			title2->Text = L"Histogram";
			this->chartHistogram->Titles->Add(title2);
			this->chartHistogram->Visible = false;
			// 
			// buttonBlackWhite
			// 
			this->buttonBlackWhite->Location = System::Drawing::Point(399, 485);
			this->buttonBlackWhite->Name = L"buttonBlackWhite";
			this->buttonBlackWhite->Size = System::Drawing::Size(93, 44);
			this->buttonBlackWhite->TabIndex = 39;
			this->buttonBlackWhite->Text = L"Siyah-Beyaz";
			this->buttonBlackWhite->UseVisualStyleBackColor = true;
			this->buttonBlackWhite->Click += gcnew System::EventHandler(this, &MyForm::buttonBlackWhite_Click);
			// 
			// labelSigma
			// 
			this->labelSigma->AutoSize = true;
			this->labelSigma->Location = System::Drawing::Point(174, 535);
			this->labelSigma->Name = L"labelSigma";
			this->labelSigma->Size = System::Drawing::Size(150, 15);
			this->labelSigma->TabIndex = 37;
			this->labelSigma->Text = L"Gaussian Filter Ýçin Sigma";
			// 
			// textBoxSigma
			// 
			this->textBoxSigma->Location = System::Drawing::Point(141, 535);
			this->textBoxSigma->Name = L"textBoxSigma";
			this->textBoxSigma->Size = System::Drawing::Size(27, 21);
			this->textBoxSigma->TabIndex = 36;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(174, 434);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(131, 15);
			this->label2->TabIndex = 35;
			this->label2->Text = L"Filtre Matrisinin Boyutu";
			// 
			// textBoxMatris
			// 
			this->textBoxMatris->Location = System::Drawing::Point(141, 434);
			this->textBoxMatris->Name = L"textBoxMatris";
			this->textBoxMatris->Size = System::Drawing::Size(27, 21);
			this->textBoxMatris->TabIndex = 34;
			// 
			// labelDosyaYoluFH
			// 
			this->labelDosyaYoluFH->Location = System::Drawing::Point(60, 367);
			this->labelDosyaYoluFH->Name = L"labelDosyaYoluFH";
			this->labelDosyaYoluFH->Size = System::Drawing::Size(333, 23);
			this->labelDosyaYoluFH->TabIndex = 32;
			this->labelDosyaYoluFH->Text = L"Resim sec";
			this->labelDosyaYoluFH->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelKaydetFH
			// 
			this->labelKaydetFH->AutoSize = true;
			this->labelKaydetFH->Location = System::Drawing::Point(12, 403);
			this->labelKaydetFH->Name = L"labelKaydetFH";
			this->labelKaydetFH->Size = System::Drawing::Size(44, 15);
			this->labelKaydetFH->TabIndex = 31;
			this->labelKaydetFH->Text = L"Kaydet";
			// 
			// textBoxKayitYoluFH
			// 
			this->textBoxKayitYoluFH->Location = System::Drawing::Point(60, 397);
			this->textBoxKayitYoluFH->Name = L"textBoxKayitYoluFH";
			this->textBoxKayitYoluFH->Size = System::Drawing::Size(333, 21);
			this->textBoxKayitYoluFH->TabIndex = 30;
			this->textBoxKayitYoluFH->Text = L"Dosya Yolu";
			this->textBoxKayitYoluFH->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonBmpIntensityFH
			// 
			this->buttonBmpIntensityFH->Location = System::Drawing::Point(398, 429);
			this->buttonBmpIntensityFH->Name = L"buttonBmpIntensityFH";
			this->buttonBmpIntensityFH->Size = System::Drawing::Size(94, 50);
			this->buttonBmpIntensityFH->TabIndex = 29;
			this->buttonBmpIntensityFH->Text = L"BMP-Intensity";
			this->buttonBmpIntensityFH->UseVisualStyleBackColor = true;
			this->buttonBmpIntensityFH->Click += gcnew System::EventHandler(this, &MyForm::buttonBmpIntensityFH_Click);
			// 
			// buttonResimSecFH
			// 
			this->buttonResimSecFH->Location = System::Drawing::Point(399, 367);
			this->buttonResimSecFH->Name = L"buttonResimSecFH";
			this->buttonResimSecFH->Size = System::Drawing::Size(93, 50);
			this->buttonResimSecFH->TabIndex = 28;
			this->buttonResimSecFH->Text = L"Resim Seç";
			this->buttonResimSecFH->UseVisualStyleBackColor = true;
			this->buttonResimSecFH->Click += gcnew System::EventHandler(this, &MyForm::buttonResimSecFH_Click);
			// 
			// buttonHistogram
			// 
			this->buttonHistogram->Location = System::Drawing::Point(364, 546);
			this->buttonHistogram->Name = L"buttonHistogram";
			this->buttonHistogram->Size = System::Drawing::Size(128, 55);
			this->buttonHistogram->TabIndex = 5;
			this->buttonHistogram->Text = L"Histogram";
			this->buttonHistogram->UseVisualStyleBackColor = true;
			this->buttonHistogram->Click += gcnew System::EventHandler(this, &MyForm::buttonHistogram_Click);
			// 
			// buttonGaussian
			// 
			this->buttonGaussian->Location = System::Drawing::Point(8, 535);
			this->buttonGaussian->Name = L"buttonGaussian";
			this->buttonGaussian->Size = System::Drawing::Size(114, 46);
			this->buttonGaussian->TabIndex = 4;
			this->buttonGaussian->Text = L"Gaussian";
			this->buttonGaussian->UseVisualStyleBackColor = true;
			this->buttonGaussian->Click += gcnew System::EventHandler(this, &MyForm::buttonGaussian_Click);
			// 
			// buttonMedian
			// 
			this->buttonMedian->Location = System::Drawing::Point(8, 484);
			this->buttonMedian->Name = L"buttonMedian";
			this->buttonMedian->Size = System::Drawing::Size(114, 45);
			this->buttonMedian->TabIndex = 3;
			this->buttonMedian->Text = L"Median";
			this->buttonMedian->UseVisualStyleBackColor = true;
			this->buttonMedian->Click += gcnew System::EventHandler(this, &MyForm::buttonMedian_Click);
			// 
			// buttonMean
			// 
			this->buttonMean->Location = System::Drawing::Point(6, 434);
			this->buttonMean->Name = L"buttonMean";
			this->buttonMean->Size = System::Drawing::Size(116, 45);
			this->buttonMean->TabIndex = 2;
			this->buttonMean->Text = L"Mean";
			this->buttonMean->UseVisualStyleBackColor = true;
			this->buttonMean->Click += gcnew System::EventHandler(this, &MyForm::buttonMean_Click);
			// 
			// pBoxFHNew
			// 
			this->pBoxFHNew->BackColor = System::Drawing::Color::LightGray;
			this->pBoxFHNew->Location = System::Drawing::Point(629, 2);
			this->pBoxFHNew->Name = L"pBoxFHNew";
			this->pBoxFHNew->Size = System::Drawing::Size(620, 352);
			this->pBoxFHNew->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pBoxFHNew->TabIndex = 1;
			this->pBoxFHNew->TabStop = false;
			// 
			// pBoxFHOriginal
			// 
			this->pBoxFHOriginal->BackColor = System::Drawing::Color::LightGray;
			this->pBoxFHOriginal->Location = System::Drawing::Point(1, 2);
			this->pBoxFHOriginal->Name = L"pBoxFHOriginal";
			this->pBoxFHOriginal->Size = System::Drawing::Size(620, 352);
			this->pBoxFHOriginal->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pBoxFHOriginal->TabIndex = 0;
			this->pBoxFHOriginal->TabStop = false;
			// 
			// tabPageSegmentation
			// 
			this->tabPageSegmentation->BackColor = System::Drawing::Color::Lavender;
			this->tabPageSegmentation->Controls->Add(this->labelTimer);
			this->tabPageSegmentation->Controls->Add(this->chartSegMahalonobis);
			this->tabPageSegmentation->Controls->Add(this->chartSegOklit);
			this->tabPageSegmentation->Controls->Add(this->chartSegOrj);
			this->tabPageSegmentation->Controls->Add(this->buttonProcess);
			this->tabPageSegmentation->Controls->Add(this->panelRadioButtonImageMode);
			this->tabPageSegmentation->Controls->Add(this->textBoxRenkAdet);
			this->tabPageSegmentation->Controls->Add(this->labelRenkAdet);
			this->tabPageSegmentation->Controls->Add(this->pictureBoxMahalonois);
			this->tabPageSegmentation->Controls->Add(this->labelDosyaYoluSegment);
			this->tabPageSegmentation->Controls->Add(this->textBoxSegment);
			this->tabPageSegmentation->Controls->Add(this->buttonResimSecSegment);
			this->tabPageSegmentation->Controls->Add(this->radioButtonMahalonobis);
			this->tabPageSegmentation->Controls->Add(this->radioButtonOklit);
			this->tabPageSegmentation->Controls->Add(this->pictureBoxOklit);
			this->tabPageSegmentation->Controls->Add(this->pictureBoxSegmentOrj);
			this->tabPageSegmentation->Location = System::Drawing::Point(4, 24);
			this->tabPageSegmentation->Name = L"tabPageSegmentation";
			this->tabPageSegmentation->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSegmentation->Size = System::Drawing::Size(1252, 703);
			this->tabPageSegmentation->TabIndex = 2;
			this->tabPageSegmentation->Text = L"Segmentation";
			// 
			// labelTimer
			// 
			this->labelTimer->AutoSize = true;
			this->labelTimer->Location = System::Drawing::Point(1047, 350);
			this->labelTimer->Name = L"labelTimer";
			this->labelTimer->Size = System::Drawing::Size(0, 15);
			this->labelTimer->TabIndex = 49;
			// 
			// chartSegMahalonobis
			// 
			chartArea6->Name = L"ChartArea1";
			this->chartSegMahalonobis->ChartAreas->Add(chartArea6);
			legend6->Name = L"Legend1";
			this->chartSegMahalonobis->Legends->Add(legend6);
			this->chartSegMahalonobis->Location = System::Drawing::Point(823, 396);
			this->chartSegMahalonobis->Name = L"chartSegMahalonobis";
			series15->ChartArea = L"ChartArea1";
			series15->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StackedColumn;
			series15->Color = System::Drawing::Color::Red;
			series15->IsVisibleInLegend = false;
			series15->Legend = L"Legend1";
			series15->Name = L"redPixelOrj";
			series16->ChartArea = L"ChartArea1";
			series16->Color = System::Drawing::Color::Green;
			series16->IsVisibleInLegend = false;
			series16->Legend = L"Legend1";
			series16->Name = L"greenPixelOrj";
			series17->ChartArea = L"ChartArea1";
			series17->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::StackedColumn;
			series17->Color = System::Drawing::Color::Blue;
			series17->IsVisibleInLegend = false;
			series17->Legend = L"Legend1";
			series17->Name = L"bluePixelOrj";
			series18->ChartArea = L"ChartArea1";
			series18->Color = System::Drawing::Color::Gray;
			series18->IsVisibleInLegend = false;
			series18->Legend = L"Legend1";
			series18->Name = L"intensity";
			this->chartSegMahalonobis->Series->Add(series15);
			this->chartSegMahalonobis->Series->Add(series16);
			this->chartSegMahalonobis->Series->Add(series17);
			this->chartSegMahalonobis->Series->Add(series18);
			this->chartSegMahalonobis->Size = System::Drawing::Size(424, 230);
			this->chartSegMahalonobis->TabIndex = 48;
			this->chartSegMahalonobis->Text = L"chartSegmentation";
			// 
			// chartSegOklit
			// 
			chartArea7->Name = L"ChartArea1";
			this->chartSegOklit->ChartAreas->Add(chartArea7);
			legend7->Name = L"Legend1";
			this->chartSegOklit->Legends->Add(legend7);
			this->chartSegOklit->Location = System::Drawing::Point(409, 396);
			this->chartSegOklit->Name = L"chartSegOklit";
			series19->ChartArea = L"ChartArea1";
			series19->Color = System::Drawing::Color::Red;
			series19->IsVisibleInLegend = false;
			series19->Legend = L"Legend1";
			series19->Name = L"redPixel";
			series19->YValuesPerPoint = 4;
			series20->ChartArea = L"ChartArea1";
			series20->Color = System::Drawing::Color::Green;
			series20->IsVisibleInLegend = false;
			series20->Legend = L"Legend1";
			series20->Name = L"greenPixel";
			series20->YValuesPerPoint = 4;
			series21->ChartArea = L"ChartArea1";
			series21->Color = System::Drawing::Color::Blue;
			series21->IsVisibleInLegend = false;
			series21->Legend = L"Legend1";
			series21->Name = L"bluePixel";
			series21->YValuesPerPoint = 4;
			series22->ChartArea = L"ChartArea1";
			series22->Color = System::Drawing::Color::Gray;
			series22->IsVisibleInLegend = false;
			series22->Legend = L"Legend1";
			series22->Name = L"intensity";
			this->chartSegOklit->Series->Add(series19);
			this->chartSegOklit->Series->Add(series20);
			this->chartSegOklit->Series->Add(series21);
			this->chartSegOklit->Series->Add(series22);
			this->chartSegOklit->Size = System::Drawing::Size(439, 230);
			this->chartSegOklit->TabIndex = 47;
			this->chartSegOklit->Text = L"chartSegmentation";
			// 
			// chartSegOrj
			// 
			chartArea8->Name = L"ChartArea1";
			this->chartSegOrj->ChartAreas->Add(chartArea8);
			legend8->Name = L"Legend1";
			this->chartSegOrj->Legends->Add(legend8);
			this->chartSegOrj->Location = System::Drawing::Point(5, 396);
			this->chartSegOrj->Name = L"chartSegOrj";
			series23->ChartArea = L"ChartArea1";
			series23->Color = System::Drawing::Color::Red;
			series23->IsVisibleInLegend = false;
			series23->Legend = L"Legend1";
			series23->Name = L"redPixel";
			series23->YValuesPerPoint = 6;
			series24->ChartArea = L"ChartArea1";
			series24->Color = System::Drawing::Color::Green;
			series24->IsVisibleInLegend = false;
			series24->Legend = L"Legend1";
			series24->Name = L"greenPixel";
			series24->YValuesPerPoint = 4;
			series25->ChartArea = L"ChartArea1";
			series25->Color = System::Drawing::Color::Blue;
			series25->IsVisibleInLegend = false;
			series25->Legend = L"Legend1";
			series25->Name = L"bluePixel";
			series26->ChartArea = L"ChartArea1";
			series26->Color = System::Drawing::Color::Gray;
			series26->IsVisibleInLegend = false;
			series26->Legend = L"Legend1";
			series26->Name = L"intensity";
			series26->YValuesPerPoint = 4;
			this->chartSegOrj->Series->Add(series23);
			this->chartSegOrj->Series->Add(series24);
			this->chartSegOrj->Series->Add(series25);
			this->chartSegOrj->Series->Add(series26);
			this->chartSegOrj->Size = System::Drawing::Size(426, 230);
			this->chartSegOrj->TabIndex = 46;
			this->chartSegOrj->Text = L"chartSegOrj";
			// 
			// buttonProcess
			// 
			this->buttonProcess->Location = System::Drawing::Point(697, 294);
			this->buttonProcess->Name = L"buttonProcess";
			this->buttonProcess->Size = System::Drawing::Size(220, 78);
			this->buttonProcess->TabIndex = 45;
			this->buttonProcess->Text = L"Hesapla";
			this->buttonProcess->UseVisualStyleBackColor = true;
			this->buttonProcess->Click += gcnew System::EventHandler(this, &MyForm::buttonProcess_Click);
			// 
			// panelRadioButtonImageMode
			// 
			this->panelRadioButtonImageMode->Controls->Add(this->radioButtonIntensity);
			this->panelRadioButtonImageMode->Controls->Add(this->radioButtonRGB);
			this->panelRadioButtonImageMode->Location = System::Drawing::Point(618, 322);
			this->panelRadioButtonImageMode->Name = L"panelRadioButtonImageMode";
			this->panelRadioButtonImageMode->Size = System::Drawing::Size(73, 50);
			this->panelRadioButtonImageMode->TabIndex = 44;
			// 
			// radioButtonIntensity
			// 
			this->radioButtonIntensity->AutoSize = true;
			this->radioButtonIntensity->Location = System::Drawing::Point(3, 3);
			this->radioButtonIntensity->Name = L"radioButtonIntensity";
			this->radioButtonIntensity->Size = System::Drawing::Size(69, 19);
			this->radioButtonIntensity->TabIndex = 39;
			this->radioButtonIntensity->TabStop = true;
			this->radioButtonIntensity->Text = L"Intensity";
			this->radioButtonIntensity->UseVisualStyleBackColor = true;
			// 
			// radioButtonRGB
			// 
			this->radioButtonRGB->AutoSize = true;
			this->radioButtonRGB->Location = System::Drawing::Point(3, 28);
			this->radioButtonRGB->Name = L"radioButtonRGB";
			this->radioButtonRGB->Size = System::Drawing::Size(51, 19);
			this->radioButtonRGB->TabIndex = 40;
			this->radioButtonRGB->TabStop = true;
			this->radioButtonRGB->Text = L"RGB";
			this->radioButtonRGB->UseVisualStyleBackColor = true;
			// 
			// textBoxRenkAdet
			// 
			this->textBoxRenkAdet->Location = System::Drawing::Point(927, 351);
			this->textBoxRenkAdet->Name = L"textBoxRenkAdet";
			this->textBoxRenkAdet->Size = System::Drawing::Size(38, 21);
			this->textBoxRenkAdet->TabIndex = 42;
			// 
			// labelRenkAdet
			// 
			this->labelRenkAdet->AutoSize = true;
			this->labelRenkAdet->Location = System::Drawing::Point(924, 327);
			this->labelRenkAdet->Name = L"labelRenkAdet";
			this->labelRenkAdet->Size = System::Drawing::Size(66, 15);
			this->labelRenkAdet->TabIndex = 41;
			this->labelRenkAdet->Text = L"Renk Adeti";
			// 
			// pictureBoxMahalonois
			// 
			this->pictureBoxMahalonois->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxMahalonois->Location = System::Drawing::Point(837, 3);
			this->pictureBoxMahalonois->Name = L"pictureBoxMahalonois";
			this->pictureBoxMahalonois->Size = System::Drawing::Size(410, 282);
			this->pictureBoxMahalonois->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxMahalonois->TabIndex = 37;
			this->pictureBoxMahalonois->TabStop = false;
			// 
			// labelDosyaYoluSegment
			// 
			this->labelDosyaYoluSegment->Location = System::Drawing::Point(6, 287);
			this->labelDosyaYoluSegment->Name = L"labelDosyaYoluSegment";
			this->labelDosyaYoluSegment->Size = System::Drawing::Size(310, 23);
			this->labelDosyaYoluSegment->TabIndex = 36;
			this->labelDosyaYoluSegment->Text = L"Resim sec";
			this->labelDosyaYoluSegment->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBoxSegment
			// 
			this->textBoxSegment->Location = System::Drawing::Point(6, 317);
			this->textBoxSegment->Name = L"textBoxSegment";
			this->textBoxSegment->Size = System::Drawing::Size(310, 21);
			this->textBoxSegment->TabIndex = 34;
			this->textBoxSegment->Text = L"Dosya Yolu";
			this->textBoxSegment->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonResimSecSegment
			// 
			this->buttonResimSecSegment->Location = System::Drawing::Point(322, 290);
			this->buttonResimSecSegment->Name = L"buttonResimSecSegment";
			this->buttonResimSecSegment->Size = System::Drawing::Size(93, 50);
			this->buttonResimSecSegment->TabIndex = 33;
			this->buttonResimSecSegment->Text = L"Resim Seç";
			this->buttonResimSecSegment->UseVisualStyleBackColor = true;
			this->buttonResimSecSegment->Click += gcnew System::EventHandler(this, &MyForm::buttonResimSecSegment_Click);
			// 
			// radioButtonMahalonobis
			// 
			this->radioButtonMahalonobis->AutoSize = true;
			this->radioButtonMahalonobis->Location = System::Drawing::Point(964, 291);
			this->radioButtonMahalonobis->Name = L"radioButtonMahalonobis";
			this->radioButtonMahalonobis->Size = System::Drawing::Size(144, 19);
			this->radioButtonMahalonobis->TabIndex = 32;
			this->radioButtonMahalonobis->Text = L"Mahalonobis Uzaklýðý";
			this->radioButtonMahalonobis->UseVisualStyleBackColor = true;
			// 
			// radioButtonOklit
			// 
			this->radioButtonOklit->AutoSize = true;
			this->radioButtonOklit->Checked = true;
			this->radioButtonOklit->Location = System::Drawing::Point(551, 291);
			this->radioButtonOklit->Name = L"radioButtonOklit";
			this->radioButtonOklit->Size = System::Drawing::Size(96, 19);
			this->radioButtonOklit->TabIndex = 31;
			this->radioButtonOklit->TabStop = true;
			this->radioButtonOklit->Text = L"Öklit Uzaklýðý";
			this->radioButtonOklit->UseVisualStyleBackColor = true;
			// 
			// pictureBoxOklit
			// 
			this->pictureBoxOklit->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxOklit->Location = System::Drawing::Point(421, 3);
			this->pictureBoxOklit->Name = L"pictureBoxOklit";
			this->pictureBoxOklit->Size = System::Drawing::Size(410, 282);
			this->pictureBoxOklit->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxOklit->TabIndex = 30;
			this->pictureBoxOklit->TabStop = false;
			// 
			// pictureBoxSegmentOrj
			// 
			this->pictureBoxSegmentOrj->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxSegmentOrj->Location = System::Drawing::Point(5, 3);
			this->pictureBoxSegmentOrj->Name = L"pictureBoxSegmentOrj";
			this->pictureBoxSegmentOrj->Size = System::Drawing::Size(410, 281);
			this->pictureBoxSegmentOrj->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxSegmentOrj->TabIndex = 29;
			this->pictureBoxSegmentOrj->TabStop = false;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textBoxTHigh);
			this->tabPage1->Controls->Add(this->textBoxTLow);
			this->tabPage1->Controls->Add(this->pictureBoxCannyNew);
			this->tabPage1->Controls->Add(this->pictureBoxCannyGradient);
			this->tabPage1->Controls->Add(this->pictureBoxCannyOrj);
			this->tabPage1->Controls->Add(this->buttonCannyHough);
			this->tabPage1->Controls->Add(this->labelDosyaYoluCanny);
			this->tabPage1->Controls->Add(this->textBoxDosyaYoluCanny);
			this->tabPage1->Controls->Add(this->buttonResimSecCanny);
			this->tabPage1->Location = System::Drawing::Point(4, 24);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1252, 703);
			this->tabPage1->TabIndex = 3;
			this->tabPage1->Text = L"Canny-Hough";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// textBoxTHigh
			// 
			this->textBoxTHigh->Location = System::Drawing::Point(440, 570);
			this->textBoxTHigh->Name = L"textBoxTHigh";
			this->textBoxTHigh->Size = System::Drawing::Size(100, 21);
			this->textBoxTHigh->TabIndex = 45;
			this->textBoxTHigh->Text = L"THigh";
			// 
			// textBoxTLow
			// 
			this->textBoxTLow->Location = System::Drawing::Point(440, 533);
			this->textBoxTLow->Name = L"textBoxTLow";
			this->textBoxTLow->Size = System::Drawing::Size(100, 21);
			this->textBoxTLow->TabIndex = 44;
			this->textBoxTLow->Text = L"TLow";
			// 
			// pictureBoxCannyNew
			// 
			this->pictureBoxCannyNew->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxCannyNew->Location = System::Drawing::Point(838, 6);
			this->pictureBoxCannyNew->Name = L"pictureBoxCannyNew";
			this->pictureBoxCannyNew->Size = System::Drawing::Size(410, 453);
			this->pictureBoxCannyNew->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxCannyNew->TabIndex = 43;
			this->pictureBoxCannyNew->TabStop = false;
			// 
			// pictureBoxCannyGradient
			// 
			this->pictureBoxCannyGradient->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxCannyGradient->Location = System::Drawing::Point(422, 6);
			this->pictureBoxCannyGradient->Name = L"pictureBoxCannyGradient";
			this->pictureBoxCannyGradient->Size = System::Drawing::Size(410, 453);
			this->pictureBoxCannyGradient->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxCannyGradient->TabIndex = 42;
			this->pictureBoxCannyGradient->TabStop = false;
			// 
			// pictureBoxCannyOrj
			// 
			this->pictureBoxCannyOrj->BackColor = System::Drawing::Color::LightGray;
			this->pictureBoxCannyOrj->Location = System::Drawing::Point(6, 6);
			this->pictureBoxCannyOrj->Name = L"pictureBoxCannyOrj";
			this->pictureBoxCannyOrj->Size = System::Drawing::Size(410, 452);
			this->pictureBoxCannyOrj->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxCannyOrj->TabIndex = 41;
			this->pictureBoxCannyOrj->TabStop = false;
			// 
			// buttonCannyHough
			// 
			this->buttonCannyHough->Location = System::Drawing::Point(440, 461);
			this->buttonCannyHough->Name = L"buttonCannyHough";
			this->buttonCannyHough->Size = System::Drawing::Size(90, 55);
			this->buttonCannyHough->TabIndex = 40;
			this->buttonCannyHough->Text = L"Canny-Hough";
			this->buttonCannyHough->UseVisualStyleBackColor = true;
			this->buttonCannyHough->Click += gcnew System::EventHandler(this, &MyForm::buttonCannyHough_Click);
			// 
			// labelDosyaYoluCanny
			// 
			this->labelDosyaYoluCanny->Location = System::Drawing::Point(6, 461);
			this->labelDosyaYoluCanny->Name = L"labelDosyaYoluCanny";
			this->labelDosyaYoluCanny->Size = System::Drawing::Size(310, 23);
			this->labelDosyaYoluCanny->TabIndex = 39;
			this->labelDosyaYoluCanny->Text = L"Resim sec";
			this->labelDosyaYoluCanny->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBoxDosyaYoluCanny
			// 
			this->textBoxDosyaYoluCanny->Location = System::Drawing::Point(6, 491);
			this->textBoxDosyaYoluCanny->Name = L"textBoxDosyaYoluCanny";
			this->textBoxDosyaYoluCanny->Size = System::Drawing::Size(310, 21);
			this->textBoxDosyaYoluCanny->TabIndex = 38;
			this->textBoxDosyaYoluCanny->Text = L"Dosya Yolu";
			this->textBoxDosyaYoluCanny->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonResimSecCanny
			// 
			this->buttonResimSecCanny->Location = System::Drawing::Point(322, 464);
			this->buttonResimSecCanny->Name = L"buttonResimSecCanny";
			this->buttonResimSecCanny->Size = System::Drawing::Size(93, 50);
			this->buttonResimSecCanny->TabIndex = 37;
			this->buttonResimSecCanny->Text = L"Resim Seç";
			this->buttonResimSecCanny->UseVisualStyleBackColor = true;
			this->buttonResimSecCanny->Click += gcnew System::EventHandler(this, &MyForm::buttonResimSecCanny_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 652);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPageCemberCiz->ResumeLayout(false);
			this->tabPageCemberCiz->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCember))->EndInit();
			this->tabPageFilterHisogram->ResumeLayout(false);
			this->tabPageFilterHisogram->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartHistogram))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBoxFHNew))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBoxFHOriginal))->EndInit();
			this->tabPageSegmentation->ResumeLayout(false);
			this->tabPageSegmentation->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegMahalonobis))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegOklit))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartSegOrj))->EndInit();
			this->panelRadioButtonImageMode->ResumeLayout(false);
			this->panelRadioButtonImageMode->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxMahalonois))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxOklit))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxSegmentOrj))->EndInit();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyNew))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyGradient))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCannyOrj))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	public: 
	Resim ^ MyForm::resim = gcnew Resim();
	Islemler MyForm::islem;
	System::Boolean MyForm::degerOku(int * row, int * column, double * sigma, String ^ filtreTip);
	System::Void MyForm::filtreUygula(String ^ filtreTip);
	System::Void MyForm::resimYukle(Label ^ labelDosyaYolu, TextBox ^ textBoxKayitYolu, PictureBox ^ picturebox);
	System::Void MyForm::bmpIntesity(TextBox ^ textBoxKayitYolu,
									 PictureBox ^ pictureBoxIntensity,
									 Label ^ labelDosyaYolu);
	// buttons
	System::Void MyForm::buttonCemberCiz_Click_1(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonResimSec_Click_1(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::bmpIntensityButton_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonResimSecFH_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonBmpIntensityFH_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void MyForm::buttonMean_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonMedian_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonGaussian_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonHistogram_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonBlackWhite_Click(System::Object^  sender, System::EventArgs^  e);
	
	System::Void MyForm::buttonResimSecSegment_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonProcess_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonResimSecCanny_Click(System::Object^  sender, System::EventArgs^  e);
	System::Void MyForm::buttonCannyHough_Click(System::Object^  sender, System::EventArgs^  e);
};
}
