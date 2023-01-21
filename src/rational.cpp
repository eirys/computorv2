/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 12:50:54 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"

Rational::Rational():
	_val(0) {}

Rational::~Rational() {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const Rational& x):
	// TreeNode(_left, _right),
	_val(x.getVal()) {}

Rational::Rational(const std::string&& buf):
	_val(std::stold(buf)) {}

Rational& Rational::operator=(long double rhs) {
	if (this->getVal() == rhs)
		return *this;
	_val = rhs;
	return *this;
}

Rational& Rational::operator=(const Rational& rhs) {
	if (*this == rhs)
		return *this;
	_val = rhs.getVal();
	return *this;
}

/* Arith operators **********************************/

Rational& Rational::operator+=(const Rational& rhs) {
	_val += rhs.getVal();
	return *this;
}

Rational& Rational::operator++() {
	_val += 1;
	return *this;
}

Rational Rational::operator++(int) {
	Rational tmp(*this);

	operator++();
	return tmp;
}

Rational Rational::operator+(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Rational& Rational::operator-=(const Rational& rhs) {
	_val -= rhs.getVal();
	return *this;
}

Rational& Rational::operator--() {
	_val -= 1;
	return *this;
}

Rational Rational::operator--(int) {
	Rational tmp(*this);

	operator--();
	return tmp;
}

Rational Rational::operator-(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

Rational Rational::operator-() const {
	if (!getVal())
		return Rational(*this);
	return Rational(-getVal());
}

Rational& Rational::operator*=(const Rational& rhs) {
	if (getVal() != 0)
		_val *= rhs.getVal();
	return *this;
}

Rational Rational::operator*(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Rational& Rational::operator/=(const Rational& rhs) {
	if (rhs.getVal() == 0)
		throw math::operation_undefined();
	_val /= rhs.getVal();
	return *this;
}

Rational Rational::operator/(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

/* Relational operators *****************************/

Complex Rational::operator+(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Complex Rational::operator-(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

Complex Rational::operator*(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Complex Rational::operator/(const Complex& rhs) const {
	Complex tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

/* Relational operators *****************************/

Matrix Rational::operator+(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Rational::operator-(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Rational::operator*(const Matrix& rhs) const {
	return rhs.operator*(*this);
}

Matrix Rational::operator/(const Matrix& rhs) const {
	return rhs.operator/(*this);
}

Rational& Rational::operator^=(const Rational& rhs) {
	if (!rhs.isInteger())
		throw math::operation_undefined();
	_val = math::pow(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator^(const Rational& rhs) const {
	Rational	tmp(*this);

	tmp.operator^=(rhs);
	return tmp;
}

Rational& Rational::operator%=(const Rational& rhs) {
	if (!isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_val = math::remainder(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator%(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator%=(rhs);
	return tmp;
}

/* Getters ******************************************/

long double Rational::getVal() const {
	return _val;
}

/* Getters ******************************************/

bool Rational::operator!() const {
	return !getVal();
}

bool Rational::isInteger() const {
	const long long int	tmp = static_cast<long long int>(getVal());
	return tmp == getVal();
}

/* Relational operators *****************************/

bool operator==(const Rational& x, const Rational& y) {
	return x.getVal() == y.getVal();
}

bool operator<(const Rational& x, const Rational& y) {
	return x.getVal() < y.getVal();
}

bool operator!=(const Rational& x, const Rational& y) {
	return !operator==(x, y);
}

bool operator>(const Rational& x, const Rational& y) {
	return !operator<=(x, y);
}

bool operator<=(const Rational& x, const Rational& y) {
	return operator==(x, y) || operator<(x, y);
}

bool operator>=(const Rational& x, const Rational& y) {
	return !operator<(x, y);
}

/* I/O stream operator ******************************/

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}
