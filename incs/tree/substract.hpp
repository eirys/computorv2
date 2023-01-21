/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substract.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:34:39 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 15:10:04 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTRACT_HPP
# define SUBSTRACT_HPP

# include "tree_node.hpp"

template <class T>
class Substract: virtual public TreeNode<T> {
	public:
		typedef 			TreeNode<T>				base;
		typedef typename	base::value_type		value_type;
		typedef typename	base::node				node;

		// Initialized
		Substract(node left, node right):
			base(left, right) {}

		// Destructor
		virtual ~Substract() {}

		const value_type	eval()  const {
			return base::getLeft()->eval() - base::getRight()->eval();
		}

		void				print() const {
			std::cout << '(';
			base::getLeft()->print();
			std::cout << '-';
			base::getRight()->print();
			std::cout << ')';
		}
};

#endif