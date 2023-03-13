/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:14:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/13 19:15:32 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

Function::Function():
	_body() {}

Function::~Function() {}

Function::Function(const Function& x):
	_var_name(x.getVarName()),
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
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator+, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator+, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator+, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator+, f_ptr);
	return nullptr;
}

Function::shared_itype	Function::operator-(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator-, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator-, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator-, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator-, f_ptr);
	return nullptr;
}

Function::shared_itype	Function::operator*(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator*, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator*, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator*, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator*, f_ptr);
	return nullptr;
}

Function::shared_itype	Function::operator/(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator/, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator/, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator/, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator/, f_ptr);
	return nullptr;
}

Function::shared_itype	Function::operator^(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator^, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator^, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator^, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator^, f_ptr);
	return nullptr;
}

Function::shared_itype	Function::operator%(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational> r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Function::operator%, r_ptr);
	std::shared_ptr<Complex> c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Function::operator%, c_ptr);
	std::shared_ptr<Matrix>	m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Function::operator%, m_ptr);
	std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(rhs_ptr);
	if (f_ptr.get())
		return _function_operator(&Function::operator%, f_ptr);
	return nullptr;
}

/* Arith Operators ---------------------------------------------------------- */

Function	Function::operator-() const {
	Negate	negate((*_body)->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(negate.toNode());

	return tmp;
}

Function	Function::operator+(const Function& rhs) const {
	Add			add((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(add.toNode());

	return tmp;
}

Function	Function::operator-(const Function& rhs) const {
	Substract	sub((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(sub.toNode());

	return tmp;
}

Function	Function::operator*(const Function& rhs) const {
	Multiply	mul((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mul.toNode());

	return tmp;
}

Function	Function::operator/(const Function& rhs) const {
	Divide		div((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(div.toNode());

	return tmp;
}

Function	Function::operator^(const Function& rhs) const {
	Power		pow((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(pow.toNode());

	return tmp;
}

Function	Function::operator%(const Function& rhs) const {
	Modulo		mod((*_body)->clone(), (*rhs.getBody())->clone());

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mod.toNode());

	return tmp;
}

/* Rational ----------------------------------------------------------------- */

Function	Function::operator+(const Rational& rhs) const {
	Add			add((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(add.toNode());

	return tmp;
}

Function	Function::operator-(const Rational& rhs) const {
	Substract	sub((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(sub.toNode());

	return tmp;
}

Function	Function::operator*(const Rational& rhs) const {
	Multiply	mul((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mul.toNode());

	return tmp;
}

Function	Function::operator/(const Rational& rhs) const {
	Divide		div((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(	div.toNode());

	return tmp;
}

Function	Function::operator^(const Rational& rhs) const {
	Power		pow((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(pow.toNode());

	return tmp;
}

Function	Function::operator%(const Rational& rhs) const {
	Modulo		mod((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mod.toNode());

	return tmp;
}

/* Complex ------------------------------------------------------------------ */

Function	Function::operator+(const Complex& rhs) const {
	Add			add((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(add.toNode());

	return tmp;
}

Function	Function::operator-(const Complex& rhs) const {
	Substract	sub((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(sub.toNode());

	return tmp;
}

Function	Function::operator*(const Complex& rhs) const {
	Multiply	mul((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mul.toNode());

	return tmp;
}

Function	Function::operator/(const Complex& rhs) const {
	Divide		div((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(	div.toNode());

	return tmp;
}

Function	Function::operator^(const Complex& rhs) const {
	Power		pow((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(pow.toNode());

	return tmp;
}

Function	Function::operator%(const Complex& rhs) const {
	Modulo		mod((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mod.toNode());

	return tmp;
}

/* Matrix ------------------------------------------------------------------- */

Function	Function::operator+(const Matrix& rhs) const {
	Add			add((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(add.toNode());

	return tmp;
}

Function	Function::operator-(const Matrix& rhs) const {
	Substract	sub((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(sub.toNode());

	return tmp;
}

Function	Function::operator*(const Matrix& rhs) const {
	Multiply	mul((*_body)->clone(), createVariable(rhs));

	Function	tmp(*this);
	tmp._body = std::make_shared<unique_node>(mul.toNode());

	return tmp;
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

const std::string  Function::getVarName() const {
	return _var_name;
}

Function::tree_head Function::getBody() const {
	return _body;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

Function::shared_itype	Function::_rational_operator(
	Function (Function::*f)(const Rational&) const,
	const std::shared_ptr<Rational>& r_ptr
) const {
	return shared_itype(new Function((this->*f)(*r_ptr)));
}

Function::shared_itype	Function::_complex_operator(
	Function (Function::*f)(const Complex&) const,
	const std::shared_ptr<Complex>& c_ptr
) const {
	return shared_itype(new Function((this->*f)(*c_ptr)));
}

Function::shared_itype	Function::_matrix_operator(
	Function (Function::*f)(const Matrix&) const,
	const std::shared_ptr<Matrix>& m_ptr
) const {
	return shared_itype(new Function((this->*f)(*m_ptr)));
}

Function::shared_itype	Function::_function_operator(
	Function (Function::*f)(const Function&) const,
	const std::shared_ptr<Function>& f_ptr
) const {
	return shared_itype(new Function((this->*f)(*f_ptr)));
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

bool operator==(const Function& lhs, const Function& rhs) {
	return lhs.getVarName() == rhs.getVarName() && lhs.getBody() == rhs.getBody();
}

std::ostream&	operator<<(std::ostream& o, const Function& x) {
	(*x.getBody())->print();
	return o;
}