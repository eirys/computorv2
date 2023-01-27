/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:49 by eli               #+#    #+#             */
/*   Updated: 2023/01/26 23:10:56 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFIER_HPP
# define IDENTIFIER_HPP

# include <string>

# include "atree_node.hpp"

/**
 * Identifier	: { char | _ }+
 * 
 * example:		variable_a
 * 				_random__Variable
 * 
*/
class Identifier: public ATreeNode {
	public:
		typedef 			ATreeNode				base;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		typedef typename	base::unique_itype		unique_itype;
		typedef typename	base::shared_itype		shared_itype;
		typedef typename	base::weak_itype		weak_itype;

		Identifier(const std::string& name, const shared_node& value = nullptr):
			base(nullptr, value),
			_name(name) {}

		virtual ~Identifier() {}

		const shared_itype		eval() const {
			if (base::getRight() == nullptr)
				throw Identifier::ValueNotSet();
			return base::getRight()->eval();
		}

		void					print() const {
			std::cout << _name;
			if (base::getRight() == nullptr)
				return;
			std::cout << ": ";
			base::getRight()->print();
		}

		class ValueNotSet: public std::exception {
			public:
				constexpr const char* what() const throw() {
					return "Variable value not set";
				}
		};

	private:
		const std::string		_name;
};

inline Identifier::shared_node	createIdentifier(
	const std::string& name,
	const Identifier::shared_node& value = nullptr
	) {
		return Identifier::shared_node(new Identifier(name, value));
	}

#endif