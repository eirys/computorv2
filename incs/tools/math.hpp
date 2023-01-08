/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:29:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/08 20:43:30 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

# include <iostream>
# include <cstddef>
# include <string>
# include <type_traits>
# include "rational.hpp"

# define SQRT_DEPTH 15
# define SQRT_10 3.16227766017

namespace math {

	/* -- PROTOTYPE ----------------------------------------------- */

	template <typename T>
		T abs(const T& x);

	template <typename T, typename U>
		long double binomial_coefficient(const T& n, const U& p);

	template <typename T>
		T factorial(const T& n);

	template <typename T, typename U>
		long double pow(const T& n, const U& exp);

	template <typename T>
		long double sqrt(const T& x);
	Rational sqrt(const Rational& val);

	template <typename T, typename U>
		long long int quotient(const T& a, const U& b);

	template <typename T, typename U>
		long double remainder(const T& a, const U& b);

	bool isPrime(const long long int& n);

	long long int biggestPrime(const long long int n);

	long long int smallestPrime(const long long int& n);

	/* -- DEFINITION ---------------------------------------------- */

	// OPERATIONS ================================

	/*   absolute 
	 **  | x |
	 */
	template <typename T>
		inline T abs(const T& x) {
			return (x < 0) ? -x : x;
		}

	/*   power
	 **  n ^ exp
	 */
	template <typename T, typename U>
		inline long double pow(const T& n, const U& exp) {
			if (exp == 0 || n == 1)
				return 1;
			else if (n == 0)
				return 0;
			else
				return n * pow(n, exp + (exp < 0 ? 1 : -1));
		}

	template <typename U>
		inline Rational pow(Rational n, const U& exp) {
			if (exp == 0 || n.getVal() == 1)
				return Rational(1);
			else if (n.getVal() == 0)
				return Rational(0);
			else
				return n * Rational(pow(n, exp - 1));
		}

	/*   square root
	 **   __
	 **  √ x    cf. Taylor Series:
	 **            (1 + x) ^ .5 = sum(binomial_coef(.5, k) * x ^ k) for k = [0, inf[
	 */
	template <typename T>
		inline long double sqrt(const T& val) {
			if (val == 0 || val == 1)
				return val;

			const size_t		exponent = std::to_string(static_cast<long long>(val)).size();
			const long double	x = (val / pow(10, exponent)) - 1;
			long double			sum = 0;

			for (int i = 0; i < SQRT_DEPTH; ++i)
				sum += binomial_coefficient(.5, i) * pow(x, i);
			if (exponent % 2 == 0)
				return sum * pow(10, exponent * .5);
			else
				return sum * SQRT_10 * pow(10, (exponent - 1) * .5);
		}

	inline Rational sqrt(const Rational& val) {
		if (val == 0 || val == 1)
			return val;

		const size_t		exponent = std::to_string(static_cast<long long>(val.getVal())).size();
		const long double	x = (val.getVal() / pow(10, exponent)) - 1;
		long double			sum = 0;

		for (int i = 0; i < SQRT_DEPTH; ++i)
			sum += binomial_coefficient(.5, i) * pow(x, i);
		if (exponent % 2 == 0)
			return Rational(sum * pow(10, exponent * .5));
		else
			return Rational(sum * SQRT_10 * pow(10, (exponent - 1) * .5));
	}

	// ARITHMETIC UTILS ==========================

	/*   binomial coefficient
	 **  / n \          n!
	 ** |     |  =  ----------
	 **  \ p /       p!(n - p)!
	 */
	template <typename T, typename U>
		inline long double binomial_coefficient(const T& n, const U& p) {
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
		inline T factorial(const T& n) {
			if (n == 1 || n == 0)
				return 1;
			return n * factorial(n - 1);
		}


	/*  euclidean division: quotient element [q]
	 **	 a = q * b + r
	 */
	template <typename T, typename U>
		inline long long int quotient(const T& a, const U& b) {
			long long int	q = 0;

			while (a - (q + 1) * b >= 0)
				++q;
			return q;
		}

	/*  euclidean division: remainder element [r]
	 **	 a = q * b + r
	 */
	template <typename T, typename U>
		inline long double remainder(const T& a, const U& b) {
			const long long int	q = quotient(a, b);

			return a - (q * b);
		}


	// ARITHM UTILS ==============================

	inline bool isPrime(const long long int& n) {
		const int	limit = sqrt(n) + 1;
		int			i = 2;
		
		while (i < limit) {
			if (!remainder(n, i))
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
			if (isPrime(limit) && !remainder(n, limit))
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
			if (remainder(n, i) && isPrime(i))
				break;
			++i;
		}
		return i;
	}
}

#endif
