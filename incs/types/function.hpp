/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:58:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/09 14:55:14 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

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
		Function(const std::string& name, const std::string& var_name, tree_head body);

		Function&			operator=(const Function& rhs);

		/* IType Operators -------------------------------------------------------- */
		shared_itype		clone() const;
		shared_itype		operator+(const shared_itype& rhs_ptr) const;
		shared_itype		operator-(const shared_itype& rhs_ptr) const;
		shared_itype		operator*(const shared_itype& rhs_ptr) const;
		shared_itype		operator/(const shared_itype& rhs_ptr) const;
		shared_itype		operator^(const shared_itype& rhs_ptr) const;
		shared_itype		operator%(const shared_itype& rhs_ptr) const;

		/* Arith Operators -------------------------------------------------------- */
		Function			operator-() const;

		Function&			operator+=(const Function& rhs);
		Function			operator+(const Function& rhs) const;

		Function&			operator-=(const Function& rhs);
		Function			operator-(const Function& rhs) const;

		Function&			operator*=(const Function& rhs);
		Function			operator*(const Function& rhs) const;
		
		Function&			operator/=(const Function& rhs);
		Function			operator/(const Function& rhs) const;

		Function&			operator^=(const Function& rhs);
		Function			operator^(const Function& rhs) const;

		Function&			operator%=(const Function& rhs);		// undefined
		Function			operator%(const Function& rhs) const;	// undefined

		/* Rational Operators ----------------------------------------------------- */
		Function			operator+(const Rational& rhs) const;
		Function			operator-(const Rational& rhs) const;
		Function			operator*(const Rational& rhs) const;
		Function			operator/(const Rational& rhs) const;
		Function			operator^(const Rational& rhs) const;
		Function			operator%(const Rational& rhs) const;

		/* Complex Operators ------------------------------------------------------ */
		Function			operator+(const Complex& rhs) const;
		Function			operator-(const Complex& rhs) const;
		Function			operator*(const Complex& rhs) const;
		Function			operator/(const Complex& rhs) const;
		Function			operator^(const Complex& rhs) const;
		Function			operator%(const Complex& rhs) const;

		/* Matrix Operators ------------------------------------------------------- */
		Function			operator+(const Matrix& rhs) const;
		Function			operator-(const Matrix& rhs) const;
		Function			operator*(const Matrix& rhs) const;
		Function			operator/(const Matrix& rhs) const;		// undefined
		Function			operator^(const Matrix& rhs) const;		// undefined
		Function			operator%(const Matrix& rhs) const;		// undefined

		/* Getter ----------------------------------------------------------------- */
		const std::string&	getName() const;
		const std::string&	getVarName() const;
		tree_head			getBody() const;

	private:
		std::string			_name;
		std::string			_var_name;
		tree_head			_body;

};

bool			operator==(const Function& lhs, const Function& rhs);
std::ostream&	operator<<(std::ostream& o, const Function& x);

#endif