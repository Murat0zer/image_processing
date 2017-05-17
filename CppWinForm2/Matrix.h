class MATRIX
{
private:
	int row, col;
	double **p;
public:		
	MATRIX(int, int);
	void Set(int, int, double) const;
	double Get(int, int) const;
	int getRow() const;
	int getColumn() const;
	MATRIX rowSwap(int row1, int row2);
	MATRIX pivotBelirle(int * pivot);
	MATRIX pivotKullan(int pivot);

	MATRIX MATRIX::SatirBol(int satir, double islem);
	
	MATRIX SatirIslem(int satir, int satir2, double islem); 
	MATRIX operator / (int n);
	bool operator ==(const MATRIX& other);
	bool operator!=(const MATRIX& other);
	// copy const.
	MATRIX(MATRIX &matrix);
	MATRIX operator = ( const MATRIX &other);
	~MATRIX();
};


