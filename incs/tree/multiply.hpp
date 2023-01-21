/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:39:57 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 20:16:56 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLY_HPP
# define MULTIPLY_HPP

# include "atree_node.hpp"

template <class T>
class Multiply: public virtual ATreeNode<T> {
	public:
		typedef 			ATreeNode<T>			base;
		typedef typename	base::value_type		value_type;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		// Initialized constructor
		Multiply(const shared_node& left, const shared_node& right):
			base(left, right) {}

		// Destructor
		virtual ~Multiply() {}

		const value_type	eval() const {
			return base::getLeft()->eval() * base::getRight()->eval();
		}

		void				print() const {
			base::getLeft()->print();
			std::cout << '*';
			base::getRight()->print();
		}
};

#endif