#include "MyForm.h"
#include "stdafx.h"
// Image_Process1.cpp : Defines the entry point for the console application.
//
#define _USE_MATH_DEFINES
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
		MessageBox::Show("Ge�ersiz De�er"); return;
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

System::Boolean CppWinForm2::MyForm::degerOku(int * row , int * column, double *sigma, String ^ filtreTip)
{
	try
	{
		*row = System::Convert::ToInt32(textBoxMatris->Text);
		*column = System::Convert::ToInt32(textBoxMatris->Text);
		if (filtreTip == "Gaussian")
			*sigma = (double)(Convert::ToDouble(textBoxSigma->Text));
	}
	catch (FormatException ^ e)
	{
		MessageBox::Show("Ge�ersiz De�er"); return false;
	}
	return true;
}

System::Void CppWinForm2::MyForm::filtreUygula(String ^ filtreTip)
{
	int row, column; double sigma;
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
	vector<MATRIX*> inverCovariances;
	for (int i = 0; i < renkAdet; i++)
		inverCovariances.push_back(new MATRIX(3, 3));
	vector<Vertex*>  histogram;
	histogram = islem.histogramHesapla(resim->getBuffer(), *resim->getWidth(), *resim->getHeight(), "rgb");
	islem.histogramCiz(histogram, chartSegOrj, "rgb");
	
	vector<Vertex*> agirlikMerkezleri;
	BYTE * buffer;
	if (radioButtonRGB->Checked)
	{		
		if (radioButtonOklit->Checked)
		{			
			agirlikMerkezleri = islem.calculateRGBThreshold(histogram, renkAdet, "oklit", inverCovariances);
			
			buffer = islem.thresholdBasedSegmentationRGB(
				resim->getBuffer(),
				agirlikMerkezleri,
				*resim->getHeight(),
				*resim->getWidth(),
				histogram,
				"oklit",
				inverCovariances);
		}
		if (radioButtonMahalonobis->Checked)
		{			
			agirlikMerkezleri = islem.calculateRGBThreshold(histogram, renkAdet, "mah", inverCovariances);

			buffer = islem.thresholdBasedSegmentationRGB(
				resim->getBuffer(),
				agirlikMerkezleri,
				*resim->getHeight(),
				*resim->getWidth(),
				histogram,
				"mah",
				inverCovariances);
		}
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
			vector<Vertex*> thresholds = islem.calculateIntensityThreshold(histogram, renkAdet, "oklit");

			islem.thresholdBasedSegmentationIntensity(
				resim->getRawIntensity(),
				thresholds,
				*resim->getHeight(),
				*resim->getWidth(),
				histogram);
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

System::Void CppWinForm2::MyForm::buttonResimSecCanny_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	resimYukle(labelDosyaYoluCanny, textBoxDosyaYoluCanny, pictureBoxCannyOrj);
}

System::Void CppWinForm2::MyForm::buttonCannyHough_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	pictureBoxCannyOrj->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(labelDosyaYoluCanny->Text)));
	
	resim->setBuffer(LoadBMP(
		resim->getWidth(),
		resim->getHeight(),
		resim->getSize(),
		stringToLPCTSTR(labelDosyaYoluCanny->Text)));

	// resim intensity.
	resim->setRawIntensity(ConvertBMPToIntensity(
		resim->getBuffer(),
		*resim->getWidth(),
		*resim->getHeight()));

	// gurultu kaldirma icin gauss filter
	resim->setRawIntensity(islem.filtreUygula(resim->getRawIntensity(),
		resim->getWidth(),
		resim->getHeight(),
		"Gaussian",
		3,
		3,
		1.0));

	
	/////edge detect hough kismi///////////
	MATRIX gradientMatrix(*resim->getHeight() - 2, *resim->getWidth() - 2);
	MATRIX cannyMatrix(*resim->getHeight() - 2, *resim->getWidth() - 2);
	MATRIX gradientBinaryMatrix(*resim->getHeight() - 2, *resim->getWidth() - 2);
	MATRIX angleMatrix(*resim->getHeight() - 2, *resim->getWidth() - 2);
	MATRIX angleMatrixDegree(*resim->getHeight() - 2, *resim->getWidth() - 2);
	MATRIX filtreX(3, 3);
	filtreX.Set(1, 1, -1); filtreX.Set(1, 2, -2); filtreX.Set(1, 3, -1);
	filtreX.Set(2, 1,  0); filtreX.Set(2, 2,  0); filtreX.Set(2, 3,  0);
	filtreX.Set(3, 1,  1); filtreX.Set(3, 2,  2); filtreX.Set(3, 3,  1);

	MATRIX filtreY(3, 3);
	filtreY.Set(1, 1, -1); filtreY.Set(1, 2, 0); filtreY.Set(1, 3, 1);
	filtreY.Set(2, 1, -2); filtreY.Set(2, 2, 0); filtreY.Set(2, 3, 2);
	filtreY.Set(3, 1, -1); filtreY.Set(3, 2, 0); filtreY.Set(3, 3, 1);

	long pozisyon;
	int sinir = (3 - 1) / 2;
	BYTE * buffer = resim->getRawIntensity();
	// yeni resmin boyutu.
	BYTE * newBufferGradient = new BYTE[(*resim->getWidth() - 2 * sinir) * (*resim->getHeight() - 2 * sinir)];
	BYTE * newBufferCanny	 = new BYTE[(*resim->getWidth() - 2 * sinir) * (*resim->getHeight() - 2 * sinir)];
	//// gradient hesabi////
	double newX = 0;
	double newY = 0;
	for (int row = sinir; row < *resim->getHeight() - sinir; row++)				  // Resmin pixellerini dolasmak
		for (int column = sinir; column < *resim->getWidth() - sinir; column++) // icin gerekli.
		{		
			newX = 0; newY = 0;
			for (int filterRow = 0; filterRow < 3; filterRow++)
				for (int filterColumn = 0; filterColumn < 3; filterColumn++)
				{
					// resimdeki filtre matrisine denk gelen pixel degerlerinin pozisyonu.
					pozisyon = (row - sinir + filterRow) * (*resim->getWidth()) + column - sinir + filterColumn;
					// gradient fln.
					newX += filtreX.Get(filterRow + 1, filterColumn + 1) * buffer[pozisyon];
					newY += filtreY.Get(filterRow + 1, filterColumn + 1) * buffer[pozisyon];
					
				}
			double angle = 0;
			// yeni resimde pixelin nerde olacaginin hesaplanmasi. 
			pozisyon = (row - sinir) * (*resim->getWidth() - 2 * sinir) + column - sinir;
			if (newX != 0) { angle = Math::Atan2(newX, newY); }
			angleMatrix.Set(row, column, angle);
			double gradientValue = Math::Sqrt(Math::Pow(newY, 2.0) + Math::Pow(newX, 2.0));
			gradientMatrix.Set(row, column, gradientValue );
			cannyMatrix.Set(row, column, gradientValue);
			newBufferGradient[pozisyon] = gradientMatrix.Get(row, column);
			newBufferCanny[pozisyon]    = gradientMatrix.Get(row, column);
		}
	//// gradient hesabi////-----------
		
	/////////// direk gradient ile cannysiz  hough icin binary yapalim//////
	vector<Vertex*>  histogram;
	histogram = islem.histogramHesapla(
		newBufferGradient,
		*resim->getWidth() -2,
		*resim->getHeight() -2,
		"intensity");
	resim->setRawIntensity(islem.siyahBeyaz(
		newBufferGradient,
		*resim->getWidth() - 2,
		*resim->getHeight() - 2,
		histogram));
	//// binary degerleri matrise atiyoruz.
	for (int row = sinir; row < *resim->getHeight() - sinir; row++)				  // Resmin pixellerini dolasmak
		for (int column = sinir; column < *resim->getWidth() - sinir; column++) // icin gerekli.
		{
			pozisyon = (row - sinir) * (*resim->getWidth() - 2 * sinir) + column - sinir;
			gradientBinaryMatrix.Set(row, column, newBufferGradient[pozisyon]);
		}
	/////////// direk gradient ile cannysiz  edge detect//////

	///////canny kismi///////// 
	//non-max sup//
	for (int row = 1; row <= cannyMatrix.getRow(); row++)
		for (int column = 1; column <= cannyMatrix.getColumn(); column++)
		{
			double angle = 180.0/M_PI  * angleMatrix.Get(row, column);
			
			if (((angle <= 22.5) && (angle >= -22.5)) || (angle >= 157.5) || (angle <= -157.5)) // 0
			{
				angleMatrixDegree.Set(row, column, 0);
				bool a = false;
				bool b = false;
				if (column - 1 == 0) // sol tarafta eleman yok kontrol etme.
					 a = cannyMatrix.Get(row, column) < cannyMatrix.Get(row, column + 1);
				if (column + 1 > cannyMatrix.getColumn()) // sag tarafta eleman yok/
					 b = cannyMatrix.Get(row, column) < cannyMatrix.Get(row, column - 1);
				if (column - 1 != 0 && column + 1 <= cannyMatrix.getColumn()) // iki tarafi da kontrol et
				{
					a = cannyMatrix.Get(row, column) < cannyMatrix.Get(row, column + 1);
					b = cannyMatrix.Get(row, column) < cannyMatrix.Get(row, column - 1);
				}				
				if(a || b)
					cannyMatrix.Set(row, column, 0);
			}
			
			if (((angle >= 22.5) && (angle <= 67.5)) || ((angle <= -112.5) && (angle >= -157.5))) // 45
			{
				angleMatrixDegree.Set(row, column, 45);
				bool a = false;
				bool b = false;
				if (row - 1 > 0 && column - 1 > 0) // kuzey bati eleman kontrol.
					a = cannyMatrix.Get(row, column) < cannyMatrix.Get(row - 1, column - 1);

				if (row + 1 <= cannyMatrix.getRow() && column + 1 <= cannyMatrix.getColumn()) // guney dogu eleman kontrol /
					b = cannyMatrix.Get(row, column) < cannyMatrix.Get(row + 1, column - 1);

				if (a || b)
					cannyMatrix.Set(row, column, 0);
			}
			if (((angle >= 67.5) && (angle <= 112.5)) || ((angle <= -67.5) && (angle >= -112.5))) // 90
			{
				angleMatrixDegree.Set(row, column, 90);
				bool a = false;
				bool b = false;
				if (row - 1 > 0 ) // kuzey  eleman kontrol.
					a = cannyMatrix.Get(row, column) < cannyMatrix.Get(row - 1, column);

				if (row + 1 <= cannyMatrix.getRow()) // guney  eleman kontrol /
					b = cannyMatrix.Get(row, column) < cannyMatrix.Get(row + 1, column);

				if (a || b)
					cannyMatrix.Set(row, column, 0);
			}
			if (((angle >= 112.5) && (angle <= 157.5)) || ((angle <= -22.5) && (angle >= -67.5))) // 135
			{
				angleMatrixDegree.Set(row, column, 135);
				bool a = false;
				bool b = false;
				if (row - 1 > 0 && column + 1 <= cannyMatrix.getColumn()) // kuzey dogu eleman kontrol.
					a = cannyMatrix.Get(row, column) < cannyMatrix.Get(row - 1, column + 1);

				if (row + 1 <= cannyMatrix.getRow() && column - 1 > 0) // guney bati eleman kontrol /
					b = cannyMatrix.Get(row, column) < cannyMatrix.Get(row + 1, column - 1);

				if (a || b)
					cannyMatrix.Set(row, column, 0);
			}
		}
	
	// histerize threshold
	int tLow = Convert::ToInt32(textBoxTLow->Text);
	int tHigh = Convert::ToInt32(textBoxTHigh->Text);

	for (int row = 1; row <= cannyMatrix.getRow(); row++)
		for (int column = 1; column <= cannyMatrix.getColumn(); column++)
		{
			if (cannyMatrix.Get(row, column) >= tHigh)
				cannyMatrix.Set(row, column, 255);
			if (cannyMatrix.Get(row, column) <= tLow)
				cannyMatrix.Set(row, column, 0);
		}
	// tlow thigh arasi degerleri kenar yonundeki pixel degerlerine bakarak degistiriyoruz.
	for (int row = 1; row <= cannyMatrix.getRow(); row++)
		for (int column = 1; column <= cannyMatrix.getColumn(); column++)
		{
			int gradientAngle = angleMatrixDegree.Get(row, column);
			int value = cannyMatrix.Get(row, column);
			if (value > 0 && value < 255)
			{	
				if (gradientAngle == 0)  // 0 a 90 dik
				{
					bool a = false;
					bool b = false;
					if (row - 1 > 0) // kuzey  eleman kontrol.
						a = cannyMatrix.Get(row - 1, column) == 255;
					if (row + 1 <= cannyMatrix.getRow()) // guney  eleman kontrol /
						//b = cannyMatrix.Get(row + 1, column) == 255;

					if (a || b)
						cannyMatrix.Set(row, column, 255);
					else
						cannyMatrix.Set(row, column, 0);
				}

				if (gradientAngle == 135)  // 135e 45 dik
				{
					bool a = false;
					bool b = false;
					if (row - 1 > 0 && column + 1 <= cannyMatrix.getColumn()) // kuzey dogu.
						a = cannyMatrix.Get(row - 1, column + 1) == 255;
					if (row + 1 < cannyMatrix.getRow() && column - 1 > 0) // guney bati
						//b = cannyMatrix.Get(row + 1, column - 1) == 255;

					if (a || b)
						cannyMatrix.Set(row, column, 255);
					else
						cannyMatrix.Set(row, column, 0);
				}
				if (gradientAngle == 0) // 90a 0 dik.
				{
					bool a = false;
					bool b = false;
					if (column - 1 > 0 ) // sol eleman
						//a = cannyMatrix.Get(row , column - 1) == 255;
					if ( column + 1 <= cannyMatrix.getColumn()) // sag eleman.
						b = cannyMatrix.Get(row, column + 1) == 255;

					if (a || b)
						cannyMatrix.Set(row, column, 255);
					else
						cannyMatrix.Set(row, column, 0);
				}
				if (gradientAngle == 45) // 45e 135 dik.
				{
					bool a = false;
					bool b = false;
					if (row - 1 > 0 && column - 1 > 0) // kuzey bati.
						a = cannyMatrix.Get(row - 1, column - 1) == 255;
					if (row + 1 < cannyMatrix.getRow() && column + 1 <= cannyMatrix.getColumn()) // guney dogu
						//b = cannyMatrix.Get(row + 1, column + 1) == 255;

					if (a || b)
						cannyMatrix.Set(row, column, 255);
					else
						cannyMatrix.Set(row, column, 0);
				}
			}
		}

	/////test ////
	for (int row = sinir; row < *resim->getHeight() - sinir; row++)				  // Resmin pixellerini dolasmak
		for (int column = sinir; column < *resim->getWidth() - sinir; column++) // icin gerekli.
		{
			pozisyon = (row - sinir) * (*resim->getWidth() - 2 * sinir) + column - sinir;
			newBufferCanny[pozisyon] = cannyMatrix.Get(row, column);
		}

	{
		//////////// resimleri ekrana aktarma kismi.///////////////
		//// cannysiz resim.
		resim->setDisplayImage(ConvertIntensityToBMP(
			newBufferGradient,
			*resim->getWidth() - 2,
			*resim->getHeight() - 2,
			resim->getNewSize()));

		if (!SaveBMP(resim->getDisplayImage(),
			*resim->getWidth() - 2,
			*resim->getHeight() - 2,
			*resim->getNewSize(),
			stringToLPCTSTR(textBoxDosyaYoluCanny->Text)))
		{
			MessageBox::Show("islem basarisiz"); return;
		}
		pictureBoxCannyGradient->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxDosyaYoluCanny->Text)));
		////cannyli
		resim->setDisplayImage(ConvertIntensityToBMP(
			newBufferCanny,
			*resim->getWidth() - 2,
			*resim->getHeight() - 2,
			resim->getNewSize()));

		if (!SaveBMP(resim->getDisplayImage(),
			*resim->getWidth() - 2,
			*resim->getHeight() - 2,
			*resim->getNewSize(),
			stringToLPCTSTR(textBoxDosyaYoluCanny->Text)))
		{
			MessageBox::Show("islem basarisiz"); return;
		}
		pictureBoxCannyNew->Image = Image::FromStream(gcnew  MemoryStream(File::ReadAllBytes(textBoxDosyaYoluCanny->Text)));
	}

}


