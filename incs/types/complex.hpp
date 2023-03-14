/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/03/14 17:42:54 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "utils.hpp"
# include "itype.hpp"
# include "rational.hpp"

class Matrix;
class Function;
class ATreeNode;

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
		typedef typename	IType::unique_itype				unique_itype;
		typedef typename	IType::shared_itype				shared_itype;
		typedef typename	IType::weak_itype				weak_itype;
		typedef				std::unique_ptr<ATreeNode>		unique_node;

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
		bool			operator==(const shared_itype& rhs_ptr) const;

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
		bool			operator==(const Rational& rhs) const;

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
		const Rational&	getReal() const;
		const Rational&	getImaginary() const;

		/* Tools ------------------------------------------------------------------ */
		bool			operator!() const;
		bool			isComplex() const;
		bool			isReal() const;
		bool			isImaginary() const;

		/* Relational Operators --------------------------------------------------- */
		bool			operator==(const Complex& y) const;
		bool			operator!=(const Complex& y) const;

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
		shared_itype	_function_operator(
							Function (Complex::*f)(const Function&) const,
							const std::shared_ptr<Function>& f_ptr
						) const;
};

std::ostream&			operator<<(std::ostream& o, const Complex& x);

#endif