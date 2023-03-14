/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:49 by eli               #+#    #+#             */
/*   Updated: 2023/03/14 12:18:34 by etran            ###   ########.fr       */
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
		Identifier(
			const std::string& name,
			unique_node&& value,
			bool in_context = false,
			const std::string& extra = std::string()
			):
				base(nullptr, std::move(value)),
				_name(name),
				_context(in_context),
				_extra(extra) {
					if (name == "i")
						throw InvalidName();
					LOG("Creating " << (in_context ? "contexted " : "") <<"identifier `"
					<< name <<"` with extra: `" +extra+"`" );
				}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Identifier() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype		eval() {
			if (base::getRight() == nullptr) {
				// Not set, check existing in local context
				shared_itype	value;
				value = Computor::find(_name, _context);
				if (value == nullptr)
					throw Identifier::ValueNotSet(_name);
				return value;
			} else {
				// Set a new value
				Computor::push(_name, base::getRight()->eval());
				return base::getRight()->eval();
			}
		}

		void					print() {
			LOG("[id]");
			std::cout << _name;
			if (!_extra.empty())
				std::cout << '(' << _extra << ')';
		}

		unique_node				toNode() {
			return unique_node(
				new Identifier(
					_name,
					std::move(base::getRight()),
					_context,
					_extra
				)
			);
		}

		unique_node				clone() const {
			unique_node		new_right;
			if (base::getRight() != nullptr)
				new_right = base::getRight()->clone();
			return unique_node(
				new Identifier(
					_name,
					std::move(new_right),
					_context,
					_extra
				)
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

		class InvalidName: public std::exception {
			public:
				const char* what() const throw() {
					return "Can't use `i` as identifier name";
				}
		};

		/* Getter ----------------------------------------------------------------- */
		const std::string&		getName() const {
			return _name;
		}

	private:
		const std::string		_name;
		bool					_context;
		const std::string		_extra;
};

#endif