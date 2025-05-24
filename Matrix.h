//
// Created by admin on 18.05.2025.
//

#ifndef LAB3_IMATRIX_H
#define LAB3_IMATRIX_H

#include <ostream>
#include "Vector.h" //also Linal

template <linal::Field T>
class Matrix{
public:
    virtual int rows() const = 0;
    virtual int cols() const = 0;
    virtual T get(int x, int y) const = 0;
    virtual Matrix<T>& set(int x, int y, T item) = 0;
    virtual Vector<T> getRow(int x) const = 0;
    virtual Matrix<T>& setRow(int x, const Vector<T>& vec) = 0;
    virtual Vector<T> getCol(int x) const = 0;
    virtual Matrix<T>& setCol(int x, const Vector<T>& vec) = 0;
    virtual Matrix<T>* operator+(const Matrix<T>& other) const = 0;
    virtual Matrix<T>& operator+=(const Matrix<T>& other) = 0;
    virtual Matrix<T>* operator*(T item) const = 0;
    virtual Matrix<T>& operator*=(T item) = 0;
    virtual Matrix<T>* operator*(const Matrix<T>& other) const = 0;
    virtual Matrix<T>& swapRows(int x, int y) = 0;
    virtual Matrix<T>& swapCols(int x, int y) = 0;
    virtual Matrix<T>& mulRow(int x, T mul) = 0;
    virtual Matrix<T>& mulCol(int x, T mul) = 0;
    virtual Matrix<T>& combRows(int to, int from, T mul) = 0;
    virtual Matrix<T>& combCols(int to, int from, T mul) = 0;
    virtual double norm() const = 0;
    virtual Matrix<T>* clone() const = 0;
    virtual ~Matrix() = default;
};

template <linal::Field T>
Matrix<T>* operator*(const T& scalar, const Matrix<T>& m){
    return m * scalar;
}

template <linal::Field T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& X){
    os << "[ ";
    for(int i=0;i<X.rows();i++){
        if(i != 0){
            os << "; ";
        }
        for(int j=0;j<X.cols();j++){
            os << X.get(i, j);
            if(j != X.cols()-1){
                os << " ";
            }
        }
    }
    os << "]";
    return os;
}

#endif //LAB3_IMATRIX_H
