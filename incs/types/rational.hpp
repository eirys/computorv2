/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 13:22:49 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>
# include <memory>

# include "utils.hpp"
# include "itype.hpp"

class Complex;
class Matrix;
class Function;
class ATreeNode;

/**
 * Rational		: { - } digit { digit | { . digit } }
 * 
 * example:		-123
 * 				0.56
 *
*/
class Rational: public IType {
	public:
		typedef typename	IType::unique_itype				unique_itype;
		typedef typename	IType::shared_itype				shared_itype;
		typedef typename	IType::weak_itype				weak_itype;
		typedef				std::unique_ptr<ATreeNode>		unique_node;

		Rational();
		virtual ~Rational();

		Rational(long double x);
		Rational(const Rational& x);
		
		Rational&		operator=(long double rhs);
		Rational&		operator=(const Rational& rhs);

		/* IType Operators -------------------------------------------------------- */
		shared_itype	clone() const;
		shared_itype	negate() const;
		shared_itype	operator+(const shared_itype& rhs) const;
		shared_itype	operator-(const shared_itype& rhs) const;
		shared_itype	operator*(const shared_itype& rhs) const;
		shared_itype	operator/(const shared_itype& rhs) const;
		shared_itype	operator^(const shared_itype& rhs) const;
		shared_itype	operator%(const shared_itype& rhs) const;
		bool			operator==(const shared_itype& rhs) const;

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
		bool			operator==(const Complex& rhs) const;

		/* Matrix Operators ------------------------------------------------------- */
		Matrix			operator+(const Matrix& rhs) const;		// undefined
		Matrix			operator-(const Matrix& rhs) const;		// undefined
		Matrix			operator*(const Matrix& rhs) const;
		Matrix			operator/(const Matrix& rhs) const;		// undefined
		Matrix			operator^(const Matrix& rhs) const;		// undefined
		Matrix			operator%(const Matrix& rhs) const;		// undefined
		bool			operator==(const Matrix& rhs) const;	// undefined
		
		/* Function Operators ----------------------------------------------------- */
		Function		operator+(const Function& rhs) const;
		Function		operator-(const Function& rhs) const;
		Function		operator*(const Function& rhs) const;
		Function		operator/(const Function& rhs) const;
		Function		operator^(const Function& rhs) const;
		Function		operator%(const Function& rhs) const;
		bool			operator==(const Function& rhs) const;	// undefined

		/* Getter ----------------------------------------------------------------- */
		long double		getVal() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isInteger() const;

		/* Relational Operators --------------------------------------------------- */
		bool			operator==(const Rational& y) const;
		bool			operator<(const Rational& y) const;
		bool			operator!=(const Rational& y) const;
		bool			operator<=(const Rational& y) const;
		bool			operator>(const Rational& y) const;
		bool			operator>=(const Rational& y) const;

	private:
		long double		_val;

		/* Utils ------------------------------------------------------------------ */
		shared_itype	_rational_operator(
							Rational (Rational::*f)(const Rational&) const,
							const std::shared_ptr<Rational>& r_ptr
						) const;
		shared_itype	_complex_operator(
							Complex (Rational::*f)(const Complex&) const,
							const std::shared_ptr<Complex>& c_ptr
						) const;
		shared_itype	_matrix_operator(
							Matrix (Rational::*f)(const Matrix&) const,
							const std::shared_ptr<Matrix>& m_ptr
						) const;
		shared_itype	_function_operator(
							Function (Rational::*f)(const Function&) const,
							const std::shared_ptr<Function>& f_ptr
						) const;
};

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif