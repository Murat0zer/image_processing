#include "stdafx.h"
#include "islemler.h"
#include "imge_bmp.h"
#include "MyForm.h"
#include "Vertex.h"

//////////////////////////
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>


using namespace MyVector;
using namespace std;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Windows::Forms::DataVisualization::Charting;

Islemler::Islemler() {}
Islemler::~Islemler() {}

float Islemler::DeegreToRadian(float degree)
{	
	return degree = degree * M_PI / 180;
}

BYTE * Islemler::daireCiz(BYTE* Buffer, int width, int height, int cemberX, int cemberY, float yaricap)
{	
	//  1 cm = 38 pixel.
	const int PIXEL = 38;
	float alfa = 0;
	const float cemberCevre = 2 * M_PI * yaricap;
	const int pixelSayisi = cemberCevre * 38;
	const float angleArtirimMiktar = (float)360 / pixelSayisi;
	const float epsilon = 0.005;
	long pozisyon = 0;
	
	float rowX = yaricap * cos(DeegreToRadian(alfa));
	float columnY = yaricap * sin(DeegreToRadian(alfa));
	
	pozisyon = (cemberY )* width + cemberX ;
	Buffer[pozisyon] = 255;
	long resimUstAdresSinir = width * height;
	
		while (alfa - 360 < epsilon) {
		    int (columnY) =  yaricap * sin(DeegreToRadian(alfa)) * PIXEL  ;
			int (rowX) = yaricap * cos(DeegreToRadian(alfa))  * PIXEL;
			pozisyon = (cemberY + columnY )* width +  cemberX + rowX;
			long resimYanAdresSinir = cemberX + rowX;
			// üstten taþma kontrolü.
			if (pozisyon < resimUstAdresSinir && pozisyon > 0)
			// yanlardan taþma kontrolü
			if (width - resimYanAdresSinir > 0 && resimYanAdresSinir >0 )
				Buffer[pozisyon], Buffer[pozisyon + 1] , Buffer[pozisyon + 2] = 255; //rgb. +1 +2 gereksiz olabilir
			
			alfa += angleArtirimMiktar;			 
		}
	return  Buffer;
}
BYTE * Islemler::filtreUygula(
	BYTE * Buffer, int * width, int * height, System::String ^ filtre, int row, int column, float sigma)

{
	int filterMatrisRow = row;
	int filterNatrisColumn = column;
	int filterMatrisBoyut = filterMatrisRow * filterNatrisColumn;
	int * filterMatris = new int[filterMatrisBoyut];
	long pozisyon;
	int sinir = (filterMatrisRow - 1) / 2;
	// yeni resmin boyutu.
	BYTE * newBuffer = new BYTE[(*width - 2 * sinir) * (*height - 2 * sinir)];
	FLOAT * gaussianMatris = new FLOAT[filterMatrisBoyut];
	int filterMatrisIndis = 0;

	// gaussian  filtre matrisi hesaplanmasi.
	if (filtre == "Gaussian")
	{
		int X, Y;  float sum = 0;
		for(int y=0; y<filterNatrisColumn; y++)
			for(int x=0; x < filterMatrisRow; x++)
			{
				//  merkez noktaya gore pixellerin uzaklik donusumu.
				X = x - ((filterMatrisRow - 1) / 2);
				Y = -y + ((filterMatrisRow - 1) / 2);
				// degerler 2d gaus fonksiyonuna gore hesaplaniyor.
				gaussianMatris[filterMatrisIndis++] = (1 / (2 * M_PI*pow(sigma,2)))* // 2d gaus func.
					pow(M_E, -(pow(X,2) + pow(Y,2)) / (2 * pow(sigma,2)));
			}
		// matris degerleri toplaniyor.
		for (int i = 0; i < filterMatrisBoyut; i++)
			sum += gaussianMatris[i];
		// matris degerlerinin toplaminin 1 olmasi icin normalizasyon yapiliyor.
		for (int i = 0; i < filterMatrisBoyut; i++)
			gaussianMatris[i] /= sum;
			
	}
	// filtrelere gore yeni pixel degerinin hesaplanmasi
	for(int row = sinir; row < *height - sinir; row++)				  // Resmin pixellerini dolasmak
		for (int column = sinir; column < *width  - sinir; column++) // icin gerekli.
			{
			float sum = 0;  filterMatrisIndis = 0;
				for(int filterRow = 0; filterRow < filterNatrisColumn; filterRow++)
					for(int filterColumn =0; filterColumn < filterMatrisRow; filterColumn++ )
					{ 
						// resimdeki filtre matrisine denk gelen pixel degerlerinin pozisyonu.
						pozisyon = (row - sinir + filterRow) * (*width) + column - sinir + filterColumn;
						// mean icin pixel degerleri toplanir.
						if(filtre == "Mean")
							sum += Buffer[pozisyon];
						// median icin degerleri daha sonra siralamak uzere bir arraya atiyoruz.
						if (filtre == "Median")							
							filterMatris[filterMatrisIndis++] = Buffer[pozisyon];	
						// gaussian filtre matris degerleriyle orjinal matris degerlerini carpip topluyoruz.
						if (filtre == "Gaussian")
						{
						  sum += Buffer[pozisyon] * (gaussianMatris[(filterMatrisIndis++)]);
						}
					}
				// yeni resimde pixelin nerde olacaginin hesaplanmasi. 
				pozisyon = (row - sinir) * (*width - 2 * sinir) + column - sinir;
				// mean icin komsu pixellerin ortalama degeri yazilir.
				if (filtre == "Mean") 
				{
					int avg =  Convert::ToInt32(sum / filterMatrisBoyut);
					newBuffer[pozisyon] = avg;
				}
				// median icin ortadaki deger yazilir.
				if (filtre == "Median")
				{
				   std::sort(filterMatris , filterMatris+filterMatrisBoyut);
				   newBuffer[pozisyon] = filterMatris[(filterMatrisBoyut - 1) / 2];
				}
				// carpip toplanmis matris degerleri merkezdeki pixelin yeni degeri.
				if (filtre == "Gaussian")
				{
					newBuffer[pozisyon] = Convert::ToInt32(sum);
				}
			}
		
	// resmin yeni boyutlari.
	*width -= sinir*2;
	*height -= sinir*2;
	delete[] gaussianMatris;
	delete[] filterMatris;
	return newBuffer;
}

