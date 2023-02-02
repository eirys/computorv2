/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/27 12:00:10 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>

# include "utils.hpp"
# include "itype.hpp"

class Complex;
class Matrix;

/**
 * Rational		: { - } digit { digit | { . digit } }
 * 
 * example:		-123
 * 				0.56
 *
*/
class Rational: public IType {
	public:
		typedef typename	IType::unique_itype		unique_itype;
		typedef typename	IType::shared_itype		shared_itype;
		typedef typename	IType::weak_itype		weak_itype;

		Rational();
		virtual ~Rational();

		Rational(long double x);
		Rational(const Rational& x);
		
		Rational&		operator=(long double rhs);
		Rational&		operator=(const Rational& rhs);

		// IType operators
		shared_itype	operator+(const shared_itype& rhs) const;
		shared_itype	operator-(const shared_itype& rhs) const;
		shared_itype	operator*(const shared_itype& rhs) const;
		shared_itype	operator/(const shared_itype& rhs) const;

		// Arith operators
		Rational		operator-() const;

		Rational&		operator+=(const Rational& rhs);
		Rational&		operator++();
		Rational		operator++(int);
		Rational		operator+(const Rational& rhs) const;

		Rational&		operator-=(const Rational& rhs);
		Rational&		operator--();
		Rational		operator--(int);
		Rational		operator-(const Rational& rhs) const;

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

		shared_itype	_rational_operator(
							Rational (Rational::*f)(const Rational&) const,
							const std::shared_ptr<Rational>& r_ptr
							) const;
		shared_itype	_complex_operator(
							Complex (Rational::*f)(const Complex&) const,
							const std::shared_ptr<Complex>& r_ptr
							) const;
		shared_itype	_matrix_operator(
							Matrix (Rational::*f)(const Matrix&) const,
							const std::shared_ptr<Matrix>& r_ptr
							) const;
};

bool			operator==(const Rational& x, const Rational& y);
bool			operator<(const Rational& x, const Rational& y);
bool			operator!=(const Rational& x, const Rational& y);
bool			operator<=(const Rational& x, const Rational& y);
bool			operator>(const Rational& x, const Rational& y);
bool			operator>=(const Rational& x, const Rational& y);

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif