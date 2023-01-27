/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:04:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/25 15:54:34 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"
#include "complex.hpp"

Matrix::Matrix() {}

Matrix::~Matrix() {}

Matrix::Matrix(const Matrix& x):
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

Matrix::Matrix(const IType& x) {
	try {
		const Matrix&	tmp = dynamic_cast<const Matrix&>(x);
		*this = tmp;
	} catch (const std::bad_cast& e) {
		throw math::operation_undefined();
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

/* Element access ----------------------------------------------------------- */

Matrix::row&	Matrix::operator[](size_t index) {
	if (index >= _n)
		throw std::out_of_range("out_of_range: Matrix::operator[]");
	return _matrix[index];
}

const Matrix::row&	Matrix::operator[](size_t index) const {
	if (index >= _n)
		throw std::out_of_range("out_of_range: Matrix::operator[]");
	return _matrix[index];
}

/* IType operators ---------------------------------------------------------- */

Matrix::shared_itype		Matrix::operator+(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Matrix::operator+, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Matrix::operator+, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Matrix::operator+, m_ptr);
	return nullptr;
}

Matrix::shared_itype		Matrix::operator-(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Matrix::operator-, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Matrix::operator-, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Matrix::operator-, m_ptr);
	return nullptr;
}

Matrix::shared_itype		Matrix::operator*(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Matrix::operator*, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Matrix::operator*, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Matrix::operator*, m_ptr);
	return nullptr;
}

Matrix::shared_itype		Matrix::operator/(const shared_itype& rhs_ptr) const {
	std::shared_ptr<Rational>	r_ptr = std::dynamic_pointer_cast<Rational>(rhs_ptr);
	if (r_ptr.get())
		return _rational_operator(&Matrix::operator/, r_ptr);
	std::shared_ptr<Complex>	c_ptr = std::dynamic_pointer_cast<Complex>(rhs_ptr);
	if (c_ptr.get())
		return _complex_operator(&Matrix::operator/, c_ptr);
	std::shared_ptr<Matrix>		m_ptr = std::dynamic_pointer_cast<Matrix>(rhs_ptr);
	if (m_ptr.get())
		return _matrix_operator(&Matrix::operator/, m_ptr);
	return nullptr;
}

Matrix::shared_itype	Matrix::_rational_operator(
	Matrix (Matrix::*f)(const Rational&) const,
	const std::shared_ptr<Rational>& r_ptr
	) const {
		return shared_itype(new Matrix((this->*f)(*r_ptr)));
	}

Matrix::shared_itype	Matrix::_complex_operator(
	Matrix (Matrix::*f)(const Complex&) const,
	const std::shared_ptr<Complex>& r_ptr
	) const {
		return shared_itype(new Matrix((this->*f)(*r_ptr)));

	}

Matrix::shared_itype	Matrix::_matrix_operator(
	Matrix (Matrix::*f)(const Matrix&) const,
	const std::shared_ptr<Matrix>& r_ptr
	) const {
		return shared_itype(new Matrix((this->*f)(*r_ptr)));

	}

/* Arith operators ---------------------------------------------------------- */

Matrix Matrix::operator-() const {
	return operator*(Rational(-1));
}

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

Matrix&	Matrix::operator/=(const Matrix& rhs) {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix	Matrix::operator/(const Matrix& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
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

/* -------------------------------------------------------------------------- */

Matrix	Matrix::operator+(const Rational& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix	Matrix::operator-(const Rational& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix Matrix::operator*(const Rational& rhs) const {
	const Rational	rhs_copy(rhs);
	Matrix			tmp(getNbRows(), getNbColumns());

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			tmp[i][j] = _matrix[i][j] * rhs_copy;
		}
	}
	return tmp;
}

Matrix Matrix::operator/(const Rational& rhs) const {
	const Rational	rhs_copy(rhs);
	Matrix			tmp(getNbRows(), getNbColumns());

	for (size_t i = 0; i < getNbRows(); ++i) {
		for (size_t j = 0; j < getNbColumns(); ++j) {
			tmp[i][j] = _matrix[i][j] / rhs_copy;
		}
	}
	return tmp;
}

/* -------------------------------------------------------------------------- */

Matrix	Matrix::operator+(const Complex& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix	Matrix::operator-(const Complex& rhs) const {
	(void)rhs;
	throw math::operation_undefined();
}

Matrix	Matrix::operator*(const Complex& rhs) const {
	if (rhs.isReal()) {
		Rational	tmp(rhs.getReal());

		return operator*(tmp);
	}
	throw math::operation_undefined();
}

Matrix	Matrix::operator/(const Complex& rhs) const {
	if (rhs.isReal()) {
		Rational	tmp(rhs.getReal());

		return operator/(tmp);
	}
	throw math::operation_undefined();
}

/* Getters ------------------------------------------------------------------ */

size_t Matrix::getNbRows() const {
	return _n;
}

size_t Matrix::getNbColumns() const {
	return _p;
}

const Matrix::matrix& Matrix::getMatrix() const {
	return _matrix;
}

/* Tools -------------------------------------------------------------------- */

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

/* Useless lol 
void	Matrix::forEach(void (*f)(const Rational&)) const {
	for (Matrix::matrix::const_iterator it = getMatrix().begin();
	it != getMatrix().end();
	++it) {
		for (Matrix::row::const_iterator ite = it->begin();
		ite != it->end();
		++ite) {
			f(*ite);
		}
	}
}

void	Matrix::forEach(void (*f)(const Rational&)) {
	for (Matrix::matrix::iterator it = getMatrix().begin();
	it != getMatrix().end();
	++it) {
		for (Matrix::row::iterator ite = it->begin();
		ite != it->end();
		++ite) {
			f(*ite);
		}
	}
} */

/* Relational operators ----------------------------------------------------- */

bool operator==(const Matrix& x, const Matrix& y) {
	if (x.isSameSize(y))
		if (x.getMatrix() == y.getMatrix())
			return true;
	return false;
}

bool operator!=(const Matrix& x, const Matrix& y) {
	return !operator==(x,y);
}

/* I/O stream operator ------------------------------------------------------ */

/**
 * TODO:
 * 	get largest element for each COLUMN
 * 	save length value in array
 * 	
*/
std::ostream& operator<<(std::ostream& o, const Matrix& x) {
	std::ostringstream	os;

	os << std::setprecision(3);

	size_t field_w = x.getMaxLength() + 1;
	for (Matrix::matrix::const_iterator it = x.getMatrix().begin();
	it != x.getMatrix().end();
	++it) {
		os << '[';
		for (Matrix::row::const_iterator ite = it->begin();
		ite != it->end();
		++ite) {
			os << std::setw(field_w) << *ite;
			if (ite + 1 == it->end() + 1)
				os << ' ';
			// if (ite == it->begin()) {
			// 	os << std::setw(field_w + 1) << *ite << " , ";
			// } else if (ite + 1 != it->end()) {
			// 	os << std::setw(field_w) << *ite << " , ";
			// } else {
			// 	os << std::setw(field_w) << *ite;
			// 	os << ' ';
			// }
		}
		os << ']';
		if (it + 1 != x.getMatrix().end())
			os << NL;
	}
	o << os.str();
	return o;
}