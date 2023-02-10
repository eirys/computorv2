/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atree_node.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:16:37 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 11:56:23 by eli              ###   ########.fr       */
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
		const shared_node			getLeft() const {
			return _left.lock();
		}
		const shared_node			getRight() const {
			return _right.lock();
		}
		void						setLeft(const shared_node& new_left) {
			_left = new_left;
		}
		void						setRight(const shared_node& new_right) {
			_right = new_right;
		}

		/* Override --------------------------------------------------------------- */
		virtual const shared_itype	eval() const = 0;
		virtual void				print() const = 0;

	protected:
		/* Default ---------------------------------------------------------------- */
		ATreeNode():
			_left(),
			_right() {}

		/* Initialized Constructor ------------------------------------------------ */
		ATreeNode(const shared_node& left, const shared_node& right):
			_left(left),
			_right(right) {}

		/* ------------------------------------------------------------------------ */
		weak_node					_left;
		weak_node					_right;
};

#endif