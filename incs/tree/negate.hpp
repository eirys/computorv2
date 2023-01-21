/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:10:38 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 17:31:19 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEGATE_HPP
# define NEGATE_HPP

# include "tree_node.hpp"

template <class T>
class Negate: public virtual TreeNode<T> {
	public:
		typedef 			TreeNode<T>				base;
		typedef typename	base::value_type		value_type;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		// Initialized constructor
		Negate(const shared_node& right):
			base(nullptr, right) {}

		// Destructor
		virtual ~Negate() {}

		const value_type	eval() const {
			return -base::getRight()->eval();
		}

		void				print() const {
			std::cout << "(-";
			base::getRight()->print();
			std::cout <<')';			
		}
};

#endif