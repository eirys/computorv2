/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rational.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:42:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 18:56:03 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rational.hpp"

Rational::Rational(const std::string&& s):
	i(std::stold(s)) {}

Rational::~Rational() {}

Rational& Rational::operator=(const Rational& rhs) {
	if (this == &rhs)
		return *this;
	i = rhs.i;
	return *this;
}