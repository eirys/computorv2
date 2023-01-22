/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/01/22 18:16:27 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"
#include "math.hpp"

Complex::Complex():
	_re(0),
	_im(0) {}

Complex::~Complex() {}

Complex::Complex(const Rational& x, const Rational& y):
	_re(x),
	_im(y) {
		LOG("Complex rational");
}

Complex::Complex(const std::string&& buf) {
	LOG("Complex buf");
	_parseBuf(buf);
}

Complex::Complex(const Complex& x):
	// Aaatreenode(_left, _right),
	_re(x.getReal()),
	_im(x.getImaginary()) {
		LOG("Complex copy");
}

Complex& Complex::operator=(const Rational& rhs) {
	if (isReal() && getReal() == rhs)
		return *this;
	_re = rhs;
	_im = 0;
	return *this;
}

Complex& Complex::operator=(const Complex& rhs) {
	if (this == &rhs)
		return *this;
	_re = rhs.getReal();
	_im = rhs.getImaginary();
	return *this;
}

/* Arith operators **********************************/

Complex::shared_itype	Complex::operator+(const shared_itype& rhs_ptr) const {
	return _general_operator(operator+, rhs_ptr);
}

Complex::shared_itype	Complex::operator-(const shared_itype& rhs_ptr) const {
	return _general_operator(operator-, rhs_ptr);
}

Complex::shared_itype	Complex::operator*(const shared_itype& rhs_ptr) const {
	return _general_operator(operator*, rhs_ptr);
}

Complex::shared_itype	Complex::operator/(const shared_itype& rhs_ptr) const {
	return _general_operator(operator/, rhs_ptr);
}

Complex::shared_itype	Complex::_general_operator(
	shared_itype (Complex::*f)(const shared_itype&) const,
	const shared_itype& rhs_ptr
	) const {
		std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
		if (r_ptr.get())
			return _rational_operator(f, r_ptr);
		std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
		if (c_ptr.get())
			return _complex_operator(f, c_ptr);
		std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
		if (m_ptr.get())
			return _matrix_operator(f, m_ptr);
	}

Complex::shared_itype	Complex::_rational_operator(
	shared_itype (Complex::*f)(const shared_itype&) const,
	const std::shared_ptr<Rational>& r_ptr
	) const {
		shared_itype	tmp = (this->*f)(r_ptr);
		Rational		r = *std::dynamic_pointer_cast<Rational>(tmp);
		tmp.reset(new Rational(r));
		return tmp;
	}

Complex::shared_itype	Complex::_complex_operator(
	shared_itype (Complex::*f)(const shared_itype&) const,
	const std::shared_ptr<Complex>& c_ptr
	) const {
		shared_itype	tmp = (this->*f)(c_ptr);
		Complex			c = *std::dynamic_pointer_cast<Complex>(tmp);
		tmp.reset(new Complex(c));
		return tmp;
	}

Complex::shared_itype	Complex::_matrix_operator(
	shared_itype (Complex::*f)(const shared_itype&) const,
	const std::shared_ptr<Matrix>& m_ptr
	) const {
		throw math::operation_undefined();
		return nullptr;
	}

/* Arith operators **********************************/

Complex Complex::conjugate() const {
	Complex tmp(*this);

	tmp._im.operator-();
	return tmp;
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
	return Complex(-getReal(), -getImaginary());
}

Complex& Complex::operator*=(const Complex& rhs) {
	const Rational	new_re((getReal() * rhs.getReal())
					- (getImaginary() * rhs.getImaginary()));
	const Rational	new_im((getReal() * rhs.getImaginary())
					+ (getImaginary() * rhs.getReal()));

	_re = new_re;
	_im = new_im;
	return *this;
}

Complex Complex::operator*(const Complex& rhs) const {
	Complex	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Complex& Complex::operator/=(const Complex& rhs) {
	const Complex	conj = rhs.conjugate();
	const Complex	den(rhs * conj);
	const Complex	num(*this * conj);

	_re = num.getReal() / den.getReal();
	_im = num.getImaginary() / den.getReal();
	return *this;
}

Complex Complex::operator/(const Complex& rhs) const {
	Complex	tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

Complex& Complex::operator^=(const Rational& rhs) {
	if (!rhs.isInteger() || rhs < Rational(0))
		throw math::operation_undefined();
	if (rhs == Rational(1) || !*this)
		return *this;
	else if (!rhs) {
		_re = 0;
		_im = 0;
	} else {
		Rational	rhs_copy(rhs);
		for (Rational i = 1; i < rhs_copy; ++i) {
			operator*=(*this);
		}
	}
	return *this;
}

Complex Complex::operator^(const Rational& rhs) const {
	Complex	tmp(*this);

	tmp.operator^=(rhs);
	return tmp;
}

Complex& Complex::operator%=(const Rational& rhs) {
	if (!isReal() || !getReal().isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_re.operator%=(rhs);
	return *this;
}

Complex Complex::operator%(const Rational& rhs) const {
	Complex	tmp(*this);

	tmp.operator%(rhs);
	return tmp;
}

/* Getters ******************************************/

Rational Complex::getReal() const {
	return Rational(_re);
}

Rational Complex::getImaginary() const {
	return Rational(_im);
}

/* Other ********************************************/

bool	Complex::operator!() const {
	return !getReal() && !getImaginary();
}

bool	Complex::isComplex() const {
	return getImaginary().getVal() && getReal().getVal();
}

bool	Complex::isReal() const {
	return !getImaginary().getVal();
}

bool	Complex::isImaginary() const {
	return !isReal();
}

/* Other ********************************************/

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
		if (math::abs(x.getImaginary()) != 1)
			o << math::abs(x.getImaginary());
		o << 'i';
	} else if (x.isReal()) {
		o << x.getReal();
	} else if (x.isImaginary()) {
		if (x.getImaginary() < 0)
			o << " - ";
		if (math::abs(x.getImaginary()) != 1)
			o << math::abs(x.getImaginary());
		o << 'i';
	}
	return o;
}
