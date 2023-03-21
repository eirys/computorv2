/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:57:49 by etran             #+#    #+#             */
/*   Updated: 2023/03/21 16:46:15 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "atree_node.hpp"
# include "function.hpp"
# include "computor.hpp"

/**
 * Image	: Identifier ( E )
 * 
 * example:	f(22)
 * 			f(a + 22*3)
*/
class Image: public ATreeNode {
	public:
		typedef 			ATreeNode					base;
		typedef typename	base::unique_node			unique_node;
		typedef typename	base::shared_node			shared_node;
		typedef typename	base::weak_node				weak_node;

		typedef typename	base::unique_itype			unique_itype;
		typedef typename	base::shared_itype			shared_itype;
		typedef typename	base::weak_itype			weak_itype;

		/* Constructor ------------------------------------------------------------ */
		Image(const std::string& func_name, unique_node&& right, const std::string& context = std::string()):
			base(nullptr, std::move(right)),
			_func_name(func_name) {
				LOG("Creating image");
				if (func_name == context)
					throw RecursiveCall();
			}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Image() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval() {
			shared_itype				x_value = base::getRight()->eval();
			shared_itype				raw_ptr = Computor::find(_func_name);
			if (raw_ptr == nullptr)
				throw Identifier::ValueNotSet(_func_name);
			std::shared_ptr<Function>	f_ptr = std::dynamic_pointer_cast<Function>(raw_ptr);
			if (f_ptr == nullptr)
				throw NotAFunction(_func_name);
			Computor::push(f_ptr->getVarName(), x_value, _func_name);
			shared_itype				ret = (*f_ptr->getBody())->eval();
			return ret;
		}

		void				print() {
			LOG("[img]");
			std::cout << _func_name << '(';
			base::getRight()->print();
			std::cout << ')';
		}

		unique_node			toNode() {
			return unique_node(
				new Image(_func_name, std::move(base::getRight()))
			);
		}

		unique_node			clone() const {
			return unique_node(
				new Image(_func_name, base::getRight()->clone())
			);
		}

		Indeterminates		collapse() const {
			throw Indeterminates::ExpansionNotSupported();
		}

		/* Exception -------------------------------------------------------------- */
		class NotAFunction: public std::exception {
			public:
				NotAFunction() = delete;
				NotAFunction(const std::string& specificity):
					_specificity("`" + specificity + "` is not a function") {}

				const char* what() const throw() {
					return _specificity.c_str();
				}
			private:
				const std::string	_specificity;
		};

		class RecursiveCall: public std::exception {
			public:
				const char* what() const throw() {
					return "Function has a recursive call of itself";
				}
		};

	private:
		const std::string	_func_name;
};


#endif