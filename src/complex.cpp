/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/01/08 20:41:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"
#include "math.hpp"

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

Complex::Complex(const Rational& x, const Rational& y):
	_re(x),
	_im(y) {}

Complex::Complex(const std::string&& buf) {
	_parseBuf(buf);
}

Complex::Complex(const Complex& x):
	_re(x.getReal()),
	_im(x.getImaginary()) {}

Complex& Complex::operator=(long double rhs) {
	if (isReal() && getReal() == rhs)
		return *this;
	_re = rhs;
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

/* Relational operators *****************************/

Complex& Complex::conjugate() {
	_im.operator-();
	return *this;
}

Complex& Complex::rationalize() {
	const Complex tmp(*this);

	_re = tmp.getReal() * tmp.getReal();
	_im = -(tmp.getImaginary() * tmp.getImaginary());
	return *this;
}

Complex& Complex::operator+=(const Complex& rhs) {
	_re += rhs.getReal();
	_im += rhs.getImaginary();
	return *this;
}

Complex Complex::operator+(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Complex& Complex::operator-=(const Complex& rhs) {
	_re -= rhs.getReal();
	_im -= rhs.getImaginary();
	return *this;
}

Complex Complex::operator-(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

Complex Complex::operator-() const {
	return Complex(-this->getReal(), -this->getImaginary());
}

Complex& Complex::operator*=(const Complex& rhs) {
	const Complex	tmp(*this);
	_re = (tmp.getReal() * rhs.getReal()) - (tmp.getImaginary() * rhs.getImaginary());
	_im = (tmp.getReal() * rhs.getImaginary()) + (tmp.getImaginary() * rhs.getReal());
	return *this;
}

Complex Complex::operator*(const Complex& rhs) const {
	Complex	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Complex& Complex::operator/=(const Complex& rhs) {
	Complex	conj(rhs);
	conj.conjugate();

	Complex	den(rhs * conj);
	Complex	num(*this * conj);

	_re = num.getReal() / den.getReal();
	_im = num.getImaginary() / den.getReal();
	return *this;
}

Complex Complex::operator/(const Complex& rhs) const {
	Complex	tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

/* Getters ******************************************/

const Rational& Complex::getReal() const {
	return _re;
}

const Rational& Complex::getImaginary() const {
	return _im;
}

/* Other ********************************************/

bool	Complex::isComplex() const {
	return getImaginary().getVal() && getReal().getVal();
}

bool	Complex::isReal() const {
	return !getImaginary().getVal();
}

bool	Complex::isImaginary() const {
	return !isReal();
}

void	Complex::_parseBuf(const std::string& buf) {
	size_t	pos;
	long double ld = std::stold(buf, &pos);

	_re = Rational(ld);
	_im = Rational(std::string(buf.c_str() + pos));
}

/* Relational operators *****************************/

bool operator==(const Complex& x, const Complex& y) {
	return x.getReal() == y.getReal() && x.getImaginary() == y.getImaginary();
}

bool operator!=(const Complex& x, const Complex& y) {
	return !operator==(x,y);
}

/* I/O stream operator *****************************/

std::ostream& operator<<(std::ostream& o, const Complex& x) {
	if (x.isComplex()) {
		o << x.getReal();
		if (x.getImaginary() > 0)
			o << " + ";
		else if (x.getImaginary() < 0)
			o << " - ";
		o << math::abs(x.getImaginary()) << 'i';
	} else if (x.isReal()) {
		o << x.getReal();
	} else if (x.isImaginary()) {
		o << x.getImaginary() << 'i';
	}
	return o;
}