/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:05:58 by etran             #+#    #+#             */
/*   Updated: 2023/03/22 17:30:10 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULO_HPP
# define MODULO_HPP

# include "atree_node.hpp"

class Modulo: public virtual ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Constructor ------------------------------------------------------------ */
		Modulo(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Modulo() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval() const {
			const shared_itype&			tmp = base::getLeft()->eval();

			std::shared_ptr<Rational>	arg1 = std::dynamic_pointer_cast<Rational>(tmp);
			if (arg1.get())
				return *arg1 % base::getRight()->eval();
			std::shared_ptr<Complex>	arg2 = std::dynamic_pointer_cast<Complex>(tmp);
			if (arg2.get())
				return *arg2 % base::getRight()->eval();
			std::shared_ptr<Matrix>		arg3 = std::dynamic_pointer_cast<Matrix>(tmp);
			if (arg3.get())
				return *arg3 % base::getRight()->eval();
			std::shared_ptr<Function>	arg4 = std::dynamic_pointer_cast<Function>(tmp);
			if (arg4.get())
				return *arg4 % base::getRight()->eval();
			return nullptr;
		}

		void				print() {
			LOG("[mod]");
			base::getLeft()->print();
			std::cout << '%';
			base::getRight()->print();
		}

		unique_node			toNode() {
			return unique_node(
				new Modulo(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Modulo(base::getLeft()->clone(), base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			throw Indeterminates::ExpansionNotSupported();
		}
};

#endif
