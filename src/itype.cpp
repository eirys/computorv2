/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itype.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:52:20 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 12:10:45 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itype.hpp"
#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

IType::~IType() {}

/* -------------------------------------------------------------------------- */

std::ostream&	operator<<(std::ostream& o, const IType& x) {
	try {
		const Rational&	r_ref = dynamic_cast<const Rational&>(x);
		o << r_ref;
	} catch (const std::bad_cast& exception1) {
		try {
			const Complex&	c_ref = dynamic_cast<const Complex&>(x);
			o << c_ref;
		} catch (const std::bad_cast& exception2) {
			try {
				const Matrix&	m_ref = dynamic_cast<const Matrix&>(x);
				o << m_ref;
			} catch (const std::bad_cast& exception3) {
				throw std::exception();
			}
		}
	}
	return o;
}