#pragma once
#include "stdafx.h"
#include <Windows.h>
#include "Vertex.h"
#include <vector>
#include "Matrix.h"
using namespace MyVector;
using namespace std;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;
ref class Islemler
{
private:
	double Islemler::DeegreToRadian(double degree);

	double oklitDistance(Vertex pixel, Vertex agirlikMerkez);

	double mahalanobisDistance(Vertex pixel, Vertex agirlikMerkez, MATRIX inversCovariance);
	// matris sýnýfýnýn  içine  koy bi ara.////////////////
	MATRIX matrixMultiplication(MATRIX matrixA, MATRIX matrixB);
	MATRIX covarianceMatrix(vector<Vertex*> pixelKume, Vertex agrlkMerkez, int kumeAdet);
	MATRIX matrisTranspoze(MATRIX matris);
	//////////////////////////////////////////////////////
	vector<Vertex*> calculateThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode, vector<MATRIX*> inverCovariances);
	vector<Vertex*> rastgeleAgirlikMerkezleriOlustur(int renkAdet);	
	
public:
	Islemler();
	~Islemler();
	/////////////////////////////////
	MATRIX inverseMatrix(MATRIX matrix);
	////////////////////////////////
	BYTE * daireCiz(BYTE* Buffer, int width, int height, int cemberX, int cemberY, double yaricap );

	BYTE * filtreUygula(BYTE* Buffer,
						int *width,
						int *height,
						System::String ^ filtre,
						int row,
						int column, double sigma);

	vector<Vertex*> histogramHesapla(BYTE * buffer, int width, int height, String ^ mode);
	System::Void histogramCiz(vector<Vertex*> histogram, Chart ^ chartHistogram, String ^ mode);
	BYTE * siyahBeyaz(BYTE * buffer, int width, int height, vector<Vertex*>  histogram);	
	
	vector<Vertex*> calculateRGBThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode, vector<MATRIX*> inverCovariances);
	
	vector<Vertex*> calculateIntensityThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode);
	

	BYTE * thresholdBasedSegmentationRGB(BYTE * buffer, vector<Vertex*> agirlikMerkezleri, 
		int height, int width, vector<Vertex*> histogram, String  ^ mode, vector<MATRIX*> inverCovariances);

	System::Void thresholdBasedSegmentationIntensity(BYTE * buffer, vector<Vertex*> thresholds, int height, int width, vector<Vertex*> histogram);

};

