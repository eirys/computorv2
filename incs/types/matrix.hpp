/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 14:19:16 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <vector>
# include <iomanip>
# include <sstream>
# include <ios>

# include "rational.hpp"

class Matrix {
	public:
		typedef				std::vector<Rational>			line;
		typedef typename	std::vector<line>				matrix;
		typedef typename	matrix::iterator				iterator;
		typedef typename	matrix::const_iterator			const_iterator;

		Matrix();
		virtual ~Matrix();
		
		Matrix(const Matrix& x);
		explicit Matrix(size_t n);
		explicit Matrix(size_t n, size_t p);

		Matrix&				operator=(const Matrix& rhs);

		line&				operator[](size_t index);
		const line&			operator[](size_t index) const;

		Matrix&				transpose();
		
		Matrix&				operator+=(const Matrix& rhs);
		Matrix&				operator-=(const Matrix& rhs);
		Matrix&				operator*=(const Matrix& rhs);

		size_t				getNbRows() const;
		size_t				getNbLines() const;
		const matrix&		getMatrix() const;

		const Rational&		getMin() const;
		const Rational&		getMax() const;

		bool				isSameSize(const Matrix& rhs) const;

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

	private:
		size_t				_n;
		size_t				_p;
		matrix				_matrix;
};

bool			operator==(const Matrix& x, const Matrix& y);
bool			operator!=(const Matrix& x, const Matrix& y);

std::ostream&	operator<<(std::ostream& o, const Matrix& x);

#endif