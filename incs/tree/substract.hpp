/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:34:39 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 20:05:05 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTRACT_HPP
# define SUBSTRACT_HPP

# include "atree_node.hpp"

class Substract: virtual public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Initialized ------------------------------------------------------------ */
		Substract(const shared_node& left, const shared_node& right):
			base(left, right) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Substract() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval()  const {
			const shared_itype&			tmp = base::getLeft()->eval();

			std::shared_ptr<Rational>	arg1 = std::dynamic_pointer_cast<Rational>(tmp);
			if (arg1.get())
				return *arg1 - base::getRight()->eval();
			std::shared_ptr<Complex>	arg2 = std::dynamic_pointer_cast<Complex>(tmp);
			if (arg2.get())
				return *arg2 - base::getRight()->eval();
			std::shared_ptr<Matrix>		arg3 = std::dynamic_pointer_cast<Matrix>(tmp);
			if (arg3.get())
				return *arg3 - base::getRight()->eval();
			return nullptr;
		}

		void				print() const {
			std::cout << '(';
			base::getLeft()->print();
			std::cout << '-';
			base::getRight()->print();
			std::cout << ')';
		}

		shared_node			toNode() const {
			return shared_node(new Substract(base::getLeft(), base::getRight()))
		}
};

#endif