/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:57:49 by etran             #+#    #+#             */
/*   Updated: 2023/03/14 09:27:54 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "atree_node.hpp"
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
		Image(const std::string& func_name, unique_node&& x):
			base(nullptr, std::move(x)),
			_func_name(func_name) {
				LOG("Creating image");
			}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Image() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval() {
			shared_itype	x_value = base::getRight()->eval();
			shared_itype	f_ptr = Computor::find(_func_name, true);
			if (f_ptr == nullptr)
				throw std::exception();
			Function&		function = *(std::dynamic_pointer_cast<Function>(f_ptr));
			Computor::create_context();
			Computor::push(function.getVarName(), x_value/* , _func_name */);
			shared_itype	ret = (*function.getBody())->eval();
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

	private:
		const std::string	_func_name;
};


#endif