/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:58:10 by etran             #+#    #+#             */
/*   Updated: 2023/03/06 18:15:36 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

# include "itype.hpp"
# include "atree_node.hpp"

class Function: public IType {
	public:
		typedef typename	IType::unique_itype		unique_itype;
		typedef typename	IType::shared_itype 	shared_itype;
		typedef typename	IType::weak_itype		weak_itype;

		typedef typename	ATreeNode::unique_node	unique_node;

		Function();
		virtual ~Funtion();

		Function(const Function& x);
		Function(const std::string& name, const std::string& var_name, unique_node&& body);

		Function&				operator=(const Function& rhs);

		/* IType Operators -------------------------------------------------------- */
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

	private:
		std::string				_name;
		std::string				_var_name;
		unique_node				_body;
};

#endif