#include "stdafx.h"
#include "islemler.h"
#include "imge_bmp.h"
#include "MyForm.h"
#include "Vertex.h"
//#include "Matrix.h"
//////////////////////////
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>
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

MATRIX Islemler::matrixMultiplication(MATRIX matrixA, MATRIX matrixB)
{
	MATRIX productMatrix(matrixA.getRow(), matrixB.getColumn());
	float sum = 0; int j = 1;
	for (int i = 1; i <= matrixA.getRow(); i++)
	{		
		for (j = 1; j <= matrixB.getColumn(); j++)
		{
			sum = 0;
			for (int k = 1; k <= matrixA.getColumn(); k++)
			{
				float a = matrixA.Get(i,  k);
				float b = matrixB.Get(k, j);
				float carpim = a * b;
				sum +=  carpim ;
			}
			productMatrix.Set(i, j, sum);
		}
	}
	return productMatrix;
}

MATRIX Islemler::inverseMatrix(MATRIX matrix)
{
	int col = matrix.getColumn();
	int row = matrix.getRow();
	MATRIX inverseMatrix(row, col);
	MATRIX augmentedMatrix(row, col * 2);
///////////// genisletilmis matris olusturma/////////////////////////
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col * 2; j++)
		{
			if (j > col) // birim matris tarafi // kosegen ise 1 degilse 0.
			{
				if (j - col == i)
					augmentedMatrix.Set(i, j, 1);
				else
					augmentedMatrix.Set(i, j, 0);
			}
			else
				augmentedMatrix.Set(i, j, matrix.Get(i, j));
		}
	//////////////
	int p = 1; 
	while (augmentedMatrix.Get(1, 1) == 0)
		augmentedMatrix = augmentedMatrix.rowSwap(1, p); p++;
	////////////////////////

	//pivot belirleme.
	int pivot = 1;  
	int pivotTemp = pivot;
	bool done = false;
	while (pivot <= row)
	{
		augmentedMatrix = augmentedMatrix.pivotBelirle(&pivot);
		augmentedMatrix = augmentedMatrix.pivotKullan(pivotTemp);
		pivotTemp = pivot;
	}
	// genisletilmis matrisde olusan ters matrisi olusturuyorz.
	for (int i = 1; i <= row; i++)
		for (int j = col; j <= col * 2; j++)
			inverseMatrix.Set(i, j - col + 1, augmentedMatrix.Get(i, j - col + 4));
	/////////////////////////////////////////////////////////////			
	return inverseMatrix;

}

MATRIX Islemler::covarianceMatrix(vector<Vertex*> pixelKume, Vertex agrlkMerkez, int kumePixelAdet)
{
	MATRIX covariance(3,3);
	MATRIX A(3, kumePixelAdet); 
		for (int j = 1; j <= kumePixelAdet; j++)
		{			
				A.Set(1, j, pixelKume[j-1]->getX() - agrlkMerkez.getX());
				A.Set(2, j, pixelKume[j-1]->getY() - agrlkMerkez.getY());
				A.Set(3, j, pixelKume[j-1]->getZ() - agrlkMerkez.getZ());			
		}
	MATRIX transposeA(A.getColumn(), A.getRow());
	transposeA = (matrisTranspoze(A));
	covariance = matrixMultiplication(A, transposeA);
	covariance = covariance / kumePixelAdet;
	
	return covariance;
}

MATRIX Islemler::matrisTranspoze(MATRIX matris)
{
	MATRIX transpozeMatris(matris.getColumn(), matris.getRow());
	for(int i=1; i<=matris.getColumn(); i++)
		for (int j = 1; j <= matris.getRow(); j++)
		{
			transpozeMatris.Set(i, j, matris.Get(j, i));
		}
	
	return transpozeMatris;
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
		agirlikMerkezleri[i]->setZ ( a);
		a += alfa;
	}
	return agirlikMerkezleri;
}
float Islemler::oklitDistance(Vertex pixel, Vertex agirlikMerkez)
{
	float distance = Math::Abs(
		Math::Sqrt(
			Math::Pow(Math::Abs(agirlikMerkez.getX() - pixel.getX()), 2) +
			Math::Pow((Math::Abs(agirlikMerkez.getY() - pixel.getY())), 2) +
			Math::Pow((Math::Abs(agirlikMerkez.getZ() - pixel.getZ())), 2)));
	return  distance;
}
float Islemler::mahalanobisDistance(Vertex pixel, Vertex agirlikMerkez, MATRIX inversCovariance)
{	
	Vertex p1 = pixel - agirlikMerkez;
	MATRIX pixel_agrlkMrkz(3,1);  // vertex to matris
	pixel_agrlkMrkz.Set(1, 1, p1.getX()); 
	pixel_agrlkMrkz.Set(2, 1, p1.getY());
	pixel_agrlkMrkz.Set(3, 1, p1.getZ());
	MATRIX transpozePixel_AgirlikMerkez = matrisTranspoze(pixel_agrlkMrkz);
	
	MATRIX distance = matrixMultiplication(transpozePixel_AgirlikMerkez,
	matrixMultiplication(inversCovariance, pixel_agrlkMrkz));

	float skalarDistance = distance.Get(1,1);
	
	return sqrt(skalarDistance);
}

