/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:07:32 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"

Complex::Complex():
	_re(0),
	_im(0) {}


// TODO: useless?
Complex::Complex(const std::string&& buf):
	_re(0),
	_im(0) { (void)buf; }

Complex::~Complex() {}

Complex::Complex(const Complex& x):
	_re(x.getReal()),
	_im(x.getImaginary()) {}

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

	(void)o; (void)x;
	return o;
}
