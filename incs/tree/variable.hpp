/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:24:40 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 20:19:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include "atree_node.hpp"

template <class T>
class Variable: virtual public ATreeNode<T> {
	public:
		typedef 			ATreeNode<T>			base;
		typedef typename	base::value_type		value_type;
		typedef typename	base::unique_node		unique_node;
		typedef typename	base::shared_node		shared_node;
		typedef typename	base::weak_node			weak_node;

		// Initialized constructor
		Variable(const value_type& value):
			base(),
			_value(value) {}

		// Destructor
		virtual ~Variable() {}

		const value_type	eval() const {
			return value_type(_value);
		}

		void				print() const {
			std::cout << _value;
		}

	private:
		T			_value;
};

#endif