vector<Vertex*> Islemler::calculateThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode, vector<MATRIX*> inverCovariances)
{
	vector<Vertex*> agirlikMerkezleri(rastgeleAgirlikMerkezleriOlustur(renkAdet));
	vector<Vertex*> tempAgirlikMerkezleri(rastgeleAgirlikMerkezleriOlustur(renkAdet));
	// kumelerin toplam x y z degerleri.
	vector<Vertex*> clusterSums;
	// kumelerdeki tum elemanlar. covariance matris icin.
	vector<vector<Vertex*>> clusters;
	// kumelerin covariance matrisleri
	vector<MATRIX*> covarianceMatrices;
	// pixelin kumelere olan uzakliklari.
	vector<float> uzakliklar;
	// kumelerdeki pixel adetleri.
	vector<int> pixelSayi;
	// uzaklik karsilastirmasi yapilacak pixel.
	Vertex pixel = new Vertex();

	for (int i = 0; i < renkAdet; i++) {// bo$ covariance matrisler olusturuluyor.		
		covarianceMatrices.push_back(new MATRIX(3, 3)); 
	}

	bool done = false; bool ilkDefa = true;
	while (!done)
	{
		clusterSums.clear();
		pixelSayi.clear();
		clusters.clear();
		
		for (int i = 0; i < renkAdet; i++) 
		{ 
			pixelSayi.push_back(0);
			clusterSums.push_back(new Vertex()); 

			vector<Vertex*> kume;
			clusters.push_back(kume);
			clusters[i].push_back(agirlikMerkezleri[i]);
		}
		for (int i = 0; i < 256; i++)
		{
			uzakliklar.clear();
			for (int j = 0; j < renkAdet; j++)
			{
				pixel.setX(histogram[i]->getX());
				pixel.setY(histogram[i]->getY());
				pixel.setZ(histogram[i]->getZ());
				if (mode == "oklit" || (ilkDefa))
					uzakliklar.push_back(oklitDistance(pixel, agirlikMerkezleri[j]));
				else
				{
					if (covarianceMatrices[j]->Get(1, 1) != 0) {

						MATRIX inverseCovariance = inverseMatrix(*covarianceMatrices[j]);
						*inverCovariances[j] = inverseCovariance;
						uzakliklar.push_back(mahalanobisDistance(pixel, agirlikMerkezleri[j], inverseCovariance));
					}
					else
						uzakliklar.push_back(INFINITY);
				}
			}
			// noktanin minumum uzaklikta oldugu kumenin indisini dondurur.
			int minUzaklik = (min_element(uzakliklar.begin(), uzakliklar.end())) - uzakliklar.begin();

			// daha sonra yeni agirlik merkezlerini bulmak uzere degerleri topluyoruz.
			clusterSums[minUzaklik]->setX(clusterSums[minUzaklik]->getX() + pixel.getX());
			clusterSums[minUzaklik]->setY(clusterSums[minUzaklik]->getY() + pixel.getY());
			clusterSums[minUzaklik]->setZ(clusterSums[minUzaklik]->getZ() + pixel.getZ());
			pixelSayi[minUzaklik]++;
			//mahalanobis			
			clusters[minUzaklik].push_back(new Vertex(pixel));
		}
		ilkDefa = false;

		vector<MATRIX*> tempCovariances;
		int gerekliEsitlikSayisi = 0;
		// yeni agirlik merkezleri hesaplaniyor ve test icin mevcut olanlar tempe aktariliyor.
		for (int k = 0; k < renkAdet; k++)
		{
			tempAgirlikMerkezleri[k]->setX(agirlikMerkezleri[k]->getX());
			tempAgirlikMerkezleri[k]->setY(agirlikMerkezleri[k]->getY());
			tempAgirlikMerkezleri[k]->setZ(agirlikMerkezleri[k]->getZ());

			if (pixelSayi[k] != 0) {
				agirlikMerkezleri[k]->setX(clusterSums[k]->getX() / pixelSayi[k]);
				agirlikMerkezleri[k]->setY(clusterSums[k]->getY() / pixelSayi[k]);
				agirlikMerkezleri[k]->setZ(clusterSums[k]->getZ() / pixelSayi[k]);
			}

			// covariance matrisinin hesaplanmasi.
			int N = clusters[k].size();
			tempCovariances.push_back( new MATRIX(*covarianceMatrices[k]));
			covarianceMatrices[k] = new MATRIX(covarianceMatrix(clusters[k], agirlikMerkezleri[k], N));


			// kumeleme isleminin bitip bitmediginin kontrolu.
			float xTemp = tempAgirlikMerkezleri[k]->getX();
			float yTemp = tempAgirlikMerkezleri[k]->getY();
			float zTemp = tempAgirlikMerkezleri[k]->getZ();
			float xNew = agirlikMerkezleri[k]->getX();
			float yNew = agirlikMerkezleri[k]->getY();
			float zNew = agirlikMerkezleri[k]->getZ();
			if (mode == "mah")
			{
				/*MATRIX a = ;
				MATRIX b = ;*/
				bool matris = *covarianceMatrices[k] == *tempCovariances[k];
				if (xTemp == xNew && yTemp == yNew && zTemp == zNew && matris )
					gerekliEsitlikSayisi++;
			}
			else
				if (xTemp == xNew && yTemp == yNew && zTemp == zNew)
					gerekliEsitlikSayisi++;
		}
		
		
		/*for (int m = 0; m < renkAdet; m++)
		{
			float xTemp = tempAgirlikMerkezleri[m]->getX();
			float yTemp = tempAgirlikMerkezleri[m]->getY();
			float zTemp = tempAgirlikMerkezleri[m]->getZ();
			float xNew = agirlikMerkezleri[m]->getX();
			float yNew = agirlikMerkezleri[m]->getY();
			float zNew = agirlikMerkezleri[m]->getZ();
			if (mode == "mah")
			{
				if (xTemp == xNew && yTemp == yNew && zTemp == zNew && covarianceMatrices[m] == tempCovariances[m])
					gerekliEsitlikSayisi++;
			}
			else
				if (xTemp == xNew && yTemp == yNew && zTemp == zNew)
					gerekliEsitlikSayisi++;

		}*/
		if (gerekliEsitlikSayisi == renkAdet)
			done = true;

	}
	return agirlikMerkezleri;
}


