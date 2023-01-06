/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:46:41 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"

Rational::Rational():
	_val(0) {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const std::string&& s):
	_val(std::stold(s)) {}

Rational::Rational(const Rational& x):
	_val(x.getVal()) {}

Rational::~Rational() {}

Rational& Rational::operator=(const Rational& rhs) {
	if (this == &rhs)
		return *this;
	_val = rhs._val;
	return *this;
}

Rational& Rational::operator=(long double rhs) {
	if (this->getVal() == rhs)
		return *this;
	_val = rhs;
	return *this;
}

Rational::operator long double() const {
	return _val;
}

/* Getters ******************************************/

long double Rational::getVal() const {
	return _val;
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

/* I/O stream operator *****************************/

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}