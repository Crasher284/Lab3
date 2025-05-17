//
// Created by admin on 17.05.2025.
//

#ifndef LAB3_COMPLEX_H
#define LAB3_COMPLEX_H

#include <cmath>

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : real_(real), imag_(imag) {}

    double real() const{
        return real_;
    }

    double imag() const{
        return imag_;
    }

    Complex operator+(const Complex& other) const{
        return {real_ + other.real_, imag_ + other.imag_};
    }

    Complex operator*(const Complex& other) const {
        return {real_ * other.real_ - imag_ * other.imag_,
                       real_ * other.imag_ + imag_ * other.real_};
    }

    Complex operator-() const {
        return {-real_, -imag_};
    }

    Complex conjugate() const {
        return {real_, -imag_};
    }

    double abs() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }

    bool operator==(const Complex& other) const{
        return real_ == other.real_ && imag_ == other.imag_;
    }
private:
    double real_;
    double imag_;
};

std::ostream& operator<< (std::ostream& os, Complex z){
    os << "{Re: " << z.real() << ", Im: " << z.imag() << "}";
    return os;
}

namespace linal {
    float conjugate(float x) { return x; }

    double conjugate(double x) { return x; }

    long double conjugate(long double x) { return x; }

    Complex conjugate(Complex z) { return z.conjugate(); }

    float abs(float x) { return std::abs(x); }

    double abs(double x) { return std::abs(x); }

    long double abs(long double x) { return std::abs(x); }

    double abs(Complex z) { return z.abs(); }
}

#endif //LAB3_COMPLEX_H
