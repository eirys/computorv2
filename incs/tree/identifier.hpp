/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:10:49 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 14:13:20 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTIFIER_HPP
# define IDENTIFIER_HPP

# include <string>

# include "atree_node.hpp"
# include "computor.hpp"
# include "function.hpp"

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
		typedef				std::shared_ptr<Function>	shared_function;
		typedef				std::shared_ptr<Rational>	shared_rational;

		/* Constructor ------------------------------------------------------------ */
		Identifier(
			const std::string& name,
			unique_node&& value,
			const std::string& context = std::string(),
			const std::string& extra = std::string()
		):
			base(nullptr, std::move(value)),
			_name(name),
			_context(context),
			_extra(extra) {
				LOG("Creating" << (!context.empty()? " contexted " + context + " " : "")
				<<" identifier `" << name <<"` with extra: `" +extra+"`" );
			}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Identifier() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype		eval() const {
			DEBUG(
				"Identifier " << _name << " in context: "
				<< (_context.empty() ? "none" : _context)
			);

			if (base::getRight() == nullptr) {
				// Not set, check existing in local context
				shared_itype	value = Computor::find(_name, _context);
				shared_itype	global = Computor::find(_name);
				shared_function	f_ptr = std::dynamic_pointer_cast<Function>(global);

				if (f_ptr != nullptr && _extra.empty()) {
					throw MissingVariableName();
				} else if (global != nullptr) {
					return global;
				} else if (value == nullptr
					&& Computor::to_compute()
					&& !Computor::to_solve()) {
					throw ValueNotSet(_name, _context);
				}
				return value;
			} else {
				// Set a new value
				shared_itype	value = base::getRight()->eval();
				if (value == nullptr)
					throw RhsNotSet();
				shared_function	f_ptr = std::dynamic_pointer_cast<Function>(value);
				if (f_ptr != nullptr) {
					if (!_extra.empty()) {
						Computor::create_context(_name, f_ptr->getVarName());
					} else {
						throw BadFunctionDefinition();
					}
				}
				Computor::push(_name, value);
				return value;
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

		Indeterminates			collapse() const {
			const shared_itype		value = eval();
			if (value == nullptr) {
				// This identifier is an indeterminate
				if (!_context.empty()) {
					// It should be a function element
					Computor::subcontext	sub = Computor::find_context(_context);
					if (sub.front().first.first != utils::toLower(_name)) {
						// Unmatched
						throw ValueNotSet(_name, _context);
					}
				}
				return Indeterminates(nullptr, _name);
			}
			// Regular value
			const shared_function	f_ptr =
				std::dynamic_pointer_cast<Function>(value);
			const shared_rational	factor =
				std::dynamic_pointer_cast<Rational>(value);
			if (f_ptr == nullptr && factor == nullptr) {
				DEBUG("Here");
				throw Indeterminates::ExpansionNotSupported();
			} else if (f_ptr != nullptr) {
				return (*f_ptr->getBody())->collapse();
			} else {
				return Indeterminates(factor);
			}
		}

		/* Exception -------------------------------------------------------------- */
		class ValueNotSet: public std::exception {
			public:
				ValueNotSet() = delete;
				ValueNotSet(
					const std::string& name,
					const std::string& context = std::string()
				):
					_specificity(
						"Variable `" + name + "` not set"
						+ (context.empty() ? "" : (" in function `" + context + "`"))
					) {}

				const char* what() const throw() {
					return _specificity.c_str();
				}
			private:
				const std::string	_specificity;
		};
		class BadFunctionDefinition: public std::exception {
			public:
				const char* what() const throw() {
					return "Missing variable name in function definition";
				}
		};
		class MissingVariableName: public std::exception {
			public:
				const char* what() const throw() {
					return "Missing variable name for function declaration";
				}
		};
		class RhsNotSet: public std::exception {
			public:
				const char* what() const throw() {
					return "Rhs value is not set";
				}
		};

		/* Getter ----------------------------------------------------------------- */
		const std::string&		getName() const {
			return _name;
		}

	private:
		const std::string		_name;
		const std::string		_context;
		const std::string		_extra;
		std::string				_buffer_name;
};

#endif