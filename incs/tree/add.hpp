/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:13:54 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 20:15:51 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_HPP
# define ADD_HPP

# include "tree.hpp"

template <class T>
class Add: virtual public ATreeNode<T> {
	public:
		typedef 			ATreeNode<T>			base;
		typedef typename	base::value_type		value_type;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		// Initialized constructor
		Add(const shared_node& left, const shared_node& right):
			base(left, right) {}

		// Destructor
		virtual ~Add() {}

		const value_type	eval() const {
			return base::getLeft()->eval() + base::getRight()->eval();
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