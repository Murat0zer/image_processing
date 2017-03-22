#include "MyForm.h"
#include "stdafx.h"
// Image_Process1.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <math.h>
#include <msclr\marshal.h>
#include <vector>
#include <chrono>  // for high_resolution_clock
//User defined includes
#include "imge_bmp.h"
#include "islemler.h"
#include "Resim.h"
#include "Vertex.h"
using namespace MyVector;
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace CppWinForm2;
using namespace msclr::interop;

[STAThread]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CppWinForm2::MyForm form;
	Application::Run(%form);
}

LPCTSTR stringToLPCTSTR(String ^ string)
{
	marshal_context context;
	LPCTSTR lpcstr = context.marshal_as<const TCHAR*>(string);
	return lpcstr;
}

System::Void MyForm::resimYukle(Label ^ labelDosyaYolu, TextBox ^ textBoxKayitYolu, PictureBox ^ picturebox)
{
	OpenFileDialog  dlg;
	dlg.Title = "Open Image";
	dlg.Filter = "bmp files (*.bmp)|*.bmp";

	if (dlg.ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		// resmin kopyasini bellege alir.
		picturebox->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(dlg.FileName)));

		resim->setInput(stringToLPCTSTR(dlg.FileName));

		resim->setBuffer(LoadBMP(
			resim->getWidth(),
			resim->getHeight(),
			resim->getSize(),
			stringToLPCTSTR(dlg.FileName)));
		//dosya yollarini gunceller.
		labelDosyaYolu->Text = dlg.FileName;
		textBoxKayitYolu->Text = dlg.FileName;
		//resmi raw image haline getiriyoruz.
		resim->setRawIntensity(ConvertBMPToIntensity(
			resim->getBuffer(),
			*resim->getWidth(),
			*resim->getHeight()));
		resim->setOutput(stringToLPCTSTR(textBox1->Text));
	}
}

System::Void MyForm::bmpIntesity(TextBox ^ textBoxKayitYolu, PictureBox ^ pictureBoxIntensity, Label^ labelDosyaYolu)
{
	// orjinal resmi yukluyoruz.
	resim->setBuffer(LoadBMP(
		resim->getWidth(),
		resim->getHeight(),
		resim->getSize(),
		stringToLPCTSTR(labelDosyaYolu->Text)));

	resim->setRawIntensity(ConvertBMPToIntensity(
		resim->getBuffer(),
		*resim->getWidth(),
		*resim->getHeight()));

	resim->setDisplayImage(ConvertIntensityToBMP(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		resim->getNewSize()));

	resim->setOutput(stringToLPCTSTR(textBoxKayitYolu->Text));

	if (!SaveBMP(resim->getDisplayImage(),
		*resim->getWidth(),
		*resim->getHeight(),
		*resim->getNewSize(),
		stringToLPCTSTR(textBoxKayitYolu->Text)))
	{
		MessageBox::Show("islem basarisiz"); return;
	}
	Image ^ img = Image::FromStream(gcnew MemoryStream(File::ReadAllBytes(textBoxKayitYolu->Text)));
	pictureBoxIntensity->Image = img;
	resim->setInput(resim->getOutput());
}

System::Void MyForm::buttonResimSec_Click_1(System::Object^  sender, System::EventArgs^  e) {
	resimYukle(labelDosyaYolu, textBox1, pictureBoxCember);	
}

System::Void MyForm::bmpIntensityButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{	
	bmpIntesity(textBox1, pictureBoxCember,labelDosyaYolu);
	// dosya yollarini gunceller.
	labelDosyaYolu->Text = textBox1->Text;
	resim->setInput(resim->getOutput());
}


