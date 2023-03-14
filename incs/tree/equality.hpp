/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equality.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:43:36 by etran             #+#    #+#             */
/*   Updated: 2023/03/14 12:54:58 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUALITY_HPP
# define EQUALITY_HPP

# include "atree_node.hpp"

class Equality: public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Constructor ------------------------------------------------------------ */
		Equality(unique_node&& left, unique_node&& right):
			base(std::move(left), std::move(right)) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Equality() {}

		const shared_itype	eval() {
			if (base::getLeft() == base::getRight())
				std::cout << "True";
			else
				std::cout << "False";
			return nullptr;
		}

		void				print() {
			base::getLeft()->print();
			std::cout << " == "
			base::getRight()->print();
		}

		unique_node			toNode() {
			return unique_node(
				new Equality(std::move(base::getLeft()), std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Equality(base::getLeft()->clone(), base::getRight()->clone())
			);
		}
};

#endif