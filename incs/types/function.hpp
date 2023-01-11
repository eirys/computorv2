/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:57:53 by eli               #+#    #+#             */
/*   Updated: 2023/01/11 21:29:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

// # include <map>
// # include <memory>

// # include "rational.hpp"

// // template <class T>
// class Variable {
// 	private:
// 		const std::string		name;
// };

// class FunctionElement {
// 	public:
// 		typedef		T							value_type;
// 		typedef		U							arg_type;
// 		typedef		std::shared_ptr<arg_type>	arg_pointer;

// 		FunctionElement(value_type (value_type::*f)() const, const arg_type& arg = 0) :
// 			_function(f),
// 			_arg(arg_pointer(new arg_type(arg))) {}

// 		FunctionElement() {}

// 		virtual ~FunctionElement() {}

// 		template <class T>
// 		T	getResult(const T& x) const {
// 			if (_arg)
// 				return _function(x, *_arg);
// 			else
// 				return _function(x);
// 		}

// 	private:
// 		value_type				(value_type::*_function)() const;
// 		arg_pointer				_arg;
// 		// arg_type*				_arg;
// 		// std::list<value_type>	_args;
// };

// class Function {
// 	public:
// 		typedef 	FunctionElement		element;
// 		typedef		std::list<element>	elements;
		
// 		Function() {}
// 		virtual ~Function() {}

// 		template <class T>
// 		T	getResult(const T& x) const {
// 			T	sum;

// 			for (typename elements::const_iterator it = _terms.begin();
// 			it != _terms.end();
// 			++it) {
// 				sum += it->getResult(x);
// 			}
// 			return sum;
// 		}

// 		template <class T, class U>
// 		void		add(T (T::*f)(), const U& arg = 0) {
// 			_terms.push_back(FunctionElement(f, arg));
// 		}

// 	private:
// 		elements				_terms;
// 		// std::list<element>	_terms;
// };

#endif