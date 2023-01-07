/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/07 23:25:32 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>
# include "utils.hpp"

class Rational {
	public:
		Rational();
		virtual ~Rational();

		Rational(const Rational& x);
		Rational(long double x);
		explicit Rational(const std::string&& buf);
		
		Rational&		operator=(long double rhs);
		Rational&		operator=(const Rational& rhs);

		// Arith. operators
		Rational&		operator+=(const Rational& rhs);
		Rational&		operator++();
		Rational		operator++(int);
		Rational		operator+(const Rational& rhs);

		Rational&		operator-=(const Rational& rhs);
		Rational&		operator--();
		Rational		operator--(int);
		Rational		operator-(const Rational& rhs);

		Rational&		operator*=(const Rational& rhs);
		Rational		operator*(const Rational& rhs);
		
		Rational&		operator/=(const Rational& rhs);
		Rational		operator/(const Rational& rhs);

		// Getter
		long double		getVal() const;

	private:
		long double		_val;
};

bool			operator==(const Rational& x, const Rational& y);
bool			operator<(const Rational& x, const Rational& y);
bool			operator!=(const Rational& x, const Rational& y);
bool			operator<=(const Rational& x, const Rational& y);
bool			operator>(const Rational& x, const Rational& y);
bool			operator>=(const Rational& x, const Rational& y);

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif