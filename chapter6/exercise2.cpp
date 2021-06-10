#include <iostream>

using namespace std;

template<typename elemType>
class Matrix
{
    template<typename U>
    friend Matrix<U> 
        operator+(const Matrix<U> &, const Matrix<U> &);
    template<typename U>
    friend Matrix<U> 
        operator*(const Matrix<U> &, const Matrix<U> &);
public:
    Matrix(const elemType *); 
    Matrix(int row, int col);   
    Matrix(const Matrix<elemType> &);
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

template<typename elemType>
Matrix<elemType>::Matrix(int row, int col)
{
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
        {
            _matrix[i][j] = 0.0;
        }
}

template<typename elemType>
Matrix<elemType>::Matrix(const elemType *arr)
{
    int arr_index = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++, arr_index++)
        {
            this->_matrix[i][j] = arr[arr_index];
        }
}

template<typename elemType>
Matrix<elemType>::Matrix(const Matrix &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            this->_matrix[i][j] = A._matrix[i][j];
}

template<typename elemType>
ostream &Matrix<elemType>::print(ostream &os) const
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

template<typename elemType>
inline ostream & operator <<(ostream &os, const Matrix<elemType> &rhs)
{
    return rhs.print(os);
}

template<typename elemType>
Matrix<elemType> 
operator+(const Matrix<elemType> &A, const Matrix<elemType> &B)
{
    Matrix<elemType> result(A);
    result += B;
    return result;
}

template<typename elemType>
Matrix<elemType> 
operator*(const Matrix<elemType> &A, const Matrix<elemType> &B)
{
    Matrix<elemType> result(A.row(), B.col());
    for(int i = 0; i < A.row(); i++)
        for(int j = 0; j < B.col(); j++)
            for(int k = 0; k < A.col(); k++)
                result(i, j) += A(i, k) * B(k, j);
    return result;
}

template<typename elemType>
void Matrix<elemType>::operator+=(const Matrix<elemType> &A)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            _matrix[i][j] += A._matrix[i][j];
}

int main()
{
    Matrix<float> m(4,4);
    cout << m << endl;

    float ar[16] = {
        1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,  
    };

    Matrix<float> identity(ar);
    cout << identity << endl;

    Matrix<float> m2(identity);//??
    m = identity;
    cout << m2 << endl;
    cout << m << endl;

    float ar2[16] = {
        1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.0, 10.1, 11.2, 12.3, 13.4, 14.5, 15.6, 16.7
    };
    Matrix<float> m3(ar2);
    cout << m3 << endl;
    Matrix<float> m4 = m3 * identity;
    cout << m4 << endl;
    Matrix<float> m5 = m3 + m4;
    cout << m5 << endl;
    m3 += m4;
    cout << m3 << endl;
    return 0;
}