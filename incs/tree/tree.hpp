/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:59:51 by eli               #+#    #+#             */
/*   Updated: 2023/03/08 22:16:09 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "atree_node.hpp"

class Tree {
	public:
		typedef typename	ATreeNode::unique_node	unique_node;
		typedef typename	ATreeNode::shared_itype	shared_itype;

		Tree();
		Tree(const Tree& x);
		Tree(unique_node&& head);
		virtual ~Tree();

		void			print() const;
		shared_itype	eval() const;

	private:
		unique_node		_head;
};

#endif