#pragma once
#include "stdafx.h"
#include <Windows.h>
#include "Vertex.h"
#include <vector>
using namespace MyVector;
using namespace std;
using namespace System::Drawing;
using namespace System::Windows::Forms::DataVisualization::Charting;
ref class Islemler
{
private:
	float Islemler::DeegreToRadian(float degree);

public:
	Islemler();
	~Islemler();
		
	BYTE * daireCiz(BYTE* Buffer, int width, int height, int cemberX, int cemberY, float yaricap );

	BYTE * filtreUygula(BYTE* Buffer,
						int *width,
						int *height,
						System::String ^ filtre,
						int row,
						int column, float sigma);

	vector<Vertex*> histogramHesapla(BYTE * buffer, int width, int height, String ^ mode);
	System::Void histogramCiz(vector<Vertex*> histogram, Chart ^ chartHistogram, String ^ mode);
	BYTE * siyahBeyaz(BYTE * buffer, int width, int height, vector<Vertex*>  histogram);

	vector<Vertex*> rastgeleAgirlikMerkezleriOlustur(int renkAdet);
	//vector<Vertex*> matrixMultiplication(vector<Vertex*> matrixA, vector<Vertex*> matrixB);
	//vector<Vertex*> inverseMatrix(vector<Vertex*> matrix);
	//vector<Vertex*> covarianceMatrix(vector<Vertex*> pixel, vector<Vertex*> agirlikMerkez, int N);
	//float mahalanobisDistance(vector<Vertex*> pixel, vector<Vertex*> agirlikMerkez, vector<Vertex*> inversCovariance);
	float oklitDistance(Vertex pixel, Vertex agirlikMerkez);

	vector<int> calculateRgbOklitThreshold(vector<Vertex*> histogram, int renkAdet);
	vector<int> calculateRgbMahalanobisThreshold(vector<Vertex*> histogram, int renkAdet);
	vector<int> calculateIntensityOklitThreshold(vector<Vertex*> histogram, int renkAdet);
	vector<int> calculateIntensityMahalanobisThreshold(vector<Vertex*> histogram, int renkAdet);

	//System::Void thresholdBasedSegmentationRGB(BYTE * buffer, vector<int>);
	System::Void thresholdBasedSegmentationIntensity(BYTE * buffer, vector<int> thresholds, int height, int width);

};

