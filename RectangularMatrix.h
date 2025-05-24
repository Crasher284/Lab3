//
// Created by admin on 19.05.2025.
//

#ifndef LAB3_RECTANGULARMATRIX_H
#define LAB3_RECTANGULARMATRIX_H

#include "Matrix.h" //also Vector and Linal

template <linal::Field T>
class RectangularMatrix : public Matrix<T>{
public:
    RectangularMatrix(int rows, int cols) : _rows(rows), _cols(cols) {
        if(rows < 0 || cols < 0){
            throw std::invalid_argument("RectangularMatrix: Matrix size cannot be negative.");
        }
        data = new T[rows * cols];
        for(int i=0;i<rows * cols;i++){
            data[i] = T{};
        }
    }

    RectangularMatrix(int rows, int cols, T* array) : _rows(rows), _cols(cols){
        if(rows < 0 || cols < 0){
            throw std::invalid_argument("RectangularMatrix: Matrix size cannot be negative.");
        }
        if (!array && rows > 0 && cols > 0) {
            throw std::invalid_argument("RectangularMatrix: Null array provided for non-zero dimension..");
        }
        data = new T[rows * cols];
        for(int i=0;i<rows * cols;i++){
            if(array){
                data[i] = array[i];
            }else{
                data[i] = T{};
            }
        }
    }

    RectangularMatrix(const RectangularMatrix<T>& other) : _rows(other._rows), _cols(other._cols) {
        data = new T[_rows * _cols];
        for (int i = 0; i < _rows * _cols; i++) {
            data[i] = other.data[i];
        }
    }

