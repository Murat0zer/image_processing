#include "Matrix.h"
MATRIX::MATRIX( MATRIX & matrix)
{
	row = matrix.row;
	col = matrix.col;
	p = new double*[row];
	for (int i = 0; i < row; i++)
	{
		p[i] = new double[col];
	}
	for (int i = 1; i <= matrix.row; i++)
		for (int j = 1; j <= matrix.col; j++)
			this->Set(i, j, matrix.Get(i, j));
}

MATRIX MATRIX::operator=(const MATRIX & other) 
{
	row = other.row;
	col = other.col;
	p = new double*[row];
	for (int i = 0; i < row; i++)
	{
		p[i] = new double[col];
	}
	for (int i = 1; i <= other.row; i++)
		for (int j = 1; j <= other.col; j++)
			this->Set(i, j, other.Get(i, j));
	
	return *this;
}

MATRIX::MATRIX(int x, int y)
{
	row = x;
	col = y;
	p = new double*[x];
	for (int i = 0; i < x; i++)
	{
		p[i] = new double[y];
	}
}
void MATRIX::Set(int a, int b, double d) const
{
	
	p[a-1][b-1] = d;
}

double MATRIX::Get(int a, int b) const
{
	return p[a-1][b-1];
}

int MATRIX::getRow() const
{
	return this->row;
}
int MATRIX::getColumn() const
{
	return this->col;
}

MATRIX MATRIX::rowSwap(int row1, int row2)
{
	int col = this->getColumn();
	int row = this->getRow();
	double temp = 0;
	for (int i = 1; i <= col; i++)
	{
		temp = this->Get(row1, i);
		this->Set(row1, i, this->Get(row2, i));
		this->Set(row2, i, temp);
	}
	return *this;
}

MATRIX MATRIX::pivotBelirle(int * pivot)
{
	if (*pivot < this->getRow() ) // son satir icin pivot ariyorsak satir degisme yapamayiz.
	{
		for (int i = *pivot; i < row; i++)
			if (this->Get(i, *pivot) == 1)
			{
				if (i != *pivot && *pivot < i)
				{
					*this = this->rowSwap(i, *pivot); *pivot++;
					return *this;
				}
			}
	}
	// satir degisme ile pivot belirlenemedi. bolme yapiyoruz.
	double bolunecek = this->Get(*pivot, *pivot); // pivot olmasi gereken eleman. satiri buna boluyoruz.
	*this = this->SatirBol(*pivot, bolunecek);
	*pivot +=1;
	return *this;
	
}

MATRIX MATRIX::pivotKullan(int pivot)
{
	int row = this->getRow();
	int col = this->getColumn();
	for (int i = 1; i <= row; i++)
	{
		if (pivot != i)
			*this = this->SatirIslem(i, pivot, this->Get(i, pivot));
	}
	return *this;
}

MATRIX MATRIX::SatirIslem(int satir, int satir2, double islem)
{
	int row = this->getRow();
	int col = this->getColumn();
	for (int i = 1; i <= col; i++)
	{
		double value = this->Get(satir2, i);
		double a = - (value * islem);
		double nValue = this->Get(satir, i) + a;

		this->Set(satir, i, nValue);
	}

	return *this;
}

MATRIX MATRIX::SatirBol(int satir, double islem)
{
	int row = this->getRow();
	int col = this->getColumn();
	for (int i = 1; i <= col; i++)
	{
		
		this->Set(satir, i, this->Get(satir,i)/ islem);
	}
	
	return *this;
}



MATRIX MATRIX::operator/(int n)
{
	MATRIX newMatrix(row, col);
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			newMatrix.Set(i, j, this->Get(i, j) / n);
	return newMatrix;
}
bool MATRIX::operator==(const MATRIX & other)
{
	
	int row = this->getRow();
	int col = this->getColumn();
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			if (this->Get(i, j) != other.Get(i, j))
				return false;
	
	return true;

}
bool MATRIX::operator!=(const MATRIX & other)
{
	return !(*this == other);

}
MATRIX::~MATRIX()
{
	/*for (int i = 0; i < row; i++)
		delete[] p[i];
	delete[] p;*/
}