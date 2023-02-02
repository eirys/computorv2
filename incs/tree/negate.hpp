/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:10:38 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 11:25:19 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEGATE_HPP
# define NEGATE_HPP

# include "atree_node.hpp"

class Negate: public virtual ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		// Initialized constructor
		Negate(const shared_node& right):
			base(nullptr, right) {}

		// Destructor
		virtual ~Negate() {}

		const shared_itype	eval() const {
			const shared_itype&			tmp = base::getRight()->eval();

			std::shared_ptr<Rational>	arg1 = std::dynamic_pointer_cast<Rational>(tmp);
			if (arg1.get())
				return shared_itype(new Rational(-*arg1));
			std::shared_ptr<Complex>	arg2 = std::dynamic_pointer_cast<Complex>(tmp);
			if (arg2.get())
				return shared_itype(new Complex(-*arg2));
			std::shared_ptr<Matrix>		arg3 = std::dynamic_pointer_cast<Matrix>(tmp);
			if (arg3.get())
				return shared_itype(new Matrix(-*arg3));
			return nullptr;
		}

		void				print() const {
			std::cout << "(-";
			base::getRight()->print();
			std::cout <<')';			
		}
};

#endif