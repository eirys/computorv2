/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:49 by eli               #+#    #+#             */
/*   Updated: 2023/03/06 15:58:18 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFIER_HPP
# define IDENTIFIER_HPP

# include <string>

# include "atree_node.hpp"
# include "computor.hpp"

/**
 * Identifier	: { char | _ }+
 * 
 * example:		variable_a
 * 				_random__Variable
 * 
*/
class Identifier: public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Constructor ------------------------------------------------------------ */
		Identifier(const std::string& name, unique_node&& value = nullptr):
			base(nullptr, std::move(value)),
			_name(name) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Identifier() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype		eval() {
			if (base::getRight() == nullptr) {
				shared_itype	value = Computor::find(_name);
				if (value == nullptr)
					throw Identifier::ValueNotSet(_name);
				return value;
			}
			Computor::push(_name, base::getRight()->eval());
			return base::getRight()->eval();
		}

		void					print() {
			std::cout << _name;
			if (base::getRight() == nullptr)
				return;
			std::cout << ": ";
			base::getRight()->print();
		}

		unique_node				toNode() {
			return unique_node(
				new Identifier(_name, std::move(base::getRight()))
			);
		}

		/* Exception -------------------------------------------------------------- */
		class ValueNotSet: public std::exception {
			public:
				ValueNotSet() = delete;
				ValueNotSet(const std::string& name):
					_specificity("Variable `" + name + "` not set") {}

				const char* what() const throw() {
					return _specificity.c_str();
				}
			private:
				const std::string	_specificity;
		};

	private:
		const std::string		_name;
};

#endif