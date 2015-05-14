#include<iostream>
using std::cout;
#include<vector>
using std::vector;

class matrix{
	private:
		std::vector<double> M;
		int col;
		int row;
	public:
		matrix(int c, int r);
		matrix(int n);
		matrix(const matrix& M);
		
		matrix& operator=(const matrix& M);
		matrix operator*(const matrix& M);
		matrix& operator*=(const matrix& M);
		double* operator[](int r);

		
		const double* operator[](int r) const;
		int getCol() const;
		int getRow() const;
		int getElements() const;
		bool isSquare() const;
		bool isRegular() const;
		//matrix pow(int h){}
		void resize(int c, int r);
		void resize(int n);
		void print();
		void editRow(double a[], int r);
		
		static matrix identity(int n);
};


int main()
{
	matrix m(4);
	double matx[4][4] = {{2,1,0,0},
						 {0,1,0,0},
						 {0,4,1,0},
						 {0,0,0,1}};
	for(int i=0; i<4; i++)m.editRow(matx[i], i);
	m *= m;

	m.print();

	matrix m2theH = matrix::identity(4);

	for(int i = 0; i<7; i++)
	{

	}m2theH *= m;

	m2theH.print();

	

	return 0;
}

matrix::matrix(int c, int r):M(c*r, 0),col(c),row(r){}
matrix::matrix(int n):M(n*n, 0),col(n),row(n){}
matrix::matrix(const matrix& M):M(M.getElements()),col(M.getCol()),row(M.getRow())
{
	for(int i = 0; i<(this->row); i++)
		for(int j = 0; j<(this->col); j++) 
			this->M[(i*this->col) + j] = M[i][j];
}

matrix& matrix::operator=(const matrix& M){
	if(this != &M)
	{
		(this->M).clear();
		(this->M).resize(M.getRow()*M.getCol(), 0);
		this->col = M.getCol();
		this->row = M.getRow();
		for(int i = 0; i<(this->row); i++)
			for(int j = 0; j<(this->col); j++) 
				this->M[(i*this->col) + j] = M[i][j];
	}
	return *this;
}

matrix matrix::operator*(const matrix& M)
{
	matrix P(0);
	if(this->col == M.getRow() && this->row == M.getCol())
	{
		P.resize(M.getCol(), this->row);
		double dotP;
		int i, j, k;
		for(i = 0; i < (this->row); i++)
		{
			for(j = 0; j<(this->row); j++)
			{
				dotP = 0;
				for(k = 0; k < this->row; k++)
					dotP += this->M[i*this->col + k]* M[k][j];
				P[i][j] = dotP;
			}
		}
	}
	return P;
}

matrix& matrix::operator*=(const matrix& M)
	{return this->operator=(this->operator*(M));}
		
double* matrix::operator[](int r) {return &(this->M[this->col * r]);}
const double* matrix::operator[](int r) const{return &(this->M[this->col * r]);}
int matrix::getCol() const{return this->col;}
int matrix::getRow() const{return this->row;}
int matrix::getElements() const{return ((this->col) * (this->row));}
bool matrix::isSquare() const{return (this->row ==this->col);}
//matrix pow(int h){}
void matrix::resize(int c, int r)
{
	(this->M).resize(c*r, 0);
	this->col = c;
	this->row = r;
}
void matrix::resize(int n)
{
	(this->M).resize(n*n, 0);
	this->col = n;
	this->row = n;
}
void matrix::print()
{
	for(int i = 0; i<(this->row); i++)
	{
		for(int j = 0; j<(this->col); j++)
		{
			cout<<(this->M[(i*this->col) + j])<<";";
		}
		cout<<"\n";
	}
}
void matrix::editRow(double a[], int r)
{
	for(int i=0; i<this->col; i++)
		this->M[(r*this->col) + i] = a[i];
}

matrix matrix::identity(int n)
{
	matrix I(n);
	for(int i=0; i<n; i++)
		I[i][i] = 1;
	return I;
}

bool matrix::isRegular() const{
	bool regular = true;
	for(int i=0; i<((this->row)*(this->col)) && regular; i++)
		regular &= (this->M[i] > 0);

	return regular;
}
