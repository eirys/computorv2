/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 20:17:41 by eli              ###   ########.fr       */
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

class Matrix {
	public:
		typedef				std::vector<Rational>			row;
		typedef typename	std::vector<row>				matrix;

		Matrix();
		virtual ~Matrix();
		
		Matrix(const Matrix& x);
		Matrix(const matrix&& x);
		Matrix(size_t n, const Rational&& lambda = Rational(0));
		Matrix(size_t n, size_t p);

		Matrix&				operator=(const Matrix& rhs);

		// Arith operators
		Matrix				transpose() const;
		
		Matrix&				operator+=(const Matrix& rhs);
		Matrix				operator+(const Matrix& rhs) const;

		Matrix&				operator-=(const Matrix& rhs);
		Matrix				operator-(const Matrix& rhs) const;
		Matrix				operator-() const;

		Matrix&				operator*=(const Matrix& rhs);
		Matrix				operator*(const Matrix& rhs) const;
		
		// Rational
		Matrix&				operator*=(const Rational& rhs);
		Matrix				operator*(const Rational& rhs) const;

		Matrix&				operator/=(const Rational& rhs);
		Matrix				operator/(const Rational& rhs) const;

		Matrix&				operator^=(const Rational& rhs);
		Matrix				operator^(const Rational& rhs) const;

		Matrix&				operator%=(const Rational& rhs);
		Matrix				operator%(const Rational& rhs) const;

		// Getter
		row&				operator[](size_t index);
		const row&			operator[](size_t index) const;

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
};

bool			operator==(const Matrix& x, const Matrix& y);
bool			operator!=(const Matrix& x, const Matrix& y);

std::ostream&	operator<<(std::ostream& o, const Matrix& x);

#endif