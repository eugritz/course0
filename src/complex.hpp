#pragma once

#include <SFML/Graphics.hpp>

typedef long double Real;

template<typename T>
class Complex {
    T _re, _im;

public:
    Complex() : _re((T)0), _im((T)0) {}
    Complex(const Complex &other) : _re(other._re), _im(other._im) {}
    Complex(const T &re, const T &im) : _re(re), _im(im) {}
    Complex(const T &re) : _re(re), _im((T)0) {}

    Complex operator+=(const Complex &other) {
        _re += other._re;
        _im += other._im;
        return *this;
    }

    Complex operator+(const Complex &other) {
        Complex c(*this);
        return c += other;
    }

    Complex operator*=(const Complex &other) {
        Complex c;
        c._re = _re * other._re - _im * other._im;
        c._im = _re * other._im + _im * other._re;

        *this = c;
        return *this;
    }

    Complex operator*(const Complex &other) {
        Complex c(*this);
        return c *= other;
    }

    Complex operator=(const Complex &other) {
        _re = other._re;
        _im = other._im;
        return *this;
    }

    T module_sqr() const {
        return _re * _re + _im * _im;
    }
};
