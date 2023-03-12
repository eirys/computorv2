/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itype.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:52:20 by eli               #+#    #+#             */
/*   Updated: 2023/03/12 11:45:20 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itype.hpp"
#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include "function.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

IType::IType() {}

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
				try {
					const Function&	f_ref = dynamic_cast<const Function&>(x);
					o << f_ref;
				} catch (const std::bad_cast& exception4) {
					//TODO
					throw std::exception();
				}
			}
		}
	}
	return o;
}