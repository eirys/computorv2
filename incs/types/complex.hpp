/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 10:28:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "rational.hpp"
# include "utils.hpp"

class Complex {
	public:
		Complex();
		virtual ~Complex();

		Complex(long double x);
		Complex(long double x, long double y);
		Complex(const Rational& x, const Rational& y);
		Complex(const Complex& x);
		explicit Complex(const std::string&& buf);

		Complex& 		operator=(long double rhs);
		Complex& 		operator=(const Complex& rhs);

		// Arith. operators
		Complex&		conjugate();
		Complex&		rationalize();

		Complex&		operator+=(const Complex& rhs);
		Complex			operator+(const Complex& rhs) const;

		Complex&		operator-=(const Complex& rhs);
		Complex			operator-(const Complex& rhs) const;
		Complex			operator-() const;

		Complex&		operator*=(const Complex& rhs);
		Complex			operator*(const Complex& rhs) const;
		
		Complex&		operator/=(const Complex& rhs);
		Complex			operator/(const Complex& rhs) const;

		// Getter
		const Rational&	getReal() const;
		const Rational& getImaginary() const;

		bool			isComplex() const;
		bool			isReal() const;
		bool			isImaginary() const;

	private:
		Rational		_re;
		Rational		_im;

		void			_parseBuf(const std::string& buf);
};

bool			operator==(const Complex& x, const Complex& y);
bool			operator!=(const Complex& x, const Complex& y);

std::ostream&	operator<<(std::ostream& o, const Complex& x);

#endif