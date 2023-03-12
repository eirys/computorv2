/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:14:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/12 14:17:21 by eli              ###   ########.fr       */
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
	_name(x.getName()),
	_var_name(x.getVarName()),
	_body(x.getBody()) {}

Function::Function(const std::string& name, const std::string& var_name, tree_head body):
	_name(name),
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
	Function	tmp(*this);

	unique_node	new_var = createVariable(*this);
	Negate	neg(std::move(new_var));

	*tmp._body = neg.toNode();

	// return tmp;
	// return *(*tmp._body)->eval();
	// return _eval((*tmp._body)->eval());
	return tmp._eval();
}

Function&	Function::operator+=(const Function& rhs) {
	Add	add(std::move(*_body), std::move(*rhs._body));

	*_body = add.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator+(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator+=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function&	Function::operator-=(const Function& rhs) {
	Substract	sub(std::move(*_body), std::move(*rhs._body));

	*_body = sub.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator-(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator-=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function&	Function::operator*=(const Function& rhs) {
	Multiply	mul(std::move(*_body), std::move(*rhs._body));

	*_body = mul.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator*(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator*=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function&	Function::operator/=(const Function& rhs) {
	Divide	div(std::move(*_body), std::move(*rhs._body));

	*_body = div.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator/(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator/=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function&	Function::operator^=(const Function& rhs) {
	Power	pow(std::move(*_body), std::move(*rhs._body));

	*_body = pow.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator^(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator^=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function&	Function::operator%=(const Function& rhs) {
	Modulo		mod(std::move(*_body), std::move(*rhs._body));

	*_body = mod.toNode();
	// return *this;
	// return *(*_body)->eval();
	return _eval();
}

Function	Function::operator%(const Function& rhs) const {
	Function	tmp(*this);
	tmp.operator%=(rhs);
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Rational& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator-(const Rational& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator*(const Rational& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator/(const Rational& rhs) const {
	Function	tmp(*this);
	Divide	div(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = div.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator^(const Rational& rhs) const {
	Function	tmp(*this);
	Power		pow(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = pow.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator%(const Rational& rhs) const {
	Function	tmp(*this);
	Modulo		mod(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mod.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Complex& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator-(const Complex& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator*(const Complex& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator/(const Complex& rhs) const {
	Function	tmp(*this);
	Divide	div(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = div.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator^(const Complex& rhs) const {
	Function	tmp(*this);
	Power		pow(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = pow.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator%(const Complex& rhs) const {
	Function	tmp(*this);
	Modulo		mod(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mod.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

/* -------------------------------------------------------------------------- */

Function	Function::operator+(const Matrix& rhs) const {
	Function	tmp(*this);
	Add			add(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = add.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator-(const Matrix& rhs) const {
	Function	tmp(*this);
	Substract	sub(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = sub.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
}

Function	Function::operator*(const Matrix& rhs) const {
	Function	tmp(*this);
	Multiply	mul(std::move(*tmp._body), createVariable(rhs));
	*tmp._body = mul.toNode();
	// return tmp;
	// return *(*tmp._body)->eval();
	return tmp._eval();
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

const std::string	Function::getName() const {
	return _name;
}

const std::string  Function::getVarName() const {
	return _var_name;
}

Function::tree_head Function::getBody() const {
	return _body;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

Function&	Function::_eval() const {
	Function&		cast_result = dynamic_cast<Function&>(*(*_body)->eval());

	return cast_result;
}

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
	return lhs.getVarName() == rhs.getVarName() && (*lhs.getBody())->eval() == (*rhs.getBody())->eval();
}

std::ostream&	operator<<(std::ostream& o, const Function& x) {
	// LOG("fun <<");
	(*x.getBody())->print();
	return o;
}