//
// Created by admin on 21.05.2025.
//

#ifndef LAB3_SPARSEMATRIX_H
#define LAB3_SPARSEMATRIX_H

#include "Matrix.h"
#include "LinkedList.h"

template <linal::Field T>
class SparseMatrix : public Matrix<T>{
public:
    SparseMatrix(int rows, int cols) : _rows(rows), _cols(cols) {
        if (rows < 0 || cols < 0) {
            throw std::invalid_argument("SparseMatrix: Matrix dimensions cannot be negative.");
        }
        data = new LinkedList<Trenode>;
    }

    SparseMatrix(const SparseMatrix<T>& other) : _rows(other._rows), _cols(other._cols) {
        data = new LinkedList<Trenode>(*(other.data));
    }

    int rows() const {
        return _rows;
    }

    int cols() const {
        return _cols;
    }

    T get(int x, int y) const {
        if(x<0 || x>=_rows || y<0 || y>=_cols){
            throw std::out_of_range("get: invalid pair of indices.");
        }
        for(int i=0;i<data->getLength();i++){
            const Trenode& node = data->get(i);
            if(node.getX() == x && node.getY() == y){
                return node.getItem();
            }
            if(node.getX() > x || (node.getX() == x && node.getY() > y)){
                break;
            }
        }
        return T{};
    }

    Matrix<T>& set(int x, int y, T item) {
        if(x<0 || x>=_rows || y<0 || y>=_cols){
            throw std::out_of_range("set: invalid pair of indices.");
        }
        for(int i=0;i<data->getLength();i++){
            const Trenode& node = data->get(i);
            if (node.getX() == x && node.getY() == y) {
                data->popAt(i);
                if (item != T{}) {
                    data->insertAt(Trenode(x, y, item), i);
                }
                return *this;
            }
            if (node.getX() > x || (node.getX() == x && node.getY() > y)) {
                if (item != T{}) {
                    data->insertAt(Trenode(x, y, item), i);
                }
                return *this;
            }
        }
        if(item != T{}){
            data->append(Trenode(x, y, item));
        }
        return *this;
    }

    Vector<T> getRow(int x) const {
        if (x < 0 || x >= _rows) {
            throw std::out_of_range("getRow: invalid row index.");
        }
        Vector<T> out(_cols);
        for(int i=0;i<data->getLength();i++){
            const Trenode& node = data->get(i);
            if(node.getX() == x){
                out.setCoord(node.getY(), node.getItem());
            }
            if(node.getX() > x){
                break;
            }
        }
        return out;
    }

    Matrix<T>& setRow(int x, const Vector<T>& vec) {
        if (x < 0 || x >= _rows) {
            throw std::out_of_range("setRow: invalid row index.");
        }
        if (vec.getDim() != _cols) {
            throw std::invalid_argument("setRow: vector size is illegal.");
        }
        int i = 0;
        while (i < data->getLength()) {
            const Trenode& node = data->get(i);
            if (node.getX() == x) {
                data->popAt(i);
            } else if (node.getX() > x) {
                break;
            } else {
                i++;
            }
        }
        for (int j = 0; j < _cols; j++) {
            if (vec.getCoord(j) != T{}) {
                int pos = 0;
                while (pos < data->getLength()) {
                    const Trenode& node = data->get(pos);
                    if (node.getX() > x || (node.getX() == x && node.getY() > j)) {
                        break;
                    }
                    pos++;
                }
                data->insertAt(Trenode(x, j, vec.getCoord(j)), pos);
            }
        }
        return *this;
    }

    Vector<T> getCol(int x) const {
        if (x < 0 || x >= _cols) {
            throw std::out_of_range("getCol: Invalid column index.");
        }
        Vector<T> result(_rows);
        for (int i = 0; i < data->getLength(); i++) {
            const Trenode& node = data->get(i);
            if (node.getY() == x) {
                result.setCoord(node.getX(), node.getItem());
            }
        }
        return result;
    }

    Matrix<T>& setCol(int x, const Vector<T>& vec) {
        if (x < 0 || x >= _cols) {
            throw std::out_of_range("setCol: Invalid column index.");
        }
        if (vec.getDim() != _rows) {
            throw std::invalid_argument("setCol: Vector size is illegal.");
        }
        int i = 0;
        while (i < data->getLength()) {
            const Trenode& node = data->get(i);
            if (node.getY() == x) {
                data->popAt(i);
            } else {
                i++;
            }
        }
        for (int j = 0; j < _rows; j++) {
            if (vec.getCoord(j) != T{}) {
                int pos = 0;
                while (pos < data->getLength()) {
                    const Trenode& node = data->get(pos);
                    if (node.getX() > j || (node.getX() == j && node.getY() > x)) {
                        break;
                    }
                    pos++;
                }
                data->insertAt(Trenode(j, x, vec.getCoord(j)), pos);
            }
        }
        return *this;
    }

    Matrix<T>* operator+(const Matrix<T>& other) const {
        if (_rows != other.rows() || _cols != other.cols()) {
            throw std::invalid_argument("+: Matrices must have the same size.");
        }
        auto* result = new SparseMatrix<T>(_rows, _cols);
        if (auto* otherS = dynamic_cast<const SparseMatrix<T>*>(&other)) {
            int cnt = 0, otherCnt = 0;
            while(cnt<data->getLength() || otherCnt<otherS->data->getLength()){
                Trenode node = (cnt<data->getLength()) ? data->get(cnt) : Trenode(_rows, _cols, T{});
                Trenode otherNode = (otherCnt<otherS->data->getLength()) ? otherS->data->get(otherCnt) : Trenode(_rows, _cols, T{});
                int x = node.getX(), y = node.getY();
                int xO = otherNode.getX(), yO = otherNode.getY();
                if(x < xO || (x == xO && y < yO)){
                    result->data->append(Trenode(x, y, node.getItem()));
                    cnt++;
                }else if(xO < x || (xO == x && yO < y)){
                    result->data->append(Trenode(xO, yO, otherNode.getItem()));
                    otherCnt++;
                }else{
                    T sum = node.getItem() + otherNode.getItem();
                    if(sum != T{}){
                        result->data->append(Trenode(xO, yO, sum));
                    }
                    cnt++;
                    otherCnt++;
                }
            }
        }else {
            int cnt = 0;
            for (int i = 0; i < _rows; i++) {
                for (int j = 0; j < _cols; j++) {
                    T sum = T{};
                    if (cnt < data->getLength()) {
                        const Trenode &node = data->get(cnt);
                        if (node.getX() == i && node.getY() == j) {
                            sum = node.getItem();
                            cnt++;
                        }
                    }
                    sum = sum + other.get(i, j);
                    if (sum != T{}) {
                        result->data->append(Trenode(i, j, sum));
                    }
                }
            }
        }
        return result;
    }

    Matrix<T>& operator+=(const Matrix<T>& other) {
        if (_rows != other.rows() || _cols != other.cols()) {
            throw std::invalid_argument("+=: Matrices must have the same size.");
        }
        Matrix<T>* temp = *this + other;
        SparseMatrix<T>* sTemp = dynamic_cast<SparseMatrix<T>*>(temp);
        delete data;
        data = new LinkedList<Trenode>(*sTemp->data);
        delete temp;
        return *this;
    }

    Matrix<T>* operator*(T item) const {
        auto* result = new SparseMatrix<T>(_rows, _cols);
        if(item != T{}) {
            for (int i = 0; i < data->getLength(); i++) {
                const Trenode &node = data->get(i);
                T new_value = node.getItem() * item;
                if (new_value != T{}) {
                    result->data->append(Trenode(node.getX(), node.getY(), new_value));
                }
            }
        }
        return result;
    }

    Matrix<T>& operator*=(T item) {
        if (item == T{}) {
            while (data->getLength() > 0) {
                data->popForward();
            }
            return *this;
        }
        for(int i=0;i<data->getLength();i++){
            const Trenode& node = data->get(i);
            T mult = node.getItem() * item;
            if (mult != T{}) {
                data->popAt(i);
                data->insertAt(Trenode(node.getX(), node.getY(), mult), i);
            } else {
                data->popAt(i);
                i--;
            }
        }
        return *this;
    }

    Matrix<T>* operator*(const Matrix<T>& other) const {
        if (_cols != other.rows()) {
            throw std::invalid_argument("*: matrix must have connectable size to be multiplied to each other.");
        }
        Matrix<T>* result = new SparseMatrix<T>(_rows, other.cols());
        if (auto* otherS = dynamic_cast<const SparseMatrix<T>*>(&other)) {
            for (int i = 0; i < data->getLength(); i++) {
                const Trenode& node = data->get(i);
                int x = node.getX(), y = node.getY();
                for (int j = 0; j < otherS->data->getLength(); j++) {
                    const Trenode& otherNode = otherS->data->get(j);
                    if (otherNode.getX() == y) {
                        int col = otherNode.getY();
                        T sum = result->get(x, col) + node.getItem() * otherNode.getItem();
                        if (sum != T{}) {
                            result->set(x, col, sum);
                        }
                    }else if(otherNode.getX() > y){
                        break;
                    }
                }
            }
        }else{
            for (int i = 0; i < data->getLength(); i++) {
                const Trenode &node = data->get(i);
                int x = node.getX(), y = node.getY();
                for (int j = 0; j < other.cols(); j++) {
                    T sum = result->get(x, j) + node.getItem() * other.get(y, j);
                    if (sum != T{}) {
                        result->set(x, j, sum);
                    }
                }
            }
        }
        return result;
    }

    Matrix<T>& swapRows(int x, int y) {
        if (x < 0 || x >= _rows || y < 0 || y >= _rows) {
            throw std::out_of_range("swapRows: Invalid row indices.");
        }
        Vector<T> temp = getRow(x);
        setRow(x, getRow(y));
        setRow(y, temp);
        return *this;
    }

    Matrix<T>& swapCols(int x, int y) {
        if (x < 0 || x >= _cols || y < 0 || y >= _cols) {
            throw std::out_of_range("swapCols: Invalid column indices.");
        }
        Vector<T> temp = getCol(x);
        setCol(x, getCol(y));
        setCol(y, temp);
        return *this;
    }

    Matrix<T>& mulRow(int x, T mul) {
        if(x<0 || x>=_rows){
            throw std::out_of_range("mulRows: invalid row index.");
        }
        setRow(x, getRow(x) * mul);
        return *this;
    }

    Matrix<T>& mulCol(int x, T mul) {
        if(x<0 || x>=_cols){
            throw std::out_of_range("mulCols: invalid column index.");
        }
        setCol(x, getCol(x) * mul);
        return *this;
    }

    Matrix<T>& combRows(int to, int from, T mul) {
        if(to<0 || to>=_rows || from<0 || from>=_rows){
            throw std::out_of_range("combRows: invalid row index.");
        }
        setRow(to, getRow(to) + getRow(from) * mul);
        return *this;
    }

    Matrix<T>& combCols(int to, int from, T mul) {
        if(to<0 || to>=_cols || from<0 || from>=_cols){
            throw std::out_of_range("combCols: invalid column index.");
        }
        setCol(to, getCol(to) + getCol(from) * mul);
        return *this;
    }

    double norm() const {
        static_assert(linal::EuclideanField<T>, "norm: type T must satisfy EuclideanField for norm.");
        double out = 0.0;
        for (int i = 0; i < data->getLength(); i++) {
            double a = linal::abs(data->get(i).getItem());
            out += a * a;
        }
        return std::sqrt(out);
    }

    Matrix<T>* clone() const {
        return new SparseMatrix<T>(*this);
    }

    SparseMatrix<T>& operator=(const SparseMatrix<T>& other) {
        if (this != &other) {
            delete data;
            _rows = other._rows;
            _cols = other._cols;
            data = new LinkedList<Trenode>(*(other.data));
        }
        return *this;
    }

    bool operator==(const SparseMatrix<T>& other) const {
        if (_rows != other._rows || _cols != other._cols) return false;
        if (data->getLength() != other.data->getLength()) return false;
        for (int i = 0; i < data->getLength(); ++i) {
            const Trenode& n1 = data->get(i);
            const Trenode& n2 = other.data->get(i);
            if (n1.getX() != n2.getX() || n1.getY() != n2.getY() || std::abs(n1.getItem() - n2.getItem()) > 1e-6) {
                return false;
            }
        }
        return true;
    }

    ~SparseMatrix() {
        delete data;
    }
private:
    class Trenode {
    public:
        Trenode(int x, int y, T item) : x(x), y(y), item(item) {}
        int getX() const { return x; }
        int getY() const { return y; }
        T getItem() const { return item; }
    private:
        int x;
        int y;
        T item;
    };

    int _rows;
    int _cols;
    LinkedList<Trenode>* data;

};
#endif //LAB3_SPARSEMATRIX_H
