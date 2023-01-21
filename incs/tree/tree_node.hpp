/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:46:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 12:48:40 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_HPP
# define TREE_NODE_HPP

# include <memory>

template <class T>
class TreeNode {
	public:
		typedef typename	std::unique_ptr<TreeNode<T>>	unique_node;
		typedef typename	std::shared_ptr<TreeNode<T>>	shared_node;
		typedef typename	std::weak_ptr<TreeNode<T>>		weak_node;
		typedef				T								value_type;

		// Destructor
		virtual	~TreeNode() {}

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
		TreeNode():
			_left(),
			_right() {}

		// Initialized constructor
		TreeNode(const shared_node& left, const shared_node& right):
			_left(left),
			_right(right) {}

		weak_node					_left;
		weak_node					_right;
};

#endif