System::Void MyForm::buttonCemberCiz_Click_1(System::Object^  sender, System::EventArgs^  e) {
	int  cemberX, cemberY; double yaricap;
	try 
	{
	  cemberX = System::Convert::ToInt32(Xkord_textBox->Text);
	  cemberY = System::Convert::ToInt32(YKord_textBox->Text);
	  yaricap = System::Convert::ToDouble(yariCap_textBox->Text);
	}
	catch (FormatException ^ e)
	{
		MessageBox::Show("Geçersiz Deðer"); return;
	}

	islem.daireCiz(resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		cemberX,
		cemberY,
		yaricap);

	resim->setDisplayImage(ConvertIntensityToBMP(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		resim->getNewSize()));

	resim->setOutput (stringToLPCTSTR(textBox1->Text)); // gereksiz

	if (!SaveBMP(resim->getDisplayImage(),
		*resim->getWidth(),
		*resim->getHeight(),
		*resim->getNewSize(),
		resim->getOutput()))
	{
		MessageBox::Show("islem basarisiz"); return;
	}	
	pictureBoxCember->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBox1->Text)));
	labelDosyaYolu->Text = textBox1->Text;
	resim->setOutput(stringToLPCTSTR(textBox1->Text));
}// cember cizdirme


 ////###############################################################################################
 //// Filter-Histogram Kodlari #####################################################################
 ////###############################################################################################
System::Void CppWinForm2::MyForm::buttonResimSecFH_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	resimYukle(labelDosyaYoluFH, textBoxKayitYoluFH, pBoxFHOriginal);
}
System::Void CppWinForm2::MyForm::buttonBmpIntensityFH_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	bmpIntesity(textBoxKayitYoluFH, pBoxFHNew, labelDosyaYoluFH);
}

System::Boolean CppWinForm2::MyForm::degerOku(int * row , int * column, float *sigma, String ^ filtreTip)
{
	try
	{
		*row = System::Convert::ToInt32(textBoxMatris->Text);
		*column = System::Convert::ToInt32(textBoxMatris->Text);
		if (filtreTip == "Gaussian")
			*sigma = (float)(Convert::ToDouble(textBoxSigma->Text));
	}
	catch (FormatException ^ e)
	{
		MessageBox::Show("Geçersiz Deðer"); return false;
	}
	return true;
}

System::Void CppWinForm2::MyForm::filtreUygula(String ^ filtreTip)
{
	int row, column; float sigma;
	if (!degerOku(&row, &column, &sigma, filtreTip))
		return;
	resim->setRawIntensity(islem.filtreUygula(resim->getRawIntensity(),
		resim->getWidth(),
		resim->getHeight(),
		filtreTip,
		row,
		column,
		sigma));

	resim->setDisplayImage(ConvertIntensityToBMP(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		resim->getNewSize()));

	resim->setOutput(stringToLPCTSTR(textBoxKayitYoluFH->Text));

	if (!SaveBMP(resim->getDisplayImage(),
		*resim->getWidth(),
		*resim->getHeight(),
		*resim->getNewSize(),
		stringToLPCTSTR(textBoxKayitYoluFH->Text)))
	{
		MessageBox::Show("islem basarisiz"); return;
	}
	pBoxFHNew->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxKayitYoluFH->Text)));
	resim->setOutput(stringToLPCTSTR(textBoxKayitYoluFH->Text));
}

System::Void CppWinForm2::MyForm::buttonMean_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	filtreUygula("Mean");
}

System::Void CppWinForm2::MyForm::buttonMedian_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	filtreUygula("Median");
}

System::Void CppWinForm2::MyForm::buttonGaussian_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	filtreUygula("Gaussian");
}

System::Void CppWinForm2::MyForm::buttonHistogram_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	vector<Vertex*>  histogram;       
	// histogram degerlerini hesapliyoruz.
	histogram = islem.histogramHesapla(resim->getRawIntensity(), *resim->getWidth(), *resim->getHeight(), "intensity");
	// histogrami cizdirme
	islem.histogramCiz(histogram, chartHistogram, "intensity");
}