vector<MyVector::Vertex*> Islemler::histogramHesapla(BYTE * buffer, int width, int height, String ^ mode)
{
	vector<Vertex*>  histogram;
	vector<Vertex *>::iterator  pixel = histogram.begin();

	for (int i = 0; i <= 255; i++)
		histogram.push_back(new Vertex());

	if (mode == "rgb")
	{
		int i = 0;
		while( i < width*height*3)
		{				
			histogram[buffer[i]]->setX(histogram[buffer[i]]->getX() + 1); i++;
			histogram[buffer[i]]->setY(histogram[buffer[i]]->getY() + 1); i++;
			histogram[buffer[i]]->setZ(histogram[buffer[i]]->getZ() + 1); i++;
		}
	}
	else
	{
		int i = 0;
		while ( i < width*height)
		{
			histogram[buffer[i]]->setX(histogram[buffer[i]]->getX() + 1);  // x += 1
			/*histogram[buffer[i]]->setY(histogram[buffer[i]]->getY() + 1);
			histogram[buffer[i]]->setZ(histogram[buffer[i]]->getZ() + 1);*/
			i++;
		}
	}
	return histogram;
}

Void Islemler::histogramCiz(vector<Vertex*> histogram, Chart ^ chartHistogram, String ^ mode)
{
	// charttaki onceki verileri temizliyoruz.
	for each(Series ^ series in  chartHistogram->Series)
		series->Points->Clear();
	
	if (mode == "intensity")
	{
		chartHistogram->Visible = true;
		int x1 = 0;
		int y1 = 0;
		for (int i = 0; i <= 255; i++)
		{
			y1 = histogram[i]->getX();
			chartHistogram->Series["intensity"]->Points->AddXY(x1++, y1);
		}
	}
	else
	{
		int pixelValue = 0;
		int redPixelAdet = 0; int greenPixelAdet = 0; int bluePixelAdet = 0;
		for (int i = 0; i <= 255; i++)
		{
			redPixelAdet   = histogram[i]->getX();
			greenPixelAdet = histogram[i]->getY();
			bluePixelAdet  = histogram[i]->getZ();
			chartHistogram->Series["redPixel"]->Points->AddXY(pixelValue, redPixelAdet);
			chartHistogram->Series["greenPixel"]->Points->AddXY(pixelValue, greenPixelAdet);
			chartHistogram->Series["bluePixel"]->Points->AddXY(pixelValue, bluePixelAdet);
			pixelValue++;
		}
	}
	
}

