/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:29:23 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 13:14:51 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include <iostream>
# include <cstddef>
# include <string>
# include <type_traits>
# include <vector>

# include "rational.hpp"

# define EPSILON 1e-10

namespace math {

class operation_undefined: public std::exception {
	public:
		const char* what() const throw() {
			return ("Operation undefined");
		}
};

/* -- PROTOTYPE ----------------------------------------------- */

template <typename T>
	T abs(const T x);

template <typename T, typename U>
	T pow(const T n, const U exp);

template <typename T, typename U>
	long double binomial_coefficient(const T n, const U p);

template <typename T>
	T factorial(const T n);

template <typename T>
	long double sqrt(const T x);

template <typename T, typename U>
	long long int quotient(const T a, const U b);

template <typename T, typename U>
	long double modulo(const T a, const U b);

bool isPrime(const long long int& n);

long long int biggestPrime(const long long int n);

long long int smallestPrime(const long long int& n);

/* -- DEFINITION ---------------------------------------------- */

// OPERATIONS ================================

/*   absolute
 **  | x |
 */
template <typename T>
	inline T abs(const T x) {
		return (x < T(0)) ? -x : x;
	}

/*   power
 **  n ^ exp
 */
template <typename T, typename U>
	inline T pow(const T n, const U exp) {
		if (exp == 0 || n == 1)
			return T(1);
		else if (n == 0)
			return T(0);
		else
			return T(n * pow(n, exp - U(1)));
	}

/**
 * Newton's method sqrt function
*/
template <typename T>
inline long double sqrt(const T val) {
	T	x = val / T(2), x_next;
	T	y, y_bis;

	if (val < T(0))
		throw math::operation_undefined();
	while (1) {
		y = pow(x, T(2)) - val;
		y_bis = T(2) * x;
		if (abs(y_bis) < EPSILON)
			break;
		x_next = x - (y / y_bis);
		if (abs(x_next - x) < EPSILON)
			return x_next;
		x = x_next;
	}
	throw math::operation_undefined();
}

// ARITHMETIC UTILS ==========================

/*   binomial coefficient
 *   / n \          n!
 *  |     |  =  ----------
 *   \ p /       p!(n - p)!
 */
template <typename T, typename U>
	inline long double binomial_coefficient(const T n, const U p) {
		const T denominator = factorial(p);

		T numerator = 1;
		for (T i = 0; i < p; ++i)
			numerator *= n - i;
		return numerator/denominator;
	}

/*   factorial
 **  n! = n * (n - 1) * ... * 2 * 1
 */
template <typename T>
	inline T factorial(const T n) {
		if (n < T(0))
			throw math::operation_undefined();
		if (n == T(1) || n == T(0))
			return T(1);
		return n * factorial(n - T(1));
	}


/*  euclidean division: quotient element [q]
 **	 a = q * b + r
 */
template <typename T, typename U>
	inline long long int quotient(const T a, const U b) {
		long long int	q = 0;

		while (a - (q + 1) * b >= 0)
			++q;
		return q;
	}

/*  euclidean division: modulo element [r]
 **	 a = q * b + r
 */
template <typename T, typename U>
	inline long double modulo(const T a, const U b) {
		if (a < 0 || b < 0)
			throw math::operation_undefined();
		const long long int	q = quotient(a, b);

		return a - (q * b);
	}


// ARITHM UTILS ==============================

inline bool isPrime(const long long int& n) {
	const int	limit = sqrt(n) + 1;
	int			i = 2;

	while (i < limit) {
		if (!modulo(n, i))
			return false;
		++i;
	}
	return true;
}

inline long long int biggestPrime(const long long int n) {
	long long int	limit;

	if (n < 0)
		return -1;
	else if (isPrime(n))
		return n;
	limit = (n / 2) + 1;
	while (limit > 2) {
		if (isPrime(limit) && !modulo(n, limit))
			return limit;
		--limit;
	}
	return limit;
}

inline long long int smallestPrime(const long long int& n) {
	long long int	limit;
	long long int	i;

	if (n < 0)
		return -1;
	limit = sqrt(n);
	i = 2;
	while (i < limit) {
		if (modulo(n, i) && isPrime(i))
			break;
		++i;
	}
	return i;
}

} // namespace math

#endif
