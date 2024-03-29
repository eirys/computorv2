/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:10:38 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 23:46:15 by eli              ###   ########.fr       */
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

		/* Constructor ------------------------------------------------------------ */
		Negate(unique_node&& right):
			base(nullptr, std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Negate() {}

		/* ------------------------------------------------------------------------ */
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
			std::shared_ptr<Function>	arg4 = std::dynamic_pointer_cast<Function>(tmp);
			if (arg4.get())
				return shared_itype(new Function(-*arg4));
			return nullptr;
		}

		void				print() {
			LOG("[neg]");
			std::cout << "(-";
			base::getRight()->print();
			std::cout <<')';			
		}

		unique_node			toNode() {
			return unique_node(
				new Negate(std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Negate(base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			Indeterminates	ind = -(base::getRight()->collapse());
			DEBUG("Negate: " << ind);
			#ifdef __DEBUG
			ind.show();
			#endif
			return ind;
		}
};

#endif