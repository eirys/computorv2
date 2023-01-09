/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:04:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 14:37:04 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"

Matrix::Matrix() {}

Matrix::~Matrix() {}

Matrix::Matrix(const Matrix& x):
	_n(x.getNbRows()),
	_p(x.getNbLines()),
	_matrix(x.getMatrix()) {}

/*
**	Identity matrix
*/
Matrix::Matrix(size_t n):
	_n(n),
	_p(n),
	_matrix(n, line(n)) {
		for (size_t i = 0; i < getNbRows(); ++i) {
			_matrix[i][i] = 1;
		}
	}

Matrix::Matrix(size_t n, size_t p):
	_n(n),
	_p(p),
	_matrix(n, line(p)) {}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (*this == rhs)
		return *this;
	_n = rhs.getNbRows();
	_p = rhs.getNbLines();
	_matrix = Matrix::matrix(rhs.getMatrix());
	return *this;
}

/* Relational operators *****************************/

Matrix::line&	Matrix::operator[](size_t index) {
	if (index > _n)
		throw std::out_of_range("Matrix::operator[]");
	return _matrix[index];
}

const Matrix::line&	Matrix::operator[](size_t index) const {
	if (index > _n)
		throw std::out_of_range("Matrix::operator[]");
	return _matrix[index];
}

/* Relational operators *****************************/

Matrix& Matrix::transpose() {
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if (!isSameSize(rhs))
		throw Matrix::not_same_size();
	for (size_t i = 0; i < _n; ++i) {
		for (size_t j = 0; j < _p; ++j) {
			_matrix[i][j] += rhs.getMatrix()[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	if (!isSameSize(rhs))
		throw Matrix::not_same_size();
	for (size_t i = 0; i < _n; ++i) {
		for (size_t j = 0; j < _p; ++j) {
			_matrix[i][j] -= rhs.getMatrix()[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	(void)rhs;
	return *this;
}

/* Relational operators *****************************/

size_t Matrix::getNbRows() const {
	return _n;
}

size_t Matrix::getNbLines() const {
	return _p;
}

const Matrix::matrix& Matrix::getMatrix() const {
	return _matrix;
}

const Rational& Matrix::getMax() const {
	size_t max_n = 0;
	size_t max_p = 0;
	for (size_t j = 0; j < getNbRows(); ++j) {
		for (size_t i = 0; i < getNbLines(); ++i) {
			if (_matrix[j][i] > _matrix[max_n][max_p]) {
				max_n = j;
				max_p = i;
			}
		}
	}
	return getMatrix()[max_n][max_p];
}

const Rational& Matrix::getMin() const {
	size_t min_n = 0;
	size_t min_p = 0;
	for (size_t j = 0; j < getNbRows(); ++j) {
		for (size_t i = 0; i < getNbLines(); ++i) {
			if (_matrix[j][i] < _matrix[min_n][min_p]) {
				min_n = j;
				min_p = i;
			}
		}
	}
	return getMatrix()[min_n][min_p];
}

/* Relational operators *****************************/

bool Matrix::isSameSize(const Matrix& rhs) const {
	if (getNbLines() == rhs.getNbLines() && getNbRows() == rhs.getNbRows())
		return true;
	return false;
} 

/* Relational operators *****************************/

bool operator==(const Matrix& x, const Matrix& y) {
	if (x.isSameSize(y))
		if (x.getMatrix() == y.getMatrix())
			return true;
	return false;
}

bool operator!=(const Matrix& x, const Matrix& y) {
	return !operator==(x,y);
}

/* Relational operators *****************************/

std::ostream& operator<<(std::ostream& o, const Matrix& x) {
	std::ostringstream	os;
	os << NL << std::setprecision(3);
	size_t field_w = utils::getMinWidth(x.getMax()) + 1;
	for (Matrix::const_iterator it = x.getMatrix().begin();
	it != x.getMatrix().end();
	++it) {
		os << '|';
		for (Matrix::line::const_iterator ite = it->begin();
		ite != it->end();
		++ite) {
			os << std::setw(field_w) << *ite;
		}
		os << '|' << NL;
	}
	// os.precision(og_size);
	o << os.str();
	return o;
}