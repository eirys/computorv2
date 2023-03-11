/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:57:49 by etran             #+#    #+#             */
/*   Updated: 2023/03/11 18:34:01 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_HPP
# define IMAGE_HPP

# include "atree_node.hpp"
# include "computor.hpp"

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
		// Image(unique_node&& func, unique_node&& x, const std::string& func_name):
		// 	base(std::move(func), std::move(x)) {}
		Image(const std::string& func_name, unique_node&& x):
			base(nullptr, std::move(x)),
			_func_name(func_name) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Image() {}

		/* ------------------------------------------------------------------------ */
		const shared_itype	eval() {
			// Replace occurence of x
			shared_itype	x_value = base::getRight()->eval();
			shared_itype	f_ptr = Computor::find(_func_name); // replace
			if (f_ptr == nullptr)
				throw std::exception();
			Function&		function = *(std::dynamic_pointer_cast<Function>(f_ptr));
			Computor::push(function.getVarName(), x_value, _func_name);
			return (*function.getBody())->eval();
		}

		void				print() {
			std::cout << _func_name << '(';
			base::getRight()->print();
			std::cout << ')';
		}

		unique_node			toNode() {
			return unique_node(
				new Image(_func_name, std::move(base::getRight()))
			);
		}

	private:
		const std::string	_func_name;
};


#endif