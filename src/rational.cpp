/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/22 18:30:10 by eli              ###   ########.fr       */
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
	_val(x.getVal()) {}

// Rational::Rational(const std::string&& buf):
// 	_val(std::stold(buf)) {}

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

Rational::shared_itype	Rational::operator+(const shared_itype& p_rhs) const {
	return _general_operator(Rational::operator+, p_rhs);
}

Rational::shared_itype	Rational::operator-(const shared_itype& p_rhs) const {
	return _general_operator(Rational::operator-, p_rhs);
}

Rational::shared_itype	Rational::operator*(const shared_itype& p_rhs) const {
	return _general_operator(Rational::operator*, p_rhs);
}

Rational::shared_itype	Rational::operator/(const shared_itype& p_rhs) const {
	return _general_operator(Rational::operator/, p_rhs);
}

Rational::shared_itype	Rational::_general_operator(
		shared_itype (Rational::*f)() const,
		const shared_itype& rhs_ptr
	) const {
		std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
		if (r_ptr.get())
			return _rational_operator(f, r_ptr);
			// tmp = std::make_shared<IType>((this->*f)(rhs_ptr));
			// Rational	r = *std::dynamic_pointer_cast<Rational>(tmp);
			// tmp.reset(new Rational(r));
		std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
		if (c_ptr.get())
			return _complex_operator(f, c_ptr);
			// tmp = std::make_shared<IType>((this->*f)(rhs_ptr));
			// Complex		c = *std::dynamic_pointer_cast<Complex>(tmp);
			// tmp.reset(new Complex(c));
			// return Rational::shared_itype(new Complex(c));
		std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
		if (m_ptr.get())
			return _matrix_operator(f, m_ptr);
			// tmp = std::make_shared<IType>((this->*f)(m_ptr));
			// Matrix		m = *std::dynamic_pointer_cast<Matrix>(tmp);
			// tmp.reset(new Matrix(m));
			// return Rational::shared_itype(new Matrix(m));
		return nullptr;
	}


Rational::shared_itype	Rational::_rational_operator(
		shared_itype (Rational::*f)(const Rational&) const,
		const std::shared_ptr<Rational>& r_ptr
	) const {
		shared_itype	tmp = /* std::make_shared<IType>( */(this->*f)(*r_ptr)/* ) */;
		Rational		r = *std::dynamic_pointer_cast<Rational>(tmp);
		tmp.reset(new Rational(r));
		return tmp;
	}


Rational::shared_itype	Rational::_complex_operator(
		shared_itype (Rational::*f)(const Complex& rhs) const,
		const std::shared_ptr<Complex>& c_ptr
	) const {
		shared_itype	tmp = (this->*f)(*c_ptr);
		Complex			c = *std::dynamic_pointer_cast<Complex>(tmp);
		tmp.reset(new Complex(c));
		return tmp;
	}


Rational::shared_itype	Rational::_matrix_operator(
		shared_itype (Rational::*f)(const Matrix&) const,
		const std::shared_ptr<Matrix>& m_ptr
	) const {
		shared_itype	tmp = (this->*f)(m_ptr);
		Matrix			m = *std::dynamic_pointer_cast<Matrix>(tmp);
		tmp.reset(new Matrix(m));
		return tmp;
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
