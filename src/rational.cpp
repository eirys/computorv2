/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:56:26 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"

Rational::Rational():
	_val(0) {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const std::string&& s):
	_val(std::stold(s)) {}

Rational::~Rational() {}

Rational& Rational::operator=(long double rhs) {
	if (this->getVal() == rhs)
		return *this;
	_val = rhs;
	return *this;
}

/* Getters ******************************************/

long double Rational::getVal() const {
	return _val;
}

Rational::operator long double() const {
	return _val;
}

/* Relational operators *****************************/

bool operator==(const Rational& x, const long double& y) {
	return x.getVal() == y;
}

bool operator<(const Rational& x, const long double& y) {
	return x.getVal() < y;
}

bool operator!=(const Rational& x, const long double& y) {
	return !operator==(x, y);
}

bool operator>(const Rational& x, const long double& y) {
	return !operator<=(x, y);
}

bool operator<=(const Rational& x, const long double& y) {
	return operator==(x, y) || operator<(x, y);
}

bool operator>=(const Rational& x, const long double& y) {
	return !operator<(x, y);
}