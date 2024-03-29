/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:07:29 by eli               #+#    #+#             */
/*   Updated: 2023/03/18 11:40:57 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.hpp"
#include "matrix.hpp"
#include "function.hpp"
#include "math.hpp"

#include "identifier.hpp"
#include "negate.hpp"
#include "add.hpp"
#include "substract.hpp"
#include "multiply.hpp"
#include "divide.hpp"
#include "power.hpp"
#include "modulo.hpp"
#include "variable.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Complex::Complex():
	_re(0),
	_im(0) {}

Complex::~Complex() {}

Complex::Complex(const Complex& x):
	_re(x.getReal()),
	_im(x.getImaginary()) {}

Complex::Complex(const Rational& x, const Rational& y):
	_re(x),
	_im(y) {}

/* -------------------------------------------------------------------------- */

Complex& Complex::operator=(const Complex& rhs) {
	if (this == &rhs)
		return *this;
	_re = rhs.getReal();
	_im = rhs.getImaginary();
	return *this;
}

/* IType operators ---------------------------------------------------------- */

Complex::shared_itype	Complex::clone() const {
	return shared_itype(new Complex(*this));
}

Complex::shared_itype	Complex::negate() const {
	Complex	copy(this->operator-());

	return shared_itype(new Complex(copy));
}

Complex::shared_itype	Complex::operator+(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator+, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator+, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator+, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator+, f_ptr);
	return nullptr;
}

Complex::shared_itype	Complex::operator-(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator-, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator-, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator-, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator-, f_ptr);
	return nullptr;
}

Complex::shared_itype	Complex::operator*(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator*, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator*, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator*, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator*, f_ptr);
	return nullptr;
}

Complex::shared_itype	Complex::operator/(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator/, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator/, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator/, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator/, f_ptr);
	return nullptr;
}

Complex::shared_itype	Complex::operator^(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator^, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator^, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator^, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator^, f_ptr);
	return nullptr;
}

Complex::shared_itype	Complex::operator%(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Complex::operator%, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Complex::operator%, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Complex::operator%, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Complex::operator%, f_ptr);
	return nullptr;
}

bool	Complex::operator==(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return operator==(*r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return operator==(*c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return operator==(*m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return operator==(*f_ptr);
	throw IType::ImpossibleComparison();
}

/* Arith operators ---------------------------------------------------------- */

Complex Complex::operator-() const {
	return Complex(-getReal(), -getImaginary());
}

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

Complex Complex::operator^(const Complex& rhs) const {
	if (!isReal())
		throw math::operation_undefined();
	Complex	tmp(*this);

	tmp.operator^=(rhs.getReal());
	return tmp;
}

Complex& Complex::operator%=(const Rational& rhs) {
	if (!isReal() || !getReal().isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_re.operator%=(rhs);
	return *this;
}

Complex Complex::operator%(const Complex& rhs) const {
	if (!isReal())
		throw math::operation_undefined();
	Complex	tmp(*this);

	tmp.operator%=(rhs.getReal());
	return tmp;
}

/* Rational ----------------------------------------------------------------- */

Complex			Complex::operator+(const Rational& rhs) const {
	Rational	new_re(getReal().operator+(rhs));

	return Complex(new_re, getImaginary());
}

Complex			Complex::operator-(const Rational& rhs) const {
	Rational	new_re(getReal().operator-(rhs));

	return Complex(new_re, getImaginary());
}

Complex			Complex::operator*(const Rational& rhs) const {
	Rational	new_re(getReal().operator*(rhs));
	Rational	new_im(getImaginary().operator*(rhs));

	return Complex(new_re, new_im);
}

Complex			Complex::operator/(const Rational& rhs) const {
	Rational	new_re(getReal().operator/(rhs));
	Rational	new_im(getImaginary().operator/(rhs));

	return Complex(new_re, new_im);
}

Complex Complex::operator^(const Rational& rhs) const {
	Complex	tmp(*this);

	tmp.operator^=(rhs);
	return tmp;
}

Complex Complex::operator%(const Rational& rhs) const {
	Complex	tmp(*this);

	tmp.operator%=(rhs);
	return tmp;
}

bool	Complex::operator==(const Rational& rhs) const {
	return rhs.operator==(*this);
}

/* Matrix ------------------------------------------------------------------- */

Matrix			Complex::operator+(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix			Complex::operator-(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix			Complex::operator*(const Matrix& rhs) const {
	if (isReal()) {
		Rational	tmp(getReal());

		return rhs.operator*(tmp);
	}
	throw math::operation_undefined();
}

Matrix			Complex::operator/(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Complex::operator^(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Complex::operator%(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

bool	Complex::operator==(const Matrix& rhs) const {
	(void)rhs;
	throw IType::ImpossibleComparison();
}

/* Function ----------------------------------------------------------------- */

Function	Complex::operator+(const Function& rhs) const {
	Add			add(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(add.toNode()));
	return tmp;
}

Function	Complex::operator-(const Function& rhs) const {
	Substract	sub(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(sub.toNode()));
	return tmp;
}

Function	Complex::operator*(const Function& rhs) const {
	Multiply	mul(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(mul.toNode()));
	return tmp;
}

Function	Complex::operator/(const Function& rhs) const {
	Divide	div(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(div.toNode()));
	return tmp;
}

Function	Complex::operator^(const Function& rhs) const {
	Power	pow(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(pow.toNode()));
	return tmp;
}

Function	Complex::operator%(const Function& rhs) const {
	Modulo	mod(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(mod.toNode()));
	return tmp;
}

bool	Complex::operator==(const Function& rhs) const {
	(void)rhs;
	throw IType::ImpossibleComparison();
}

/* Getters ------------------------------------------------------------------ */

const Rational& Complex::getReal() const {
	return _re;
}

const Rational& Complex::getImaginary() const {
	return _im;
}

/* Tools -------------------------------------------------------------------- */

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

/* Relational operators ----------------------------------------------------- */

bool	Complex::operator==(const Complex& y) const {
	return getReal() == y.getReal() && getImaginary() == y.getImaginary();
}

bool	Complex::operator!=(const Complex& y) const {
	return !operator==(y);
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

Complex::shared_itype	Complex::_rational_operator(
	Complex (Complex::*f)(const Rational&) const,
	const std::shared_ptr<Rational>& r_ptr
	) const {
		return shared_itype(new Complex((this->*f)(*r_ptr)));
	}

Complex::shared_itype	Complex::_complex_operator(
	Complex (Complex::*f)(const Complex&) const,
	const std::shared_ptr<Complex>& c_ptr
	) const {
		return shared_itype(new Complex((this->*f)(*c_ptr)));
	}

Complex::shared_itype	Complex::_matrix_operator(
	Matrix (Complex::*f)(const Matrix&) const,
	const std::shared_ptr<Matrix>& m_ptr
	) const {
		return shared_itype(new Matrix((this->*f)(*m_ptr)));
	}

Complex::shared_itype	Complex::_function_operator(
	Function (Complex::*f)(const Function&) const,
	const std::shared_ptr<Function>& f_ptr
	) const {
		return shared_itype(new Function((this->*f)(*f_ptr)));
	}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

/* I/O stream operator ------------------------------------------------------ */

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
