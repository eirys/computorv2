/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/03/17 22:01:10 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include "function.hpp"

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

Rational::Rational():
	_val(0) {}

Rational::~Rational() {}

Rational::Rational(long double x):
	_val(x) {}

Rational::Rational(const Rational& x):
	_val(x.getVal()) {}

/* -------------------------------------------------------------------------- */

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

/* IType operators ---------------------------------------------------------- */

Rational::shared_itype	Rational::clone() const {
	return shared_itype(new Rational(*this));
}

Rational::shared_itype	Rational::negate() const {
	Rational	copy(this->operator-());

	return shared_itype(new Rational(copy));
}

Rational::shared_itype	Rational::operator+(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator+, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator+, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator+, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator+, f_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator-(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator-, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator-, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator-, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator-, f_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator*(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator*, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator*, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator*, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator*, f_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator/(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator/, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator/, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator/, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator/, f_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator%(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator%, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator%, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator%, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator%, f_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator^(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr != nullptr)
		return _rational_operator(&Rational::operator^, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr != nullptr)
		return _complex_operator(&Rational::operator^, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr != nullptr)
		return _matrix_operator(&Rational::operator^, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr != nullptr)
		return _function_operator(&Rational::operator^, f_ptr);
	return nullptr;
}

bool	Rational::operator==(const shared_itype& rhs_ptr) const {
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

Rational::operator bool() const {
	return getVal();
}

/* Arith operators ---------------------------------------------------------- */

Rational Rational::operator-() const {
	if (!getVal())
		return Rational(*this);
	return Rational(-getVal());
}

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
	if (!rhs || !isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_val = math::modulo(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator%(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator%=(rhs);
	return tmp;
}

/* Complex ------------------------------------------------------------------ */

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

Complex Rational::operator^(const Complex& rhs) const {
	if (!rhs.isReal())
		throw math::operation_undefined();
	Complex tmp(*this);

	tmp.operator^=(rhs.getReal());
	return tmp;
}

Complex Rational::operator%(const Complex& rhs) const {
	if (!rhs.isReal())
		throw math::operation_undefined();
	Complex tmp(*this);

	tmp.operator%=(rhs.getReal());
	return tmp;
}

bool	Rational::operator==(const Complex& rhs) const {
	if (rhs.isReal())
		return operator==(rhs.getReal());
	return false;
}

/* Matrix ------------------------------------------------------------------- */

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
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Rational::operator^(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Rational::operator%(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

bool	Rational::operator==(const Matrix& rhs) const {
	(void)rhs;
	throw IType::ImpossibleComparison();
}

/* Function ----------------------------------------------------------------- */

Function Rational::operator+(const Function& rhs) const {
	Add			add(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(add.toNode()));
	return tmp;
}

Function Rational::operator-(const Function& rhs) const {
	Substract	sub(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(sub.toNode()));
	return tmp;
}

Function Rational::operator*(const Function& rhs) const {
	Multiply	mul(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(mul.toNode()));
	return tmp;
}

Function Rational::operator/(const Function& rhs) const {
	Divide		div(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(div.toNode()));
	return tmp;
}

Function Rational::operator^(const Function& rhs) const {
	Power		pow(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(pow.toNode()));
	return tmp;
}

Function Rational::operator%(const Function& rhs) const {
	Modulo		mod(createVariable(*this), (*rhs.getBody())->clone());

	Function	tmp(rhs.getVarName(), std::make_shared<unique_node>(mod.toNode()));
	return tmp;
}

bool	Rational::operator==(const Function& rhs) const {
	(void)rhs;
	throw IType::ImpossibleComparison();
}

/* Getters ------------------------------------------------------------------ */

long double Rational::getVal() const {
	return _val;
}

/* Tools -------------------------------------------------------------------- */

bool Rational::operator!() const {
	return !getVal();
}

bool Rational::isInteger() const {
	const long long int	tmp = static_cast<long long int>(getVal());
	return tmp == getVal();
}

/* Relational operators ----------------------------------------------------- */

bool	Rational::operator==(const Rational& y) const {
	return getVal() == y.getVal();
}

bool	Rational::operator<(const Rational& y) const {
	return getVal() < y.getVal();
}

bool	Rational::operator!=(const Rational& y) const {
	return !operator==(y);
}

bool	Rational::operator>(const Rational& y) const {
	return !operator<=(y);
}

bool	Rational::operator<=(const Rational& y) const {
	return operator==(y) || operator<(y);
}

bool	Rational::operator>=(const Rational& y) const {
	return !operator<(y);
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

Rational::shared_itype	Rational::_rational_operator(
	Rational (Rational::*f)(const Rational&) const,
	const std::shared_ptr<Rational>& r_ptr
) const {
	return shared_itype(new Rational((this->*f)(*r_ptr)));
}

Rational::shared_itype	Rational::_complex_operator(
	Complex (Rational::*f)(const Complex&) const,
	const std::shared_ptr<Complex>& c_ptr
) const {
	return shared_itype(new Complex((this->*f)(*c_ptr)));
}

Rational::shared_itype	Rational::_matrix_operator(
	Matrix (Rational::*f)(const Matrix&) const,
	const std::shared_ptr<Matrix>& m_ptr
) const {
	return shared_itype(new Matrix((this->*f)(*m_ptr)));
}

Rational::shared_itype	Rational::_function_operator(
	Function (Rational::*f)(const Function&) const,
	const std::shared_ptr<Function>& f_ptr
) const {
		return shared_itype(new Function((this->*f)(*f_ptr)));
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

/* I/O stream operator ------------------------------------------------------ */

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}
