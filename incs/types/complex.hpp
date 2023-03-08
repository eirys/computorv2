/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/03/08 22:07:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "utils.hpp"
# include "itype.hpp"
# include "rational.hpp"

class Matrix;
class Function;

/**	
 * Complex		: real + imaginary
 * 				| imaginary + real
 * 				| real
 * 				| imaginary		
 * 
 * with
 * 
 * real			: Rational
 * 
 * imaginary	: Rational * i
 * 				| i * Rational
 * 
 * example:		25 + 4i
 * 				2i
 * 
*/
class Complex: public IType {
	public:
		typedef typename	IType::unique_itype		unique_itype;
		typedef typename	IType::shared_itype		shared_itype;
		typedef typename	IType::weak_itype		weak_itype;

		Complex();
		virtual ~Complex();

		Complex(const Complex& x);
		Complex(const Rational& x, const Rational& y = Rational(0));

		Complex& 		operator=(const Complex& rhs);

		/* IType Operators -------------------------------------------------------- */
		shared_itype	clone() const;
		shared_itype	operator+(const shared_itype& rhs_ptr) const;
		shared_itype	operator-(const shared_itype& rhs_ptr) const;
		shared_itype	operator*(const shared_itype& rhs_ptr) const;
		shared_itype	operator/(const shared_itype& rhs_ptr) const;
		shared_itype	operator^(const shared_itype& rhs_ptr) const;
		shared_itype	operator%(const shared_itype& rhs_ptr) const;

		/* Arith. Operators ------------------------------------------------------- */
		Complex			operator-() const;
		Complex			conjugate() const;

		Complex&		operator+=(const Complex& rhs);
		Complex			operator+(const Complex& rhs) const;

		Complex&		operator-=(const Complex& rhs);
		Complex			operator-(const Complex& rhs) const;

		Complex&		operator*=(const Complex& rhs);
		Complex			operator*(const Complex& rhs) const;
		
		Complex&		operator/=(const Complex& rhs);
		Complex			operator/(const Complex& rhs) const;

		Complex&		operator^=(const Rational& rhs);
		Complex			operator^(const Complex& rhs) const;

		Complex&		operator%=(const Rational& rhs);
		Complex			operator%(const Complex& rhs) const;

		/* Rational Operators ----------------------------------------------------- */
		Complex			operator+(const Rational& rhs) const;
		Complex			operator-(const Rational& rhs) const;
		Complex			operator*(const Rational& rhs) const;
		Complex			operator/(const Rational& rhs) const;
		Complex			operator^(const Rational& rhs) const;
		Complex			operator%(const Rational& rhs) const;

		/* Matrix Operators ------------------------------------------------------- */
		Matrix			operator+(const Matrix& rhs) const;		// undefined
		Matrix			operator-(const Matrix& rhs) const;		// undefined
		Matrix			operator*(const Matrix& rhs) const;
		Matrix			operator/(const Matrix& rhs) const;
		Matrix			operator^(const Matrix& rhs) const;		// undefined
		Matrix			operator%(const Matrix& rhs) const;		// undefined

		/* Rational Operators ----------------------------------------------------- */
		Function		operator+(const Function& rhs) const;
		Function		operator-(const Function& rhs) const;
		Function		operator*(const Function& rhs) const;
		Function		operator/(const Function& rhs) const;
		Function		operator^(const Function& rhs) const;
		Function		operator%(const Function& rhs) const;

		/* Getter ----------------------------------------------------------------- */
		Rational		getReal() const;
		Rational		getImaginary() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isComplex() const;
		bool			isReal() const;
		bool			isImaginary() const;

	private:
		Rational		_re;
		Rational		_im;

		/* Utils ------------------------------------------------------------------ */
		shared_itype	_rational_operator(
							Complex (Complex::*f)(const Rational&) const,
							const std::shared_ptr<Rational>& r_ptr
							) const;
		shared_itype	_complex_operator(
							Complex (Complex::*f)(const Complex&) const,
							const std::shared_ptr<Complex>& c_ptr
							) const;
		shared_itype	_matrix_operator(
							Matrix (Complex::*f)(const Matrix&) const,
							const std::shared_ptr<Matrix>& m_ptr
							) const;
};

bool					operator==(const Complex& x, const Complex& y);
bool					operator!=(const Complex& x, const Complex& y);

std::ostream&			operator<<(std::ostream& o, const Complex& x);

#endif