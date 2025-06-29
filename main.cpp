#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "Vector.h"
#include "RectangularMatrix.h"
#include "SquareMatrix.h"
#include "SparseMatrix.h"

std::vector<std::string> parser(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> words;
    std::string word;

    while (ss >> word) words.push_back(word);

    return words;
}

int main() {
    std::ofstream out("Result.out");
    std::ifstream in("ListTests.in");
    if (!out.is_open()) {
        std::cerr << "Could not open Result.out.";
        return 1;
    }
    if (!in.is_open()) {
        std::cerr << "Could not open ListTests.in.";
        return 1;
    }
    std::string line, name, method;
    auto* stack = new Stack<int>;
    auto* queue = new Queue<int>;
    auto* deque = new Deque<int>;
    int cnt=-1, mxCnt, pCnt, bCnt;
    while(std::getline(in, line)){
        std::vector<std::string> words = parser(line);
        if(words.empty()){
            continue;
        }else if(words.size() == 1){
            if(cnt == -1) {
                std::cerr << "Corrupted tests.";
                return 1;
            }
            out << "Group \"" << name << "\": " << mxCnt << " started, " << pCnt << " passed, " << mxCnt - pCnt - bCnt << " failed, " << bCnt << " broke." << std::endl;
        }else if(words.size() == 2) {
            cnt = 0; pCnt = 0; bCnt = 0;
            name = words[0];
            mxCnt = std::stoi(words[1]);
            out << "Starting group \"" << name << "\", " << mxCnt << " tests ahead...";
        }else{
            method = words[0];
            cnt++;
            try {
                if (name == "Stack") {
                    if (method == "push") {
                        stack->push(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }else if (method == "get") {
                        const int temp = stack->get();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "pop") {
                        const int temp = stack->pop();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "size") {
                        const int temp = stack->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "isEmpty") {
                        const std::string temp = stack->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "clear") {
                        stack->clear();
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }
                } else if (name == "Queue") {
                    if (method == "push") {
                        queue->push(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "get") {
                        const int temp = queue->get();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "pop") {
                        const int temp = queue->pop();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "size") {
                        const int temp = queue->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "isEmpty") {
                        const std::string temp = queue->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "clear") {
                        queue->clear();
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }
                } else if (name == "Deque") {
                    if (method == "prepend") {
                        deque->prepend(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "append") {
                        deque->append(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "first") {
                        const int temp = deque->first();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "last") {
                        const int temp = deque->last();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "popFirst") {
                        const int temp = deque->popFirst();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "popLast") {
                        const int temp = deque->popLast();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "size") {
                        const int temp = deque->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "isEmpty") {
                        const std::string temp = deque->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    }
                }
            } catch (const std::exception& error){
                if(words[2] == "BROKEN"){
                    pCnt++;
                    out << "Test " << cnt << ", result: passed, error: " << error.what();
                }else{
                    bCnt++;
                    out << "Test " << cnt << ", answer: " << words[2] << ", result: broken, error: " << error.what();
                }
            }
        }
        out << std::endl;
    }
    delete stack;
    delete queue;
    delete deque;
    in.close();

    std::ifstream in_matrix("MatrixTests.in");
    if (!in_matrix.is_open()) {
        std::cerr << "Could not open MatrixTests.in.";
        return 1;
    }
    auto* vector = new Vector<double>(0);
    auto* rectMatrix = new RectangularMatrix<double>(0, 0);
    auto* squareMatrix = new SquareMatrix<double>(0);
    auto* sparseMatrix = new SparseMatrix<double>(0, 0);
    cnt = -1; pCnt = 0; mxCnt = 0; bCnt = 0;
    while (std::getline(in_matrix, line)) {
        std::vector<std::string> words = parser(line);
        if (words.empty()) {
            continue;
        } else if (words.size() == 1) {
            if (cnt == -1) {
                std::cerr << "Corrupted tests.";
                return 1;
            }
            out << "Group \"" << name << "\": " << mxCnt << " started, " << pCnt << " passed, " << mxCnt - pCnt - bCnt << " failed, " << bCnt << " broke." << std::endl;
        } else if (words.size() == 2) {
            cnt = 0; pCnt = 0; bCnt = 0;
            name = words[0];
            mxCnt = std::stoi(words[1]);
            out << "Starting group \"" << name << "\", " << mxCnt << " tests ahead...";
        } else {
            method = words[0];
            cnt++;
            try {
                if (name == "Vector") {
                    if (method == "create") {
                        *vector = Vector<double>(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "setCoord") {
                        vector->setCoord(std::stoi(words[1]), std::stod(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "getCoord") {
                        const double temp = vector->getCoord(std::stoi(words[1]));
                        const double ans = std::stod(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "operator+") {
                        Vector<double> v1(3), v2(3);
                        for (int i = 0; i < 3; ++i) v1.setCoord(i, std::stod(words[1 + i]));
                        for (int i = 0; i < 3; ++i) v2.setCoord(i, std::stod(words[4 + i]));
                        auto temp = v1 + v2;
                        Vector<double> ans(3);
                        for (int i = 0; i < 3; ++i) ans.setCoord(i, std::stod(words[7 + i]));
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "operator*") {
                        auto temp = *vector * std::stod(words[1]);
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "norm") {
                        NormType norm_type = words[1] == "L1" ? L1 : (words[1] == "L2" ? L2 : LInf);
                        const double temp = vector->norm(norm_type);
                        const double ans = std::stod(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "scalar_product") {
                        Vector<double> v(3);
                        for (int i = 0; i < 3; ++i) v.setCoord(i, std::stod(words[1 + i]));
                        const double temp = vector->scalar_product(v);
                        const double ans = std::stod(words[4]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    }
                } else if (name == "RectangularMatrix") {
                    if (method == "create") {
                        *rectMatrix = RectangularMatrix<double>(std::stoi(words[1]), std::stoi(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "set") {
                        rectMatrix->set(std::stoi(words[1]), std::stoi(words[2]), std::stod(words[3]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "get") {
                        const double temp = rectMatrix->get(std::stoi(words[1]), std::stoi(words[2]));
                        const double ans = std::stod(words[3]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "operator+") {
                        RectangularMatrix<double> other(2, 3);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) other.set(i, j, std::stod(words[1 + i * 3 + j]));
                        auto* temp = *rectMatrix + other;
                        RectangularMatrix<double> ans(2, 3);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[7 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<RectangularMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "operator*" && words[1] == "scalar") {
                        auto* temp = *rectMatrix * std::stod(words[2]);
                        RectangularMatrix<double> ans(2, 3);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[3 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<RectangularMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "operator*") {
                        RectangularMatrix<double> m(3, 2);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) m.set(i, j, std::stod(words[1 + i * 2 + j]));
                        auto* temp = *rectMatrix * m;
                        RectangularMatrix<double> ans(2, 2);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) ans.set(i, j, std::stod(words[7 + i * 2 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<RectangularMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "swapRows") {
                        rectMatrix->swapRows(std::stoi(words[1]), std::stoi(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "mulRow") {
                        rectMatrix->mulRow(std::stoi(words[1]), std::stod(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "combRows") {
                        rectMatrix->combRows(std::stoi(words[1]), std::stoi(words[2]), std::stod(words[3]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "norm") {
                        const double temp = rectMatrix->norm();
                        const double ans = std::stod(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "clone") {
                        auto* temp = rectMatrix->clone();
                        RectangularMatrix<double> ans(2, 3);
                        for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[2 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<RectangularMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    }
                } else if (name == "SquareMatrix") {
                    if (method == "create") {
                        *squareMatrix = SquareMatrix<double>(std::stoi(words[1]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "set") {
                        squareMatrix->set(std::stoi(words[1]), std::stoi(words[2]), std::stod(words[3]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "det") {
                        const double temp = squareMatrix->det();
                        const double ans = std::stod(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    }
                } else if (name == "SparseMatrix") {
                    if (method == "create") {
                        *sparseMatrix = SparseMatrix<double>(std::stoi(words[1]), std::stoi(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "set") {
                        sparseMatrix->set(std::stoi(words[1]), std::stoi(words[2]), std::stod(words[3]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "get") {
                        const double temp = sparseMatrix->get(std::stoi(words[1]), std::stoi(words[2]));
                        const double ans = std::stod(words[3]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "operator+") {
                        SparseMatrix<double> m1(3, 3), other(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) other.set(i, j, std::stod(words[1 + i * 3 + j]));
                        auto* temp = *sparseMatrix + other;
                        SparseMatrix<double> ans(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[10 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<SparseMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "operator*" && words[1] == "scalar") {
                        auto* temp = *sparseMatrix * std::stod(words[2]);
                        SparseMatrix<double> ans(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[3 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<SparseMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "operator*") {
                        SparseMatrix<double> m(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) m.set(i, j, std::stod(words[1 + i * 3 + j]));
                        auto* temp = *sparseMatrix * m;
                        SparseMatrix<double> ans(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[10 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<SparseMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    } else if (method == "swapRows") {
                        sparseMatrix->swapRows(std::stoi(words[1]), std::stoi(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "mulRow") {
                        sparseMatrix->mulRow(std::stoi(words[1]), std::stod(words[2]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "combRows") {
                        sparseMatrix->combRows(std::stoi(words[1]), std::stoi(words[2]), std::stod(words[3]));
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "norm") {
                        const double temp = sparseMatrix->norm();
                        const double ans = std::stod(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (std::abs(temp - ans) < 1e-5) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "clone") {
                        auto* temp = sparseMatrix->clone();
                        SparseMatrix<double> ans(3, 3);
                        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) ans.set(i, j, std::stod(words[1 + i * 3 + j]));
                        out << "Test " << cnt << ", output: " << *temp << ", answer: " << ans << ", result: ";
                        if (*dynamic_cast<SparseMatrix<double>*>(temp) == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                        delete temp;
                    }
                }
            } catch (const std::exception& error) {
                if (words[words.size() - 1] == "BROKEN") {
                    pCnt++;
                    out << "Test " << cnt << ", result: passed, error: " << error.what();
                } else {
                    bCnt++;
                    out << "Test " << cnt << ", answer: " << words[words.size() - 1] << ", result: broken, error: " << error.what();
                }
            }
        }
        out << std::endl;
    }
    delete vector;
    delete rectMatrix;
    delete squareMatrix;
    delete sparseMatrix;
    in_matrix.close();

    std::ifstream in_string("StringTests.in");
    if (!in_string.is_open()) {
        std::cerr << "Could not open StringTests.in.";
        return 1;
    }
    auto* stackN = new Stack<std::string>;
    auto* queueN = new Queue<std::string>;
    auto* dequeN = new Deque<std::string>;
    cnt = -1; pCnt = 0; mxCnt = 0; bCnt = 0;
    while(std::getline(in_string, line)){
        std::vector<std::string> words = parser(line);
        if(words.empty()){
            continue;
        }else if(words.size() == 1){
            if(cnt == -1) {
                std::cerr << "Corrupted tests.";
                return 1;
            }
            out << "Group \"" << name << "\": " << mxCnt << " started, " << pCnt << " passed, " << mxCnt - pCnt - bCnt << " failed, " << bCnt << " broke." << std::endl;
        }else if(words.size() == 2) {
            cnt = 0; pCnt = 0; bCnt = 0;
            name = words[0];
            mxCnt = std::stoi(words[1]);
            out << "Starting group \"" << name << "\", " << mxCnt << " tests ahead...";
        }else{
            method = words[0];
            cnt++;
            try {
                if (name == "Stack") {
                    if (method == "push") {
                        stackN->push(words[1]);
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }else if (method == "get") {
                        const std::string temp = stackN->get();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "pop") {
                        const std::string temp = stackN->pop();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "size") {
                        const int temp = stackN->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "isEmpty") {
                        const std::string temp = stackN->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if(temp == ans){
                            pCnt++;
                            out << "passed.";
                        }else{
                            out << "failed.";
                        }
                    }else if (method == "clear") {
                        stackN->clear();
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }
                } else if (name == "Queue") {
                    if (method == "push") {
                        queueN->push(words[1]);
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "get") {
                        const std::string temp = queueN->get();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "pop") {
                        const std::string temp = queueN->pop();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "size") {
                        const int temp = queueN->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "isEmpty") {
                        const std::string temp = queueN->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "clear") {
                        queueN->clear();
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    }
                } else if (name == "Deque") {
                    if (method == "prepend") {
                        dequeN->prepend(words[1]);
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "append") {
                        dequeN->append(words[1]);
                        pCnt++;
                        out << "Test " << cnt << ", result: passed.";
                    } else if (method == "first") {
                        const std::string temp = dequeN->first();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "last") {
                        const std::string temp = dequeN->last();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "popFirst") {
                        const std::string temp = dequeN->popFirst();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "popLast") {
                        const std::string temp = dequeN->popLast();
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "size") {
                        const int temp = dequeN->size();
                        const int ans = std::stoi(words[2]);
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    } else if (method == "isEmpty") {
                        const std::string temp = dequeN->isEmpty() ? "1" : "0";
                        const std::string& ans = words[2];
                        out << "Test " << cnt << ", output: " << temp << ", answer: " << ans << ", result: ";
                        if (temp == ans) {
                            pCnt++;
                            out << "passed.";
                        } else {
                            out << "failed.";
                        }
                    }
                }
            } catch (const std::exception& error){
                if(words[2] == "BROKEN"){
                    pCnt++;
                    out << "Test " << cnt << ", result: passed, error: " << error.what();
                }else{
                    bCnt++;
                    out << "Test " << cnt << ", answer: " << words[2] << ", result: broken, error: " << error.what();
                }
            }
        }
        out << std::endl;
    }
    delete stackN;
    delete queueN;
    delete dequeN;
    in_string.close();
    out.close();
}