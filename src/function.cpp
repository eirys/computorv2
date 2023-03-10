/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:14:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/10 23:38:26 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.hpp"
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

Function::Function():
	_body() {}

Function::~Function() {}

Function::Function(const Function& x):
	_body(x.getBody()) {}

Function::Function(const std::string& var_name, tree_head body):
	_var_name(var_name),
	_body(body) {}

/* -------------------------------------------------------------------------- */

Function&   Function::operator=(const Function& rhs) {
	if (*this == rhs)
		return *this;
	_var_name = rhs.getVarName();
	_body = rhs.getBody();
	return *this;
}

/* IType Operators ---------------------------------------------------------- */

//TODO

Function::shared_itype	Function::clone() const {
	return shared_itype(new Function(*this));
}

Function::shared_itype	Function::operator+(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

Function::shared_itype	Function::operator-(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

Function::shared_itype	Function::operator*(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

Function::shared_itype	Function::operator/(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

Function::shared_itype	Function::operator^(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

Function::shared_itype	Function::operator%(const shared_itype& rhs_ptr) const {
	(void)rhs_ptr;
	return nullptr;
}

/* Arith Operators ---------------------------------------------------------- */

Function	Function::operator-() const {
	Function	tmp(*this);

	Negate	neg(std::move(*tmp._body));
	*tmp._body = neg.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator+=(const Function& rhs) {
	Add	add(std::move(*_body), std::move(*rhs._body));

	*_body = add.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator+(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator+=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator-=(const Function& rhs) {
	Substract	sub(std::move(*_body), std::move(*rhs._body));

	*_body = sub.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator-(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator-=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator*=(const Function& rhs) {
	Multiply	mul(std::move(*_body), std::move(*rhs._body));

	*_body = mul.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator*(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator*=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator/=(const Function& rhs) {
	Divide	div(std::move(*_body), std::move(*rhs._body));

	*_body = div.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator/(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator/=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator^=(const Function& rhs) {
	Power	pow(std::move(*_body), std::move(*rhs._body));

	*_body = pow.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator^(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator^=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

Function&	Function::operator%=(const Function& rhs) {
	Modulo		mod(std::move(*_body), std::move(*rhs._body));

	*_body = mod.toNode();
	// return *this;
	return *(*_body)->eval();
}

Function	Function::operator%(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator%=(rhs);
	// return tmp;
	return *(*tmp._body)->eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Rational& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator-(const Rational& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator*(const Rational& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator/(const Rational& rhs) const {
	Function	tmp(*this);
	Divide	div(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = div.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator^(const Rational& rhs) const {
	Function	tmp(*this);
	Power		pow(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = pow.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator%(const Rational& rhs) const {
	Function	tmp(*this);
	Modulo		mod(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mod.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Complex& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator-(const Complex& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator*(const Complex& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator/(const Complex& rhs) const {
	Function	tmp(*this);
	Divide	div(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = div.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator^(const Complex& rhs) const {
	Function	tmp(*this);
	Power		pow(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = pow.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator%(const Complex& rhs) const {
	Function	tmp(*this);
	Modulo		mod(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mod.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Matrix& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator-(const Matrix& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator*(const Matrix& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	return *(*tmp._body)->eval();
}

Function	Function::operator/(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Function	Function::operator^(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Function	Function::operator%(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

/* Getter ------------------------------------------------------------------- */

const std::string&	Function::getName() const {
	return _name;
}

const std::string&  Function::getVarName() const {
	return _var_name;
}

Function::tree_head Function::getBody() const {
	return _body;
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

bool operator==(const Function& lhs, const Function& rhs) {
	return lhs.getVarName() == rhs.getVarName() && (*lhs.getBody())->eval() == (*rhs.getBody())->eval();
}

std::ostream&	operator<<(std::ostream& o, const Function& x) {
	o << '(' << x.getVarName() << ") = ";
	(*x.getBody())->print();
	return o;
}