/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/03/18 11:41:14 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <vector>
# include <iomanip>
# include <sstream>
# include <ios>

# include "utils.hpp"
# include "math.hpp"

class Rational;
class Complex;
class Function;
class ATreeNode;

/**
 * Matrix	: [ row { ; row } ]
 * 
 * with
 * row		: [ Rational { , Rational } ]
 * 
 * ex:		[[ 1, 5.25, 11], [0, 0 ,0]]
*/
class Matrix: public IType {
	public:
		typedef typename	IType::unique_itype			unique_itype;
		typedef typename	IType::shared_itype			shared_itype;
		typedef typename	IType::weak_itype			weak_itype;
		typedef				std::unique_ptr<ATreeNode>	unique_node;

		typedef				std::vector<Rational>		row;
		typedef typename	std::vector<row>			matrix;

		Matrix();
		virtual ~Matrix();
		
		Matrix(const Matrix& x);
		Matrix(const matrix&& x);

		Matrix(size_t n, const Rational&& factor = Rational(0));
		Matrix(size_t n, size_t p);

		Matrix&				operator=(const Matrix& rhs);

		/* Element Access --------------------------------------------------------- */
		row&				operator[](size_t index);
		const row&			operator[](size_t index) const;

		/* IType Operators -------------------------------------------------------- */
		shared_itype		clone() const;
		shared_itype		negate() const;
		shared_itype		operator+(const shared_itype& rhs_ptr) const;
		shared_itype		operator-(const shared_itype& rhs_ptr) const;
		shared_itype		operator*(const shared_itype& rhs_ptr) const;
		shared_itype		operator/(const shared_itype& rhs_ptr) const;
		shared_itype		operator^(const shared_itype& rhs_ptr) const;
		shared_itype		operator%(const shared_itype& rhs_ptr) const;
		bool				operator==(const shared_itype& rhs_ptr) const;

		/* Arith Operators -------------------------------------------------------- */
		Matrix				operator-() const;
		Matrix				transpose() const;
		
		Matrix&				operator+=(const Matrix& rhs);
		Matrix				operator+(const Matrix& rhs) const;

		Matrix&				operator-=(const Matrix& rhs);
		Matrix				operator-(const Matrix& rhs) const;

		Matrix&				operator*=(const Matrix& rhs);
		Matrix				operator*(const Matrix& rhs) const;

		Matrix&				operator/=(const Matrix& rhs);			// undefined
		Matrix				operator/(const Matrix& rhs) const;		// undefined

		Matrix&				operator^=(const Matrix& rhs);			// undefined
		Matrix				operator^(const Matrix& rhs) const;		// undefined

		Matrix&				operator%=(const Matrix& rhs);			// undefined
		Matrix				operator%(const Matrix& rhs) const;		// undefined

		/* Rational Operators ----------------------------------------------------- */
		Matrix				operator+(const Rational& rhs) const;	// undefined
		Matrix				operator-(const Rational& rhs) const;	// undefined
		Matrix				operator*(const Rational& rhs) const;
		Matrix				operator/(const Rational& rhs) const;
		Matrix				operator^(const Rational& rhs) const;
		Matrix				operator%(const Rational& rhs) const;	// undefined
		bool				operator==(const Rational& rhs) const;	// undefined

		/* Complex Operators ------------------------------------------------------ */
		Matrix				operator+(const Complex& rhs) const;	// undefined
		Matrix				operator-(const Complex& rhs) const;	// undefined
		Matrix				operator*(const Complex& rhs) const;
		Matrix				operator/(const Complex& rhs) const;
		Matrix				operator^(const Complex& rhs) const;
		Matrix				operator%(const Complex& rhs) const;	// undefined
		bool				operator==(const Complex& rhs) const;	// undefined

		/* Function --------------------------------------------------------------- */
		Function			operator+(const Function& rhs) const;	// undefined
		Function			operator-(const Function& rhs) const;	// undefined
		Function			operator*(const Function& rhs) const;
		Function			operator/(const Function& rhs) const;
		Function			operator^(const Function& rhs) const;
		Function			operator%(const Function& rhs) const;	// undefined
		bool				operator==(const Function& rhs) const;	// undefined

		/* Getter ----------------------------------------------------------------- */
		size_t				getNbColumns() const;
		size_t				getNbRows() const;
		const matrix&		getMatrix() const;

		/* Tools ------------------------------------------------------------------ */
		bool				operator!() const;
		bool				isSameSize(const Matrix& rhs) const;
		bool				isSquare() const;

		/* Relational Operators --------------------------------------------------- */
		bool				operator==(const Matrix& y) const;
		bool				operator!=(const Matrix& y) const;

		class BadMatrixDimensions: public std::exception {
			public:
				const char* what() const throw() {
					return "Matrix has bad dimensions";
				}
		};

	private:
		size_t				_n;			// nb rows
		size_t				_p;			// nb columns
		matrix				_matrix;

		/* Utils ------------------------------------------------------------------ */
		shared_itype		_rational_operator(
								Matrix (Matrix::*f)(const Rational&) const,
								const std::shared_ptr<Rational>& r_ptr
							) const;
		shared_itype		_complex_operator(
								Matrix (Matrix::*f)(const Complex&) const,
								const std::shared_ptr<Complex>& c_ptr
							) const;
		shared_itype		_matrix_operator(
								Matrix (Matrix::*f)(const Matrix&) const,
								const std::shared_ptr<Matrix>& m_ptr
							) const;
		shared_itype		_function_operator(
								Function (Matrix::*f)(const Function&) const,
								const std::shared_ptr<Function>& f_ptr
							) const;

};

std::ostream&	operator<<(std::ostream& o, const Matrix& x);

#endif