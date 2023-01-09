/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:04:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/10 00:16:38 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"

Matrix::Matrix() {}

Matrix::~Matrix() {}

Matrix::Matrix(const Matrix& x):
	_n(x.getNbColumns()),
	_p(x.getNbLines()),
	_matrix(x.getMatrix()) {}

/*
**	Usage:
**	Matrix m = Matrix::matrix { {...}, ... };
*/
Matrix::Matrix(const Matrix::matrix&& x) {
	if (x.empty()) {
		_n = 0;
		_p = 0;
	} else {
		_p = x[0].size();
		for (Matrix::matrix::const_iterator it = x.begin();
		it != x.end();
		++it) {
			if (it->size() != _p) {
				throw Matrix::inconsistent_size();
			}
		}
		_matrix = x;
		_n = x.size();
		_p = x[0].size();
	}
}

/*
**	Identity matrix / Scalar matrix
*/
Matrix::Matrix(size_t n, const Rational&& lambda):
	_n(n),
	_p(n),
	_matrix(n, line(n)) {
		for (size_t i = 0; i < getNbColumns(); ++i) {
			_matrix[i][i] = lambda;
		}
	}

Matrix::Matrix(size_t n, size_t p):
	_n(n),
	_p(p),
	_matrix(n, line(p)) {}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (*this == rhs)
		return *this;
	_n = rhs.getNbColumns();
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

Matrix Matrix::transpose() const {
	Matrix	tmp(this->getNbLines(), this->getNbColumns());

	for (size_t i = 0; i < getNbColumns(); ++i) {
		for (size_t j = 0; j < getNbLines(); ++j) {
			tmp[j][i] = _matrix[i][j];
		}
	}
	return tmp;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if (!isSameSize(rhs))
		throw Matrix::not_same_size();
	for (size_t i = 0; i < getNbColumns(); ++i) {
		for (size_t j = 0; j < getNbLines(); ++j) {
			_matrix[i][j] += rhs.getMatrix()[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix	tmp(*this);

	tmp.operator+=(rhs);
	return tmp;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	if (!isSameSize(rhs))
		throw Matrix::not_same_size();
	for (size_t i = 0; i < getNbColumns(); ++i) {
		for (size_t j = 0; j < getNbLines(); ++j) {
			_matrix[i][j] -= rhs.getMatrix()[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix	tmp(*this);

	tmp.operator-=(rhs);
	return tmp;
}

Matrix Matrix::operator-() const {
	Matrix		tmp(*this);
	Rational	negate(-1);
	
	tmp.operator*=(negate);
	return tmp;
}

//TODO
Matrix& Matrix::operator*=(const Matrix rhs) {
	(void)rhs;
	if (false)
		throw Matrix::not_compatible();
	return *this;
}

Matrix& Matrix::operator*=(const Rational rhs) {
	for (size_t i = 0; i < getNbColumns(); ++i) {
		for (size_t j = 0; j < getNbLines(); ++j) {
			_matrix[i][j] *= rhs;
		}
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Matrix Matrix::operator*(const Rational& rhs) const {
	Matrix	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

/* Relational operators *****************************/

size_t Matrix::getNbColumns() const {
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
	for (size_t j = 0; j < getNbColumns(); ++j) {
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
	for (size_t j = 0; j < getNbColumns(); ++j) {
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
	if (getNbLines() == rhs.getNbLines() && getNbColumns() == rhs.getNbColumns())
		return true;
	return false;
} 

size_t Matrix::getMaxLength() const {
	size_t	biggest = MIN_W_SIZE;
	
	for (Matrix::matrix::const_iterator it = getMatrix().begin();
	it != getMatrix().end();
	++it) {
		for (Matrix::line::const_iterator ite = it->begin();
		ite != it->end();
		++ite) {
			size_t tmp = utils::getWidth(*ite);
			if (tmp > biggest)
				biggest = tmp;
		}
	}
	return biggest;
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

	size_t field_w = x.getMaxLength() + 1;
	for (Matrix::matrix::const_iterator it = x.getMatrix().begin();
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
	o << os.str();
	return o;
}