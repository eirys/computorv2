/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 22:28:01 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <vector>
# include <iomanip>
# include <sstream>
# include <ios>

# include "rational.hpp"

# define MIN_W_SIZE 2

class Matrix {
	public:
		typedef				std::vector<Rational>			line;
		typedef typename	std::vector<line>				matrix;

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
		Matrix&				operator*=(const Rational& rhs);
		Matrix				operator*(const Matrix& rhs) const;
		Matrix				operator*(const Rational& rhs) const;

		// Getter
		line&				operator[](size_t index);
		const line&			operator[](size_t index) const;

		size_t				getNbColumns() const;
		size_t				getNbLines() const;
		const matrix&		getMatrix() const;

		// Tools
		const Rational&		getMin() const;
		const Rational&		getMax() const;

		bool				isSameSize(const Matrix& rhs) const;
		size_t				getMaxLength() const;

		// Exception
		class not_same_size: public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Matrix not the same size");
				}
		};

		class not_compatible: public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Matrix not compatible");
				}
		};

		class inconsistent_size: public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Inconsistent size in columns/lines");
				}
		};

	private:
		size_t				_n;			// columns
		size_t				_p;			// lines
		matrix				_matrix;

};

bool			operator==(const Matrix& x, const Matrix& y);
bool			operator!=(const Matrix& x, const Matrix& y);

std::ostream&	operator<<(std::ostream& o, const Matrix& x);

#endif