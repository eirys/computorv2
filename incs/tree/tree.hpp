/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:04:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 12:49:06 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "tree_node.hpp"
# include "variable.hpp"

# include "add.hpp"
# include "substract.hpp"
# include "divide.hpp"
# include "multiply.hpp"
# include "negate.hpp"

/**
 * AST (Abstract Syntax Tree)
*/
template <class T>
class Tree {
	public:
		typedef				T						value_type;
		typedef				TreeNode<value_type>	node_base;
		typedef typename	node_base::node			node;

		// Default
		Tree() {}

		// Initialized
		Tree(node head):
			_head(head) {}

		// Destructor
		virtual ~Tree() {}

	protected:
		node			_head;
};

#endif