vector<Vertex*> Islemler::calculateRGBThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode, vector<MATRIX*> inverCovariances)
{	
    return calculateThreshold(histogram, renkAdet, mode, inverCovariances);
}


vector<Vertex*> Islemler::calculateIntensityThreshold(vector<Vertex*> histogram, int renkAdet, String ^ mode)
{	
	vector<MATRIX*> inverCovariances;
	return calculateThreshold(histogram, renkAdet, mode, inverCovariances);
}

BYTE * Islemler::thresholdBasedSegmentationRGB(BYTE * buffer, vector<Vertex*> agirlikMerkezleri, int height, int width, 
	vector<Vertex*> histogram, String  ^ mode, vector<MATRIX*> inverCovariances)
{
	srand(time(NULL));
	#define _SECURE_SCL 0
	enum Renk { red, green, blue };
	BYTE * bufferNew = new BYTE[width*height * 3];	
	Vertex pixel = new Vertex();
	int kumdeAdet = agirlikMerkezleri.size();
	FLOAT * uzakliklar = new FLOAT[kumdeAdet];

	vector <Vertex*> colors;  colors.reserve(kumdeAdet);
	for (int k = 0; k < kumdeAdet; k++)
	{
		colors.push_back(new Vertex(rand() % 255, rand() % 255, rand() % 255));
	}
	for (int i = 0; i < height*width*3; i += 3)
	{
		//uzakliklar.clear();
		pixel.setX(histogram[buffer[i + red]]->getX());
		pixel.setY(histogram[buffer[i + green]]->getY());
		pixel.setZ(histogram[buffer[i + blue]]->getZ());
		for (int j = 0; j < kumdeAdet; j++)
		{	
			if (mode == "oklit")
				uzakliklar[j] = (oklitDistance(pixel, agirlikMerkezleri[j]));
			else
				uzakliklar[j] = mahalanobisDistance(pixel, agirlikMerkezleri[j], *inverCovariances[j]);
		}
		int minUzaklik = uzakliklar[0]; int minUzaklikKumeIndis = 0;
		for (int k =1; k<kumdeAdet; k++)
		{
			if (uzakliklar[k] < minUzaklik)
			{
				minUzaklik = uzakliklar[k];
				minUzaklikKumeIndis = k;
			}
		}
		bufferNew[i + red] = colors[minUzaklikKumeIndis]->getX();
		bufferNew[i + blue] = colors[minUzaklikKumeIndis]->getY();
		bufferNew[i + green] = colors[minUzaklikKumeIndis]->getZ();
		
			
	}

	return bufferNew;
}

System::Void Islemler::thresholdBasedSegmentationIntensity(BYTE * buffer, vector<Vertex*> agirlikMerkezleri, int height, int width, vector<Vertex*> histogram)
{
	srand(time(NULL));
	Vertex pixel = new Vertex();
	int kumdeAdet = agirlikMerkezleri.size();
	FLOAT * uzakliklar = new FLOAT[kumdeAdet];
	vector <Vertex*> colors; colors.reserve(kumdeAdet);
	for (int k = 0; k < kumdeAdet; k++)
	{
		colors.push_back(new Vertex(rand() % 255, rand() % 255, rand() % 255));
	}
	for (int i = 0; i < height*width; i++)
	{
		pixel.setX(histogram[buffer[i]]->getX());
		for (int j = 0; j < kumdeAdet; j++)
		{
			uzakliklar[j] = (oklitDistance(pixel, agirlikMerkezleri[j]));
		}
		float minUzaklik = uzakliklar[0]; int minUzaklikKumeIndis = 0;
		for (int k = 1; k < kumdeAdet; k++)
		{
			if (uzakliklar[k] < minUzaklik)
			{
				minUzaklik = uzakliklar[k];
				minUzaklikKumeIndis = k;
			}
		}
		buffer[i] = colors[minUzaklikKumeIndis]->getX();
	}

}
