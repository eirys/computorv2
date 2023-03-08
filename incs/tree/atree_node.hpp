/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atree_node.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:16:37 by eli               #+#    #+#             */
/*   Updated: 2023/03/08 21:49:27 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATREE_NODE_HPP
# define ATREE_NODE_HPP

# include <memory>
# include <iostream>

# include "itype.hpp"
# include "rational.hpp"
# include "complex.hpp"
# include "matrix.hpp"
# include "indeterminates.hpp"

class ATreeNode {
	public:
		typedef typename	std::unique_ptr<ATreeNode>		unique_node;
		typedef typename	std::shared_ptr<ATreeNode>		shared_node;
		typedef typename	std::weak_ptr<ATreeNode>		weak_node;

		typedef				std::unique_ptr<IType>			unique_itype;
		typedef				std::shared_ptr<IType>			shared_itype;
		typedef				std::weak_ptr<IType>			weak_itype;

		/* Virtual Destructor ----------------------------------------------------- */
		virtual	~ATreeNode() {}

		/* Base Functions --------------------------------------------------------- */
		unique_node&				getLeft() {
			return _left;
		}
		unique_node&				getRight() {
			return _right;
		}
		void						setLeft(unique_node&& new_left) {
			_left = std::move(new_left);
		}
		void						setRight(unique_node&& new_right) {
			_right = std::move(new_right);
		}

		/* Override --------------------------------------------------------------- */
		virtual const shared_itype	eval() = 0;
		virtual void				print() = 0;
		virtual unique_node			toNode() = 0;

		// virtual Indeterminates		collapse() = 0;

	protected:
		/* Default ---------------------------------------------------------------- */
		ATreeNode():
			_left(),
			_right() {
				LOG("Created empty node");
			}

		/* Initialized Constructor ------------------------------------------------ */
		ATreeNode(unique_node&& left, unique_node&& right):
			_left(std::move(left)),
			_right(std::move(right)) {
				LOG("Created node");
			}

		/* ------------------------------------------------------------------------ */
		unique_node					_left;
		unique_node					_right;
};

#endif