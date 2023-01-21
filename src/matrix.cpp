/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:04:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 12:50:54 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"

Matrix::Matrix() {}

Matrix::~Matrix() {}

Matrix::Matrix(const Matrix& x):
	// TreeNode(_left, _right),
	_n(x.getNbRows()),
	_p(x.getNbColumns()),
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
				throw math::operation_undefined();
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
	_matrix(n, row(n)) {
		for (size_t i = 0; i < getNbColumns(); ++i) {
			_matrix[i][i] = lambda;
		}
	}

Matrix::Matrix(size_t n, size_t p):
	_n(n),
	_p(p),
	_matrix(n, row(p)) {}

Matrix& Matrix::operator=(const Matrix& rhs) {
	if (*this == rhs)
		return *this;
	_n = rhs.getNbRows();
	_p = rhs.getNbColumns();
	_matrix = Matrix::matrix(rhs.getMatrix());
	return *this;
}

/* Element access ***********************************/

Matrix::row&	Matrix::operator[](size_t index) {
	if (index > _n)
		throw std::out_of_range("Matrix::operator[]");
	return _matrix[index];
}

const Matrix::row&	Matrix::operator[](size_t index) const {
	if (index > _n)
		throw std::out_of_range("Matrix::operator[]");
	return _matrix[index];
}

/* Arith operators **********************************/

Matrix Matrix::transpose() const {
	Matrix	tmp(this->getNbColumns(), this->getNbRows());

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			tmp[j][i] = _matrix[i][j];
		}
	}
	return tmp;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if (!isSameSize(rhs))
		throw math::operation_undefined();

	const Matrix	rhs_copy(rhs);

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			_matrix[i][j] += rhs_copy[i][j];
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
		throw math::operation_undefined();

	const Matrix	rhs_copy(rhs);

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			_matrix[i][j] -= rhs_copy[i][j];
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
	
	tmp.operator*=(Rational(-1));
	return tmp;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if (getNbColumns() != rhs.getNbRows())
		throw math::operation_undefined();

	Matrix			new_matrix(getNbRows(), rhs.getNbColumns());
	const Matrix	rhs_copy(rhs);

	for (size_t i = 0; i < new_matrix.getNbRows(); ++i) {
		for (size_t j = 0; j < new_matrix.getNbColumns(); ++j) {
			for (size_t k = 0; k < getNbColumns(); ++k) {
				new_matrix[i][j] += (*this)[i][k] * rhs_copy[k][j];
			}
		}
	}
	*this = new_matrix;
	return *this;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Matrix& Matrix::operator^=(const Rational& rhs) {
	if (!isSquare() || !rhs.isInteger() || rhs < Rational(0))
		throw math::operation_undefined();
	if (rhs == Rational(1) || !*this)
		return *this;
	else if (rhs == Rational(0)) {
		*this = Matrix(getNbColumns(), Rational(1));
	} else {
		const Rational	rhs_copy(rhs);
		for (Rational i = Rational(0); i < rhs_copy; ++i) {
			operator*=(*this);
		}
	}
	return *this;
}

Matrix Matrix::operator^(const Rational& rhs) const {
	Matrix	tmp(*this);

	tmp.operator^=(rhs);
	return tmp;
}

Matrix& Matrix::operator%=(const Rational& rhs) {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Matrix::operator%(const Rational& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

/* Getters ******************************************/

Matrix& Matrix::operator*=(const Rational& rhs) {
	const Rational	rhs_copy(rhs);

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			_matrix[i][j] *= rhs_copy;
		}
	}
	return *this;
}

Matrix Matrix::operator*(const Rational& rhs) const {
	Matrix	tmp(*this);

	tmp.operator*=(rhs);
	return tmp;
}

Matrix& Matrix::operator/=(const Rational& rhs) {
	const Rational rhs_copy(rhs);

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			_matrix[i][j] /= rhs_copy;
		}
	}
	return *this;
}

Matrix Matrix::operator/(const Rational& rhs) const {
	Matrix	tmp(*this);

	tmp.operator/=(rhs);
	return tmp;
}

/* Getters ******************************************/

size_t Matrix::getNbRows() const {
	return _n;
}

size_t Matrix::getNbColumns() const {
	return _p;
}

const Matrix::matrix& Matrix::getMatrix() const {
	return _matrix;
}

/* Tools ********************************************/

bool Matrix::operator!() const {
	for (size_t i = 0; i < getNbColumns(); ++i) {
		for (size_t j = 0; j < getNbRows(); ++j) {
			if (getMatrix()[i][j].getVal())
				return false;
		}
	}
	return true;
}

bool Matrix::isSameSize(const Matrix& rhs) const {
	if (getNbRows() == rhs.getNbRows() && getNbColumns() == rhs.getNbColumns())
		return true;
	return false;
}

bool Matrix::isSquare() const {
	return getNbColumns() == getNbRows();
}

size_t Matrix::getMaxLength() const {
	size_t	biggest = MIN_W_SIZE;
	
	for (Matrix::matrix::const_iterator it = getMatrix().begin();
	it != getMatrix().end();
	++it) {
		for (Matrix::row::const_iterator ite = it->begin();
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

/* I/O stream operator ******************************/

std::ostream& operator<<(std::ostream& o, const Matrix& x) {
	std::ostringstream	os;

	os << NL << std::setprecision(3);

	size_t field_w = x.getMaxLength() + 1;
	for (Matrix::matrix::const_iterator it = x.getMatrix().begin();
	it != x.getMatrix().end();
	++it) {
		os << '|';
		for (Matrix::row::const_iterator ite = it->begin();
		ite != it->end();
		++ite) {
			os << std::setw(field_w) << *ite;
		}
		os << '|' << NL;
	}
	o << os.str();
	return o;
}