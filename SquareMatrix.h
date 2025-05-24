//
// Created by admin on 18.05.2025.
//

#ifndef LAB3_SQUAREMATRIX_H
#define LAB3_SQUAREMATRIX_H

#include "RectangularMatrix.h" //also Matrix, Vector and Linal

template <linal::Field T>
class SquareMatrix : public RectangularMatrix<T>{
public:
    explicit SquareMatrix(int size) : RectangularMatrix<T>(size, size) {}

    SquareMatrix(int size, T* array) : RectangularMatrix<T>(size, size, array) {}

    SquareMatrix(const SquareMatrix<T>& other) : RectangularMatrix<T>(other) {}

    Matrix<T>* operator*(const Matrix<T>& other) const override {
        if(this->_rows != other.rows()){
            throw std::invalid_argument("*: Matrix must have connectable size to be multiplied to each other.");
        }
        Matrix<T>* out;
        if (this->_rows == other.cols()) {
            out = new SquareMatrix<T>(this->_rows);
        } else {
            out = new RectangularMatrix<T>(this->_rows, other.cols());
        }
        for(int i=0;i<this->_rows;i++){
            for(int j=0;j<other.cols();j++){
                T sum = T{};
                for(int k=0;k<this->_rows;k++){
                    sum = sum + this->data[i * this->_rows + k] * other.get(k, j);
                }
                out->set(i, j, sum);
            }
        }
        return out;
    }

    T det() const{
        if (this->_rows == 0) return T{1};
        if (this->_rows == 1) return this->data[0];
        if (this->_rows == 2) return this->data[0] * this->data[3] - this->data[1] * this->data[2];

        int n = this->_rows;
        SquareMatrix<T> L(n);
        SquareMatrix<T> U(n);

        for (int i = 0; i < n; i++) {
            L.set(i, i, T{1});
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                T sum = T{};
                for (int k = 0; k < i; k++) {
                    sum = sum + L.get(i, k) * U.get(k, j);
                }
                U.set(i, j, this->get(i, j) - sum);
            }
            for (int j = i + 1; j < n; j++) {
                T sum = T{};
                for (int k = 0; k < i; k++) {
                    sum = sum + L.get(j, k) * U.get(k, i);
                }
                if (U.get(i, i) == T{}) {
                    throw std::runtime_error("det: zero pivot encountered while counting U.");
                }
                L.set(j, i, (this->get(j, i) - sum) * linal::inverse(U.get(i, i)));
            }
        }
        T result = T{1};
        for (int i = 0; i < n; i++) {
            result = result * U.get(i, i);
        }
        return result;
    }

    Matrix<T>* clone() const override {
        return new SquareMatrix<T>(*this);
    }

    SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {
        if (this != &other) {
            delete[] this->data;
            this->_rows = other._rows;
            this->data = new T[this->_rows * this->_rows];
            for (int i = 0; i < this->_rows * this->_rows; i++) {
                this->data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~SquareMatrix() = default;
};

#endif //LAB3_SQUAREMATRIX_H
