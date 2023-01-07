/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/01/07 23:52:01 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"

Complex::Complex():
	_re(0),
	_im(0) {}

Complex::~Complex() {}

Complex::Complex(long double x):
	_re(x),
	_im(0) {}

Complex::Complex(long double x, long double y):
	_re(x),
	_im(y) {}

Complex::Complex(const std::string&& buf):
	_re(0),
	_im(0) { (void)buf; }

Complex::Complex(const Complex& x):
	_re(x.getReal()),
	_im(x.getImaginary()) {}

Complex& Complex::operator=(long double rhs) {
	if (isReal() && getReal() == rhs)
		return *this;
	_re = rhs._re;
	_im = 0;
	return *this;
}

Complex& Complex::operator=(const Complex& rhs) {
	if (this == &rhs)
		return *this;
	_re = rhs._re;
	_im = rhs._im;
	return *this;
}

/* Getters ******************************************/

const Rational& Complex::getReal() const {
	return _re;
}

const Rational& Complex::getImaginary() const {
	return _im;
}

/* Other ********************************************/

bool	Complex::isReal() const {
	return getImaginary().getVal();
}

bool	Complex::isImaginary() const {
	return !isReal();
}

/* Relational operators *****************************/

Complex&		Complex::operator+=(const Complex& rhs) {
	_re += rhs.getReal();
	_im += rhs.getImaginary();
	return *this;
}

Complex			Complex::operator+(const Complex& rhs) {
	Complex tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Complex&		Complex::operator-=(const Complex& rhs) {
	_re -= rhs.getReal();
	_im -= rhs.getImaginary();
	return *this;
}
Complex			Complex::operator-(const Complex& rhs) {
	Complex tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

//TODO
Complex&		Complex::operator*=(const Complex& rhs) {
	return *this;
}

Complex			Complex::operator*(const Complex& rhs) {
	return *this;
}

//TODO
Complex&		Complex::operator/=(const Complex& rhs) {
	return *this;
}

Complex			Complex::operator/(const Complex& rhs) {
	return *this;
}

/* Relational operators *****************************/

bool operator==(const Complex& x, const Complex& y) {
	return x.getReal() == y.getReal() && x.getImaginary() == y.getImaginary();
}

/* I/O stream operator *****************************/

// TODO: change up
std::ostream& operator<<(std::ostream& o, const Complex& x) {
	// if (!x.getReal() && !x.getImaginary()) {
	// 	o << '0';
	// 	return o;
	// }
	// if (x.getReal())
	// 	o << x.getReal();
	// if (x.getImaginary())
	// 	o << 'i' << x.getImaginary();
	if (is)
	(void)o; (void)x;
	return o;
}
