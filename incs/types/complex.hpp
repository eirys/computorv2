/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:07:35 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "rational.hpp"

class Complex {
	public:
		Complex();
		Complex(const std::string&& buf);
		virtual ~Complex();
		Complex(const Complex& x);
		Complex& operator=(const Complex& rhs);

		const Rational&	getReal() const;
		const Rational& getImaginary() const;

		bool			isReal() const;
		bool			isImaginary() const;

	private:
		Rational	_re;
		Rational	_im;
};

bool			operator==(const Complex& x, const Complex& y);

std::ostream&	operator<<(std::ostream& o, const Complex& x);

#endif