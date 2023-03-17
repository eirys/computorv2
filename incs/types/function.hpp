/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:58:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/17 22:01:26 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

# include <memory>
# include <iostream>

# include "itype.hpp"
# include "atree_node.hpp"
# include "computor.hpp"

class Function: public IType {
	public:
		typedef typename	IType::unique_itype				unique_itype;
		typedef typename	IType::shared_itype 			shared_itype;
		typedef typename	IType::weak_itype				weak_itype;

		typedef typename	ATreeNode::unique_node			unique_node;
		typedef typename	ATreeNode::tree_head			tree_head;
		typedef typename	Computor::context				context;

		Function();
		virtual ~Function();

		Function(const Function& x);
		Function(const std::string& var_name, tree_head body);

		Function&			operator=(const Function& rhs);

		/* IType Operators -------------------------------------------------------- */
		shared_itype		clone() const;
		shared_itype		negate() const;
		shared_itype		operator+(const shared_itype& rhs_ptr) const;
		shared_itype		operator-(const shared_itype& rhs_ptr) const;
		shared_itype		operator*(const shared_itype& rhs_ptr) const;
		shared_itype		operator/(const shared_itype& rhs_ptr) const;
		shared_itype		operator^(const shared_itype& rhs_ptr) const;
		shared_itype		operator%(const shared_itype& rhs_ptr) const;
		bool				operator==(const shared_itype& rhs_ptr) const;
		operator bool() const;

		/* Arith Operators -------------------------------------------------------- */
		Function			operator-() const;

		Function			operator+(const Function& rhs) const;
		Function			operator-(const Function& rhs) const;
		Function			operator*(const Function& rhs) const;
		Function			operator/(const Function& rhs) const;
		Function			operator^(const Function& rhs) const;
		Function			operator%(const Function& rhs) const;

		/* Rational Operators ----------------------------------------------------- */
		Function			operator+(const Rational& rhs) const;
		Function			operator-(const Rational& rhs) const;
		Function			operator*(const Rational& rhs) const;
		Function			operator/(const Rational& rhs) const;
		Function			operator^(const Rational& rhs) const;
		Function			operator%(const Rational& rhs) const;
		bool				operator==(const Rational& rhs) const;

		/* Complex Operators ------------------------------------------------------ */
		Function			operator+(const Complex& rhs) const;
		Function			operator-(const Complex& rhs) const;
		Function			operator*(const Complex& rhs) const;
		Function			operator/(const Complex& rhs) const;
		Function			operator^(const Complex& rhs) const;
		Function			operator%(const Complex& rhs) const;
		bool				operator==(const Complex& rhs) const;

		/* Matrix Operators ------------------------------------------------------- */
		Function			operator+(const Matrix& rhs) const;
		Function			operator-(const Matrix& rhs) const;
		Function			operator*(const Matrix& rhs) const;
		Function			operator/(const Matrix& rhs) const;		// undefined
		Function			operator^(const Matrix& rhs) const;		// undefined
		Function			operator%(const Matrix& rhs) const;		// undefined
		bool				operator==(const Matrix& rhs) const;

		/* Getter ----------------------------------------------------------------- */
		const std::string	getVarName() const;
		tree_head			getBody() const;

		/* Relational Operators --------------------------------------------------- */
		bool				operator==(const Function& rhs) const;
		bool				operator!=(const Function& rhs) const;

	private:
		std::string			_var_name;
		tree_head			_body;

		shared_itype		_rational_operator(
								Function (Function::*f)(const Rational&) const,
								const std::shared_ptr<Rational>& r_ptr
							) const;
		shared_itype		_complex_operator(
								Function (Function::*f)(const Complex&) const,
								const std::shared_ptr<Complex>& c_ptr
							) const;
		shared_itype		_matrix_operator(
								Function (Function::*f)(const Matrix&) const,
								const std::shared_ptr<Matrix>& m_ptr
							) const;
		shared_itype		_function_operator(
								Function (Function::*f)(const Function&) const,
								const std::shared_ptr<Function>& f_ptr
							) const;
};

std::ostream&	operator<<(std::ostream& o, const Function& x);

#endif