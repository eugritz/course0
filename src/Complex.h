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

    Complex operator+=(const Complex &other);
    Complex operator+(const Complex &other);
    Complex operator*=(const Complex &other);
    Complex operator*(const Complex &other);
    Complex operator=(const Complex &other);

    T module_sqr() const;
};

#include "Complex.inl"
