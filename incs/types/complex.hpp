/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 20:53:21 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "rational.hpp"

class Complex {
	public:
		Complex(const std::string&& buf);
		virtual ~Complex();

		Complex(const Complex& x);

	private:
		Rational	_re;
		Rational	_im;

}

#endif