BYTE * Islemler::siyahBeyaz(BYTE * buffer, int width, int height, vector<Vertex*>  histogram)
{
	int x1 = 0; int y1 = histogram[0]->getX(); // birinci kume merkezi. rastgele
	int x2 = 255; int y2 = histogram[254]->getX(); // ikinci kume merkezi. rastgele
	int tempX1 = 1; int tempX2 = 1; int tempY2 = 1; int tempY1 = 2;     // test degerleri.
	while(x1 != tempX1 && y1 != tempY1 && x2 !=tempX2 && y2 != tempY2)
	{
		int clusterOneCount = 0, clusterTwoCount = 0;
		int clusterOneYSum =0, clusterTwoYSum = 0;
		int clusterOneXSum =0, clusterTwoXSum = 0;
		
		for (int i = 0; i < 255; i++)
		{
			float distanceToClusterOne =  // 2 nokta arasi uzaklik
				Math::Abs(Math::Sqrt(Math::Pow(Math::Abs(x1 - i), 2)
					+ Math::Pow((Math::Abs(y1 - histogram[i]->getX())), 2)));
			float distanceToClusterTwo =
				Math::Abs(Math::Sqrt(Math::Pow(Math::Abs(x2 - i), 2)
					+ Math::Pow((Math::Abs(y2 - histogram[i]->getX())), 2)));

			if ((distanceToClusterOne - distanceToClusterTwo) > 0)// nokta kume 2 e yakin
				{
					clusterTwoXSum += clusterTwoCount;
				clusterTwoYSum += histogram[i]->getX();
				clusterTwoCount++;
			}
			else  // kume 1 e yakin.
			{
				clusterOneXSum += clusterOneCount;
				clusterOneYSum += histogram[i]->getX();
				clusterOneCount++;
			}			
		} 
		tempX1 = x1; tempX2 = x2;
		tempY1 = y1; tempY2 = y2;

		if(clusterOneXSum != 0 && clusterOneCount != 0)	
			x1 = clusterOneXSum / clusterOneCount;
		if (clusterOneYSum != 0 && clusterOneCount != 0)
			y1 = clusterOneYSum / clusterOneCount;
		if (clusterTwoCount != 0 && clusterTwoCount != 0)
			x2 = clusterTwoXSum / clusterTwoCount;
		if (clusterTwoCount != 0 && clusterTwoCount != 0)
			y2 = clusterTwoXSum / clusterTwoCount;
	}
	int threshold = (x1 + x2) / 2;
	long pozisyon = 0;
	for (int row = 0; row < height; row++)				  // Resmin pixellerini dolasmak
		for (int column = 0; column < width; column++) // icin gerekli.
		{
			pozisyon = (row ) * (width) + column;
			if (buffer[pozisyon] > threshold)
				buffer[pozisyon] = 255;
			else
				buffer[pozisyon] = 0;
		}
	return buffer;
}

vector<Vertex*> Islemler::rastgeleAgirlikMerkezleriOlustur(int renkAdet)
{
	vector<Vertex*> agirlikMerkezleri;
	int alfa = 255 / renkAdet;
	int a = 0;
	for (int i = 0; i < renkAdet; i++) // rastgele merkezler.
	{
		agirlikMerkezleri.push_back(new Vertex);
		agirlikMerkezleri[i]->setX ( a);
		agirlikMerkezleri[i]->setY (a);
		agirlikMerkezleri[i]->setZ ( 0);
		a += alfa;
	}
	return agirlikMerkezleri;
}


