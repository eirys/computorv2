/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:56:06 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RATIONAL_HPP
# define RATIONAL_HPP

# include <string>
# include "utils.hpp"

class Rational {
	public:
		Rational();
		explicit Rational(long double x);
		Rational(const std::string&& buf);
		virtual ~Rational();
		Rational&		operator=(long double rhs);

		long double		getVal() const;
		operator long double() const;
		
	private:
		long double	_val;
};

bool			operator==(const Rational& x, const long double& y);
bool			operator<(const Rational& x, const long double& y);
bool			operator!=(const Rational& x, const long double& y);
bool			operator<=(const Rational& x, const long double& y);
bool			operator>(const Rational& x, const long double& y);
bool			operator>=(const Rational& x, const long double& y);

#endif