    RectangularMatrix<T>& operator=(const RectangularMatrix<T>& other) {
        if (this != &other) {
            delete[] data;
            _rows = other._rows;
            _cols = other._cols;
            data = new T[_rows * _cols];
            for (int i = 0; i < _rows * _cols; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    int rows() const override { return _rows; }

    int cols() const override { return _cols; }

    T get(int x, int y) const override {
        if(x<0 || x>=_rows || y<0 || y>=_cols){
            throw std::out_of_range("get: invalid pair of indices.");
        }
        return data[x * _cols + y];
    }

    Matrix<T>& set(int x, int y, T item) override {
        if(x<0 || x>=_rows || y<0 || y>=_cols){
            throw std::out_of_range("set: invalid pair of indices.");
        }
        data[x * _cols + y] = item;
        return *this;
    }

    Vector<T> getRow(int x) const override {
        if (x < 0 || x >= _rows) {
            throw std::out_of_range("getRow: invalid row index.");
        }
        Vector<T> out(_cols);
        for(int i=0;i<_cols;i++){
            out.setCoord(i, data[x * _cols + i]);
        }
        return out;
    }

    Matrix<T>& setRow(int x, const Vector<T>& vec) override {
        if (x < 0 || x >= _rows) {
            throw std::out_of_range("setRow: invalid row index.");
        }
        if(vec.getDim() != _cols){
            throw std::invalid_argument("setRow: vector size is illegal.");
        }
        for(int i=0;i<_cols;i++) {
            data[x * _cols + i] = vec.getCoord(i);
        }
        return *this;
    }

    Vector<T> getCol(int x) const override {
        if (x < 0 || x >= _cols) {
            throw std::out_of_range("getCol: invalid row index.");
        }
        Vector<T> out(_rows);
        for(int i=0;i<_rows;i++){
            out.setCoord(i, data[i * _cols + x]);
        }
        return out;
    }

    Matrix<T>& setCol(int x, const Vector<T>& vec) override {
        if (x < 0 || x >= _cols) {
            throw std::out_of_range("setCol: invalid row index.");
        }
        if(vec.getDim() != _rows){
            throw std::invalid_argument("setCol: vector size is illegal.");
        }
        for(int i=0;i<_rows;i++) {
            data[i * _cols + x] = vec.getCoord(i);
        }
        return *this;
    }

    Matrix<T>* operator+(const Matrix<T>& other) const override {
        if(_rows != other.rows() || _cols != other.cols()){
            throw std::invalid_argument("+: matrix must have same size to be added to each other.");
        }
        Matrix<T>* out = new RectangularMatrix<T>(_rows, _cols);
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                out->set(i, j, data[i * _cols + j] + other.get(i, j));
            }
        }
        return out;
    }

    Matrix<T>& operator+=(const Matrix<T>& other) override {
        if(_rows != other.rows() || _cols != other.cols()){
            throw std::invalid_argument("+=: matrix must have same size to be added to each other.");
        }
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                data[i * _cols + j] = data[i * _cols + j] + other.get(i, j);
            }
        }
        return *this;
    }

    Matrix<T>* operator*(T item) const override {
        Matrix<T>* out = new RectangularMatrix<T>(_rows, _cols);
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                out->set(i, j, data[i * _cols + j] * item);
            }
        }
        return out;
    }

    Matrix<T>& operator*=(T item) override {
        for(int i=0;i<_rows;i++){
            for(int j=0;j<_cols;j++){
                data[i * _cols + j] = data[i * _cols + j] * item;
            }
        }
        return *this;
    }

    Matrix<T>* operator*(const Matrix<T>& other) const override {
        if(_cols != other.rows()){
            throw std::invalid_argument("*: matrix must have connectable size to be multiplied to each other.");
        }
        Matrix<T>* out = new RectangularMatrix<T>(_rows, other.cols());
        for(int i=0;i<_rows;i++){
            for(int j=0;j<other.cols();j++){
                T sum = T{};
                for(int k=0;k<_cols;k++){
                    sum = sum + data[i * _cols + k] * other.get(k, j);
                }
                out->set(i, j, sum);
            }
        }
        return out;
    }

    Matrix<T>& swapRows(int x, int y) override {
        if(x<0 || x>=_rows || y<0 || y>=_rows){
            throw std::out_of_range("swapRows: invalid row index.");
        }
        Vector<T> temp = getRow(x);
        setRow(x, getRow(y));
        setRow(y, temp);
        return *this;
    }

    Matrix<T>& swapCols(int x, int y) override {
        if(x<0 || x>=_cols || y<0 || y>=_cols){
            throw std::out_of_range("swapCols: invalid column index.");
        }
        Vector<T> temp = getCol(x);
        setCol(x, getCol(y));
        setCol(y, temp);
        return *this;
    }

    Matrix<T>& mulRow(int x, T mul) override {
        if(x<0 || x>=_rows){
            throw std::out_of_range("mulRows: invalid row index.");
        }
        setRow(x, getRow(x) * mul);
        return *this;
    }

    Matrix<T>& mulCol(int x, T mul) override {
        if(x<0 || x>=_cols){
            throw std::out_of_range("mulCols: invalid column index.");
        }
        setCol(x, getCol(x) * mul);
        return *this;
    }

    Matrix<T>& combRows(int to, int from, T mul) override {
        if(to<0 || to>=_rows || from<0 || from>=_rows){
            throw std::out_of_range("combRows: invalid row index.");
        }
        setRow(to, getRow(to) + getRow(from) * mul);
        return *this;
    }

    Matrix<T>& combCols(int to, int from, T mul) override {
        if(to<0 || to>=_cols || from<0 || from>=_cols){
            throw std::out_of_range("combCols: invalid column index.");
        }
        setCol(to, getCol(to) + getCol(from) * mul);
        return *this;
    }

    double norm() const override {
        static_assert(linal::EuclideanField<T>, "norm: type T must satisfy EuclideanField for norm.");
        double out = 0.0;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                double a = linal::abs(data[i * _cols + j]);
                out += a * a;
            }
        }
        return std::sqrt(out);
    }

    Matrix<T>* clone() const override {
        return new RectangularMatrix<T>(*this);
    }

    ~RectangularMatrix() {
        delete[] data;
    }
protected:
    int _rows;
    int _cols;
    T* data;
};

#endif //LAB3_RECTANGULARMATRIX_H
