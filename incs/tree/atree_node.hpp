/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atree_node.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:16:37 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 20:19:15 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATREE_NODE_HPP
# define ATREE_NODE_HPP

# include <memory>

template <class T>
class ATreeNode {
	public:
		typedef typename	std::unique_ptr<ATreeNode<T>>	unique_node;
		typedef typename	std::shared_ptr<ATreeNode<T>>	shared_node;
		typedef typename	std::weak_ptr<ATreeNode<T>>		weak_node;
		typedef				T								value_type;

		// Destructor
		virtual	~ATreeNode() {}

		// Base functions
		const shared_node			getLeft() const {
			return _left.lock();
		}
		const shared_node			getRight() const {
			return _right.lock();
		}

		// Override
		virtual const value_type	eval() const = 0;
		virtual void				print() const = 0;

	protected:
		// Default
		ATreeNode():
			_left(),
			_right() {}

		// Initialized constructor
		ATreeNode(const shared_node& left, const shared_node& right):
			_left(left),
			_right(right) {}

		weak_node					_left;
		weak_node					_right;
};

#endif