/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/03/08 21:42:48 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"

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

Rational::shared_itype	Rational::operator+(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator+, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator+, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator+, m_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator-(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator-, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator-, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator-, m_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator*(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator*, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator*, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator*, m_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator/(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator/, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator/, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator/, m_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator%(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator%, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator%, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator%, m_ptr);
	return nullptr;
}

Rational::shared_itype	Rational::operator^(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Rational::operator^, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Rational::operator^, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Rational::operator^, m_ptr);
	return nullptr;
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
	if (!isInteger() || !rhs.isInteger())
		throw math::operation_undefined();
	_val = math::modulo(getVal(), rhs.getVal());
	return *this;
}

Rational Rational::operator%(const Rational& rhs) const {
	Rational tmp(*this);

	tmp.operator%=(rhs);
	return tmp;
}

/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */

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

Matrix Rational::operator^(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Rational::operator%(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
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

/* Relational operators ----------------------------------------------------- */

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

/* I/O stream operator ------------------------------------------------------ */

std::ostream&	operator<<(std::ostream& o, const Rational& x) {
	o << x.getVal();
	return o;
}
