/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:34:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:07:19 by eli              ###   ########.fr       */
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
		Rational(const Rational& x);
		virtual ~Rational();
		Rational&	operator=(const Rational& rhs);

		long double	getVal() const;

	private:
		long double	_val;
};

bool			operator==(const Rational& x, const Rational& y);

std::ostream&	operator<<(std::ostream& o, const Rational& x);

#endif