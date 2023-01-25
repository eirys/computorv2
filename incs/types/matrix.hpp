/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 13:48:22 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <vector>
# include <iomanip>
# include <sstream>
# include <ios>

# include "math.hpp"
# include "rational.hpp"

# define MIN_W_SIZE 2

class Matrix: public IType {
	public:
		typedef typename	IType::unique_itype			unique_itype;
		typedef typename	IType::shared_itype			shared_itype;
		typedef typename	IType::weak_itype			weak_itype;

		typedef				std::vector<Rational>		row;
		typedef typename	std::vector<row>			matrix;

		Matrix();
		virtual ~Matrix();
		
		Matrix(const Matrix& x);
		Matrix(const matrix&& x);

		Matrix(size_t n, const Rational&& lambda = Rational(0));
		Matrix(size_t n, size_t p);

		Matrix&				operator=(const Matrix& rhs);

		// Element access
		row&				operator[](size_t index);
		const row&			operator[](size_t index) const;

		// IType operators
		shared_itype		operator+(const shared_itype& rhs_ptr) const;
		shared_itype		operator-(const shared_itype& rhs_ptr) const;
		shared_itype		operator*(const shared_itype& rhs_ptr) const;
		shared_itype		operator/(const shared_itype& rhs_ptr) const;

		// Arith operators
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

		Matrix&				operator^=(const Rational& rhs);
		Matrix				operator^(const Rational& rhs) const;

		Matrix&				operator%=(const Rational& rhs);
		Matrix				operator%(const Rational& rhs) const;

		// Rational
		Matrix				operator+(const Rational& rhs) const;
		Matrix				operator-(const Rational& rhs) const;
		Matrix				operator*(const Rational& rhs) const;
		Matrix				operator/(const Rational& rhs) const;

		// Complex
		Matrix				operator+(const Complex& rhs) const;	// undefined
		Matrix				operator-(const Complex& rhs) const;	// undefined
		Matrix				operator*(const Complex& rhs) const;
		Matrix				operator/(const Complex& rhs) const;

		// Getter
		size_t				getNbColumns() const;
		size_t				getNbRows() const;
		const matrix&		getMatrix() const;

		// Tools
		bool				operator!() const;
		bool				isSameSize(const Matrix& rhs) const;
		bool				isSquare() const;
		size_t				getMaxLength() const;

	private:
		size_t				_n;			// nb rows
		size_t				_p;			// nb columns
		matrix				_matrix;
		
		shared_itype		_rational_operator(
								Matrix (Matrix::*f)(const Rational&) const,
								const std::shared_ptr<Rational>& r_ptr
								) const;
		shared_itype		_complex_operator(
								Matrix (Matrix::*f)(const Complex&) const,
								const std::shared_ptr<Complex>& r_ptr
								) const;
		shared_itype		_matrix_operator(
								Matrix (Matrix::*f)(const Matrix&) const,
								const std::shared_ptr<Matrix>& r_ptr
								) const;
};

bool			operator==(const Matrix& x, const Matrix& y);
bool			operator!=(const Matrix& x, const Matrix& y);

std::ostream&	operator<<(std::ostream& o, const Matrix& x);

#endif