vector<int> Islemler::calculateThreshold(vector<Vertex*> histogram, int renkAdet,String ^ mode)
{
	// 3boyutlu vektor. x y merkezin koordinantlari. ignore z.
	vector<Vertex*> agirlikMerkezleri(rastgeleAgirlikMerkezleriOlustur(renkAdet));
	vector<Vertex*> tempAgirlikMerkezleri(rastgeleAgirlikMerkezleriOlustur(renkAdet));
	// kumelerin toplam x y degerleri. z kumedeki nokta sayisi.
	vector<Vertex*> clusterSums;
	vector<float> uzakliklar;
	bool done = false;
	while (!done)
	{
		clusterSums.clear();
		for (int i = 0; i < renkAdet; i++) { clusterSums.push_back(new Vertex()); }
		for (int i = 0; i < 255; i++)
		{
			uzakliklar.clear();
			for (int j = 0; j < renkAdet; j++)
			{
				Vertex pixel = new Vertex(); pixel.setX(i); pixel.setY(histogram[i]->getX()); pixel.setZ(0.0);
				if (mode == "oklit")
					uzakliklar.push_back(oklitDistance(pixel, agirlikMerkezleri[j]));
				else
					;// mahalanobis distance hesabi yapilacak kisim.
			}
			// noktanin minumum uzaklikta oldugu kumenin indisini dondurur.
			int minUzaklik = (min_element(uzakliklar.begin(), uzakliklar.end())) - uzakliklar.begin();

			// daha sonra yeni agirlik merkezlerini bulmak uzere degerleri topluyoruz.
			clusterSums[minUzaklik]->setX(clusterSums[minUzaklik]->getX() + i);
			clusterSums[minUzaklik]->setY(clusterSums[minUzaklik]->getY() + histogram[i]->getX());
			clusterSums[minUzaklik]->setZ(clusterSums[minUzaklik]->getZ() + 1);
		}
		// yeni agirlik merkezleri hesaplaniyor ve test icin mevcut olanlar tempe aktariliyor.
		for (int k = 0; k < renkAdet; k++)
		{
			tempAgirlikMerkezleri[k]->setX(agirlikMerkezleri[k]->getX());
			tempAgirlikMerkezleri[k]->setY(agirlikMerkezleri[k]->getY());
			if (clusterSums[k]->getZ() != 0) {
				agirlikMerkezleri[k]->setX(clusterSums[k]->getX() / clusterSums[k]->getZ());
				agirlikMerkezleri[k]->setY(clusterSums[k]->getY() / clusterSums[k]->getZ());
			}
		}
		// kumeleme isleminin bitip bitmediginin kontrolu.
		int gerekliEsitlikSayisi = 0;
		for (int m = 0; m < renkAdet; m++)
		{
			float xTemp = tempAgirlikMerkezleri[m]->getX();
			float yTemp = tempAgirlikMerkezleri[m]->getY();
			float xNew = agirlikMerkezleri[m]->getX();
			float yNew = agirlikMerkezleri[m]->getY();
			if (xTemp == xNew && yTemp == yNew)
				gerekliEsitlikSayisi++;
		}
		if (gerekliEsitlikSayisi == renkAdet)
			done = true;
	}
	// elde ettigimiz agirlik merkezinin x degerleriyle threshold hesapliyoruz.
	vector<int> thresholds; vector<int> xValues;

	for each(Vertex agirlikMerkez in agirlikMerkezleri)
		xValues.push_back(agirlikMerkez.getX());

	sort(xValues.begin(), xValues.end());
	vector<int>::iterator  xValue = xValues.begin();
	int a = 0;
	for (int p = 0; p<renkAdet - 1; p++)
	{
		int xvalueOld = *xValue++;
		int threshold = (*xValue + xvalueOld) / 2;
		thresholds.push_back(threshold);
	}
	return thresholds;
}
float Islemler::oklitDistance(Vertex pixel, Vertex agirlikMerkez)
{
	float distance = Math::Abs(Math::Sqrt(Math::Pow(Math::Abs(agirlikMerkez.getX() - pixel.getX()), 2)
		+ Math::Pow((Math::Abs(agirlikMerkez.getY() - pixel.getY())), 2)));
	return  distance;
}

vector<vector<int>> Islemler::calculateRgbOklitThreshold(vector<Vertex*> histogram, int renkAdet)
{	
	//vector<Vertex*> rgbThresholdss;
	vector<vector<int>> rgbThresholdss;
	rgbThresholdss.push_back(calculateIntensityOklitThreshold(histogram, renkAdet));
	// calculeteintensityoklit threshold histogramin sadece x degerleri icin calisir.once x le y i sonra x le z yi
	// swapliyoruz boylece histogramdaki rgb degerleri icin ayri ayri thresholdlari elde ediyoruz. :(
	for (int i = 0; i < 255; i++)
		histogram[i]->setX(histogram[i]->getY());
	rgbThresholdss.push_back(this->calculateIntensityOklitThreshold(histogram, renkAdet));
	for (int i = 0; i < 255; i++)
		histogram[i]->setX(histogram[i]->getZ());
	rgbThresholdss.push_back(this->calculateIntensityOklitThreshold(histogram, renkAdet));
	
	return rgbThresholdss;
}

vector<int> Islemler::calculateRgbMahalanobisThreshold(vector<Vertex*> histogram, int renkAdet)
{
	return vector<int>();
}

vector<int> Islemler::calculateIntensityOklitThreshold(vector<Vertex*> histogram, int renkAdet)
{
	return calculateThreshold(histogram, renkAdet, "oklit");
}

vector<int> Islemler::calculateIntensityMahalanobisThreshold(vector<Vertex*> histogram, int renkAdet)
{
	return vector<int>();
}

INT * Islemler::vectorToArray(INT * myArray, vector<int> vector)
{
	int i = 0;
	for each(int  thresholdValue in vector)
	{
		myArray[i] = thresholdValue;
		i++;
	}
	return myArray;
}
BYTE * Islemler::thresholdBasedSegmentationRGB(BYTE * buffer, vector<vector<int>> thresholds, int height, int width)
{
	enum Renk { red, green, blue };
	BYTE * bufferNew = new BYTE[width * height * 3];
	int rgb = red;
	vector<vector<int>>::iterator  rgbThresholds = thresholds.begin();
	//vector<int>::iterator  thresholds = rgbThresholds[red].begin();
	int thresholdSize = rgbThresholds[red].size();
	int color = 255 / (thresholdSize + 1);

	// degerleri vector den arraya aliyoruz. daha iyi performans icin.////////////////////////////////////////
	INT * redThresholds = new INT[rgbThresholds[red].size()];
	INT * blueThresholds = new INT[rgbThresholds[green].size()];
	INT * greenThresholds = new INT[rgbThresholds[blue].size()];
	vectorToArray(redThresholds, rgbThresholds[red]);
	vectorToArray(greenThresholds, rgbThresholds[green]);
	vectorToArray(blueThresholds, rgbThresholds[blue]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < width*height * 3; i += 3)
	{			
		int redValue = buffer[i + red];
		int greenValue = buffer[i + green];
		int blueValue = buffer[i + blue];
		int colorX = 1;	

		for (int j = 0; j < thresholdSize; j++)
		{
			int newValue = 0;
			
			if (redValue < redThresholds[j])
			{	
				if (j - 1 < 0)
					newValue = (redThresholds[j]) / 2;
				else
					newValue = (redThresholds[j] + redThresholds[j - 1]) / 2;
				bufferNew[i + red] = newValue;
				break;
			}
			colorX++;
			if (colorX - 1 == thresholdSize)
			{
				newValue = (redThresholds[j] + 255) / 2;
				bufferNew[i + red] = newValue;
			}
		}

		for (int j = 0; j < thresholdSize; j++)
		{
			int newValue = 0;
			if (greenValue < greenThresholds[j])
			{
				if (j - 1 < 0)
					newValue = (greenThresholds[j]) / 2;
				else
					newValue = (greenThresholds[j] + greenThresholds[j - 1]) / 2;
				bufferNew[i + green] = newValue;
				break;
			}
			colorX++;
			if (colorX - 1 == thresholdSize)
			{
				newValue = (greenThresholds[j] + 255) / 2;
				bufferNew[i + green] = newValue;
			}
		}

		for (int j = 0; j < thresholdSize; j++)
		{
			int newValue = 0;
			if (blueValue < blueThresholds[j])
			{
				if (j - 1 < 0)
					newValue = (blueThresholds[j]) / 2;
				else
					newValue = (blueThresholds[j] + blueThresholds[j - 1]) / 2;
				bufferNew[i + blue] = newValue;
				break;
			}
			colorX++;
			if (colorX - 1 == thresholdSize)
			{
				newValue = (blueThresholds[j] + 255) / 2;
				bufferNew[i + blue] = newValue;
			}
		}
			
	}
	return bufferNew;
}

System::Void Islemler::thresholdBasedSegmentationIntensity(BYTE * buffer, vector<int> thresholds, int height, int width)
{
	long pozisyon = 0;
	int color = 255 / (thresholds.size()+1);
	vector<int>::iterator  threshold = thresholds.begin();
	
		for (int row = 0; row < height; row++)				// Resmin pixellerini dolasmak
			for (int column = 0; column < width; column++) // icin gerekli.
			{
				int colorX = 1;
				pozisyon = (row) * (width)+column;
				for each(int thrshld in thresholds)
				{	
					
					if (buffer[pozisyon] < thrshld)
					{
						buffer[pozisyon] = color * colorX;
						break;
					}
					colorX++;
					if(colorX-1 == thresholds.size())
						buffer[pozisyon] = color * colorX;
				}
			}	
}
