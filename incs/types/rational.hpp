/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/11 22:48:46 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>

# include "utils.hpp"

class Complex;
class Matrix;

class Rational {
	public:
		Rational();
		virtual ~Rational();

		Rational(long double x);
		Rational(const Rational& x);
		Rational(const std::string&& buf);
		
		Rational&		operator=(long double rhs);
		Rational&		operator=(const Rational& rhs);

		// Arith. operators
		Rational&		operator+=(const Rational& rhs);
		Rational&		operator++();
		Rational		operator++(int);
		Rational		operator+(const Rational& rhs) const;

		Rational&		operator-=(const Rational& rhs);
		Rational&		operator--();
		Rational		operator--(int);
		Rational		operator-(const Rational& rhs) const;
		Rational		operator-() const;

		Rational&		operator*=(const Rational& rhs);
		Rational		operator*(const Rational& rhs) const;
		
		Rational&		operator/=(const Rational& rhs);
		Rational		operator/(const Rational& rhs) const;

		Rational&		operator^=(const Rational& rhs);
		Rational		operator^(const Rational& rhs) const;

		Rational&		operator%=(const Rational& rhs);
		Rational		operator%(const Rational& rhs) const;

		// Complex
		Complex			operator+(const Complex& rhs) const;
		Complex			operator-(const Complex& rhs) const;
		Complex			operator*(const Complex& rhs) const;
		Complex			operator/(const Complex& rhs) const;

		// Matrix
		Matrix			operator+(const Matrix& rhs) const;		// undefined
		Matrix			operator-(const Matrix& rhs) const;		// undefined
		Matrix			operator*(const Matrix& rhs) const;
		Matrix			operator/(const Matrix& rhs) const;

		// Getter
		long double		getVal() const;

		// Tools
		bool			operator!() const;
		bool			isInteger() const;

	private:
		long double		_val;
};

bool			operator==(const Rational& x, const Rational& y);
bool			operator<(const Rational& x, const Rational& y);
bool			operator!=(const Rational& x, const Rational& y);
bool			operator<=(const Rational& x, const Rational& y);
bool			operator>(const Rational& x, const Rational& y);
bool			operator>=(const Rational& x, const Rational& y);

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif