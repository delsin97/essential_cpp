#include <iostream>

using namespace std;

typedef float elemType;

class Matrix
{
    friend Matrix operator+(const Matrix &, const Matrix &);
    friend Matrix operator*(const Matrix &, const Matrix &);
public:
    Matrix(const elemType *); 
    Matrix();   
    Matrix(const Matrix &);
    int row() const {return 4;}
    int col() const {return 4;}
    ostream &print(ostream &) const;
    void operator+=(const Matrix &);
    elemType operator()(int row, int column) const
    {
        return _matrix[row][column];
    }
    elemType &operator()(int row, int column)
    {
        return _matrix[row][column];
    }
private:
    elemType _matrix[4][4];
};

Matrix::Matrix()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            _matrix[i][j] = 0.0;
        }
}

Matrix::Matrix(const elemType *arr)
{
    int arr_index = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++, arr_index++)
        {
            this->_matrix[i][j] = arr[arr_index];
        }
}

Matrix::Matrix(const Matrix &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            this->_matrix[i][j] = A._matrix[i][j];
}

ostream &Matrix::print(ostream &os) const
{
    int cnt = 0;
    for(int i = 0; i < 4 ; i++)
        for(int j = 0; j < 4; j++, cnt++ )
        {
            if(cnt && (cnt % 4 == 0))
                os << endl;
            os << _matrix[i][j] << " ";
        }
    os << endl;
    return os;
}

inline ostream & operator <<(ostream &os, const Matrix &rhs)
{
    return rhs.print(os);
}

void Matrix::operator+=(const Matrix &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            _matrix[i][j] += A._matrix[i][j];
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    Matrix result(A);
    result += B;
    return result;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
    Matrix result;
    for(int i = 0; i < A.row(); i++)
        for(int j = 0; j < B.col(); j++)
            for(int k = 0; k < A.col(); k++)
                result(i, j) += A(i, k) * B(k, j);
    return result;
}

int main()
{
    Matrix m;
    cout << m << endl;

    elemType ar[16] = {
        1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,  
    };

    Matrix identity(ar);
    cout << identity << endl;

    Matrix m2(identity);//??
    m = identity;
    cout << m2 << endl;
    cout << m << endl;

    elemType ar2[16] = {
        1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.0, 10.1, 11.2, 12.3, 13.4, 14.5, 15.6, 16.7
    };
    Matrix m3(ar2);
    cout << m3 << endl;
    Matrix m4 = m3 * identity;
    cout << m4 << endl;
    Matrix m5 = m3 + m4;
    cout << m5 << endl;
    m3 += m4;
    cout << m3 << endl;
    return 0;
}