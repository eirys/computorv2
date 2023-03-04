/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:57:53 by eli               #+#    #+#             */
/*   Updated: 2023/03/04 21:34:15 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

# include "atree_node.hpp"

/**
 * Function		: name ( Variable ) = E
 * 
 * with
 * name			: char { char | _ }+
*/
class Function: public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		Function(
			const std::string& name,
			unique_node&& body
			):
			base(nullptr/* identifier */, std::move(body)/* body.getHead() */),
			_name(name) {}

		virtual ~Function() {}

		const shared_itype		eval() {
			return base::getRight()->eval();
		}

		void					print() {
			std::cout << "Function '" << _name << "': ";
			base::getRight()->print();
		}

	private:
		const std::string		_name;

};

#endif