/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:24:40 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 00:09:52 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include "atree_node.hpp"

class Variable: virtual public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		// Initialized constructor

		Variable(const shared_itype& val_ptr):
			base(),
			_val_ptr(val_ptr) {}

		// Destructor
		virtual ~Variable() {}

		const shared_itype	eval() const {
			return _val_ptr;
		}

		void				print() const {
			std::cout << *_val_ptr;
		}

	private:
		shared_itype	_val_ptr;
};

Variable	createVariable(const Rational& x) {
	Variable::shared_itype	tmp(new Rational(x));

	return Variable(tmp);
}

Variable	createVariable(const Complex& x) {
	Variable::shared_itype	tmp(new Complex(x));

	return Variable(tmp);
}

Variable	createVariable(const Matrix& x) {
	Variable::shared_itype	tmp(new Matrix(x));

	return Variable(tmp);
}

#endif