System::Void CppWinForm2::MyForm::buttonBlackWhite_Click(System::Object ^ sender, System::EventArgs ^ e)
{	
	 /*histogram degerlerini hesapliyoruz.*/
	vector<Vertex*>  histogram;
	histogram = islem.histogramHesapla(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		"intensity");

	resim->setRawIntensity(islem.siyahBeyaz(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		histogram));

	resim->setDisplayImage(ConvertIntensityToBMP(
		resim->getRawIntensity(),
		*resim->getWidth(),
		*resim->getHeight(),
		resim->getNewSize()));

	resim->setOutput(stringToLPCTSTR(textBoxKayitYoluFH->Text));

	if (!SaveBMP(resim->getDisplayImage(),
		*resim->getWidth(), 
		*resim->getHeight(), 
		*resim->getNewSize(),
		stringToLPCTSTR(textBoxKayitYoluFH->Text)))
	{
		MessageBox::Show("islem basarisiz"); return;
	}
	pBoxFHNew->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxKayitYoluFH->Text)));
	resim->setOutput(stringToLPCTSTR(textBoxKayitYoluFH->Text));
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////Segmentation///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Void CppWinForm2::MyForm::buttonResimSecSegment_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	resimYukle(labelDosyaYoluSegment, textBoxSegment, pictureBoxSegmentOrj);
}

System::Void CppWinForm2::MyForm::buttonProcess_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double>  elapsed;
	int renkAdet = 2;
	try {
		 renkAdet = Convert::ToInt32(textBoxRenkAdet->Text);
	}
	catch (FormatException ^e) {
		MessageBox::Show("Gecersiz deger");
	}
	vector<Vertex*>  histogram;
	histogram = islem.histogramHesapla(resim->getBuffer(), *resim->getWidth(), *resim->getHeight(), "rgb");
	islem.histogramCiz(histogram, chartSegOrj, "rgb");
	
	if (radioButtonRGB->Checked)
	{		
		
		if (radioButtonOklit->Checked)
		{
			BYTE * buffer;
			vector<vector<int>> thresholds = islem.calculateRgbOklitThreshold(histogram, renkAdet);
			
			buffer = islem.thresholdBasedSegmentationRGB(
				resim->getBuffer(),
				thresholds,
				*resim->getHeight(),
				*resim->getWidth());
			long  newSize = (*resim->getWidth() * *resim->getHeight() * 3);
			if (!SaveBMP(buffer,
				*resim->getWidth(),
				*resim->getHeight(),
				newSize,
				stringToLPCTSTR(textBoxSegment->Text)))
			{
				MessageBox::Show("islem basarisiz"); return;
			}
			pictureBoxOklit->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxSegment->Text)));
			resim->setOutput(stringToLPCTSTR(textBoxSegment->Text));
			histogram = islem.histogramHesapla(buffer, *resim->getWidth(), *resim->getHeight(), "rgb");
			islem.histogramCiz(histogram, chartSegOklit, "rgb");
		}
		if (radioButtonMahalonobis->Checked)
		{

		}
	}
	if (radioButtonIntensity->Checked)
	{
		resim->setRawIntensity(ConvertBMPToIntensity(
			resim->getBuffer(),
			*resim->getWidth(),
			*resim->getHeight()));

		histogram = islem.histogramHesapla(
			resim->getRawIntensity(),
			*resim->getWidth(),
			*resim->getHeight(),
			"intensity");

		if (radioButtonOklit->Checked)
		{
			vector<int> thresholds = islem.calculateIntensityOklitThreshold(histogram, renkAdet);

			islem.thresholdBasedSegmentationIntensity(
				resim->getRawIntensity(),
				thresholds,
				*resim->getHeight(),
				*resim->getWidth());
			resim->setDisplayImage(ConvertIntensityToBMP(
				resim->getRawIntensity(),
				*resim->getWidth(),
				*resim->getHeight(),
				resim->getNewSize()));

			if (!SaveBMP(resim->getDisplayImage(),
				*resim->getWidth(),
				*resim->getHeight(),
				*resim->getNewSize(),
				stringToLPCTSTR(textBoxSegment->Text)))
			{
				MessageBox::Show("islem basarisiz"); return;
			}
			pictureBoxOklit->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxSegment->Text)));
			resim->setOutput(stringToLPCTSTR(textBoxSegment->Text));
			histogram = islem.histogramHesapla(resim->getRawIntensity(), *resim->getWidth(), *resim->getHeight(), "intensity");
			islem.histogramCiz(histogram, chartSegOklit, "intensity");

		}
		if (radioButtonMahalonobis->Checked)
		{

		}
	}
	
	auto finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	labelTimer->Text = Convert::ToString(elapsed.count()) +  " saniyede  bitirildi.";
}


