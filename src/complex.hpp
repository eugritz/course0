#pragma once

#include <SFML/Graphics.hpp>

typedef long double Real;

template<typename T>
class Complex {
public:
    T re, im;

    Complex() : re((T)0), im((T)0) {}
    Complex(const Complex &other) : re(other.re), im(other.im) {}
    Complex(const T &re, const T &im) : re(re), im(im) {}
    Complex(const T &re) : re(re), im((T)0) {}

    Complex operator+=(const Complex &other) {
        re += other.re;
        im += other.im;
        return *this;
    }

    Complex operator+(const Complex &other) {
        Complex c(*this);
        return c += other;
    }

    Complex operator*=(const Complex &other) {
        T r = re * other.re - im * other.im;
        T i = re * other.im + im * other.re;
        re = r;
        im = i;
        return *this;
    }

    Complex operator*(const Complex &other) {
        T r = re * other.re - im * other.im;
        T i = re * other.im + im * other.re;
        Complex c(r, i);
        return c;
    }

    Complex operator=(const Complex &other) {
        re = other.re;
        im = other.im;
        return *this;
    }

    T module_sqr() const {
        return re * re + im * im;
    }
};
