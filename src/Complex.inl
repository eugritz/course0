#pragma once

#include "Complex.h"

template<typename T>
Complex<T> Complex<T>::operator+=(const Complex &other) {
    re += other.re;
    im += other.im;
    return *this;
}

template<typename T>
inline Complex<T> Complex<T>::operator+(const Complex &other) {
    Complex c(*this);
    return c += other;
}

template<typename T>
inline Complex<T> Complex<T>::operator*=(const Complex &other) {
    T r = re * other.re - im * other.im;
    T i = re * other.im + im * other.re;
    re = r;
    im = i;
    return *this;
}

template<typename T>
inline Complex<T> Complex<T>::operator*(const Complex &other) {
    T r = re * other.re - im * other.im;
    T i = re * other.im + im * other.re;
    Complex c(r, i);
    return c;
}

template<typename T>
inline Complex<T> Complex<T>::operator=(const Complex &other) {
    re = other.re;
    im = other.im;
    return *this;
}

template<typename T>
inline T Complex<T>::module_sqr() const {
    return re * re + im * im;
}
