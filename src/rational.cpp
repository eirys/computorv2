/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 23:45:57 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"

Rational::Rational():
	_val(0) {}

Rational::~Rational() {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const Rational& x):
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

/* Getters ******************************************/

long double Rational::getVal() const {
	return _val;
}

/* Relational operators *****************************/

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
		throw Rational::divide_by_zero();
	_val /= rhs.getVal();
	return *this;
}

Rational Rational::operator/(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
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

/* Relational operators *****************************/

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}