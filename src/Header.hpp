#pragma once

#include <SFML/Graphics.hpp>

typedef long double TYPE;

template<typename T>
struct Complex
{
	T re;
	T im;

	Complex operator += (const Complex & other)
	{
		re += other.re;
		im += other.im;

		return *this;
	}

	Complex operator + (const Complex & other)
	{
		Complex c(*this);
		return c += other;
	}
	Complex operator *= (const Complex & other)
	{
		Complex c;
		c.re = re * other.re - im * other.im;
		c.im = re * other.im + im * other.re;

		*this = c;
		return *this;
	}

	Complex operator * (const Complex & other)
	{
		Complex c(*this);
		return c *= other;
	}
	Complex operator = (const Complex & other)
	{
		re = other.re;
		im = other.im;
		return *this;
	}

	Complex(): re((T)0), im((T)0)
	{
	}

	Complex(const Complex& other) : re(other.re), im(other.im)
	{
	}
	Complex(const T& re, const T& im) : re(re), im(im)
	{
	}
	Complex(const T& re) : re(re), im((T)0)
	{
	}

	T module_sqr()const
	{
		return re * re + im * im;
	}
};
