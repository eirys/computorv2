/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:58:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/08 22:06:13 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

# include "itype.hpp"
# include "atree_node.hpp"
# include "tree.hpp"

class Function: public IType {
	public:
		typedef typename	IType::unique_itype		unique_itype;
		typedef typename	IType::shared_itype 	shared_itype;
		typedef typename	IType::weak_itype		weak_itype;

		// typedef typename	ATreeNode::unique_node	unique_node;

		Function();
		virtual ~Function();

		Function(const Function& x);
		Function(const std::string& name, const std::string& var_name, const Tree& body);

		Function&				operator=(const Function& rhs);

		/* IType Operators -------------------------------------------------------- */
		shared_itype			clone() const;
		shared_itype			operator+(const shared_itype& rhs_ptr) const;
		shared_itype			operator-(const shared_itype& rhs_ptr) const;
		shared_itype			operator*(const shared_itype& rhs_ptr) const;
		shared_itype			operator/(const shared_itype& rhs_ptr) const;
		shared_itype			operator^(const shared_itype& rhs_ptr) const;
		shared_itype			operator%(const shared_itype& rhs_ptr) const;

		Function				operator-() const;

		Function&				operator+=(const Function& rhs);
		Function				operator+(const Function& rhs) const;

		Function&				operator-=(const Function& rhs);
		Function				operator-(const Function& rhs) const;

		Function&				operator*=(const Function& rhs);
		Function				operator*(const Function& rhs) const;
		
		Function&				operator/=(const Function& rhs);
		Function				operator/(const Function& rhs) const;

		Function&				operator^=(const Rational& rhs);
		Function				operator^(const Function& rhs) const;

		Function&				operator%=(const Rational& rhs);		// undefined
		Function				operator%(const Function& rhs) const;	// undefined

		/* Rational Operators ----------------------------------------------------- */
		/* Complex Operators ------------------------------------------------------ */
		/* Matrix Operators ------------------------------------------------------- */

		/* Getter ----------------------------------------------------------------- */
		const Tree&				getBody() const;

	private:
		std::string				_name;
		std::string				_var_name;
		Tree					_body;
};

#endif