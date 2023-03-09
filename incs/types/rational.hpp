/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/03/09 14:18:39 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>

# include "utils.hpp"
# include "itype.hpp"

class Complex;
class Matrix;
class Function;

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

		/* IType Operators -------------------------------------------------------- */
		shared_itype	clone() const;
		shared_itype	operator+(const shared_itype& rhs) const;
		shared_itype	operator-(const shared_itype& rhs) const;
		shared_itype	operator*(const shared_itype& rhs) const;
		shared_itype	operator/(const shared_itype& rhs) const;
		shared_itype	operator^(const shared_itype& rhs) const;
		shared_itype	operator%(const shared_itype& rhs) const;

		/* Arith Operators -------------------------------------------------------- */
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

		/* Complex Operators ------------------------------------------------------ */
		Complex			operator+(const Complex& rhs) const;
		Complex			operator-(const Complex& rhs) const;
		Complex			operator*(const Complex& rhs) const;
		Complex			operator/(const Complex& rhs) const;
		Complex			operator^(const Complex& rhs) const;
		Complex			operator%(const Complex& rhs) const;

		/* Matrix Operators ------------------------------------------------------- */
		Matrix			operator+(const Matrix& rhs) const;		// undefined
		Matrix			operator-(const Matrix& rhs) const;		// undefined
		Matrix			operator*(const Matrix& rhs) const;
		Matrix			operator/(const Matrix& rhs) const;
		Matrix			operator^(const Matrix& rhs) const;		// undefined
		Matrix			operator%(const Matrix& rhs) const;		// undefined
		
		/* Function Operators ----------------------------------------------------- */
		Function		operator+(const Function& rhs) const;
		Function		operator-(const Function& rhs) const;
		Function		operator*(const Function& rhs) const;
		Function		operator/(const Function& rhs) const;
		Function		operator^(const Function& rhs) const;
		Function		operator%(const Function& rhs) const;

		/* Getter ----------------------------------------------------------------- */
		long double		getVal() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isInteger() const;

	private:
		long double		_val;

		/* Utils ------------------------------------------------------------------ */
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
		shared_itype	_function_operator(
							Function (Rational::*f)(const Function&) const,
							const std::shared_ptr<Function>& f_ptr
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