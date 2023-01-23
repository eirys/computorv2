/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:13:54 by eli               #+#    #+#             */
/*   Updated: 2023/01/23 23:54:35 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_HPP
# define ADD_HPP

# include <memory>

# include "atree_node.hpp"

class Add: virtual public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		typedef typename	base::unique_itype		unique_itype;
		typedef typename	base::shared_itype		shared_itype;
		typedef typename	base::weak_itype		weak_itype;

		// Initialized constructor
		Add(const shared_node& left, const shared_node& right):
			base(left, right) {}

		// Destructor
		virtual ~Add() {}

		const shared_itype	eval() const {
			const shared_itype&			tmp = base::getLeft()->eval();

			std::shared_ptr<Rational>	arg1 = std::dynamic_pointer_cast<Rational>(tmp);
			if (arg1.get())
				return *arg1 + base::getRight()->eval();
			std::shared_ptr<Complex>	arg2 = std::dynamic_pointer_cast<Complex>(tmp);
			if (arg2.get())
				return *arg2 + base::getRight()->eval();
			std::shared_ptr<Matrix>		arg3 = std::dynamic_pointer_cast<Matrix>(tmp);
			if (arg3.get())
				return *arg3 + base::getRight()->eval();
			return nullptr;
			// return base::getLeft()->eval() + base::getRight()->eval();
		}

		void				print() const {
			std::cout << '(';
			base::getLeft()->print();
			std::cout << '+';
			base::getRight()->print();
			std::cout << ')';
		}
};

#endif