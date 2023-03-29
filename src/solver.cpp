/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:30:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 13:24:11 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.hpp"
#include "complex.hpp"
#include "math.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Solver::Solver(const Indeterminates& expression):
	_expression(expression) {}

Solver::~Solver() {}

/* Main Function ------------------------------------------------------------ */

void	Solver::solve() const {
	void	(Solver::*solve_function)(const std::string&) const;

	if (_expression.getNbIndeterminates() > 1)
		throw TooManyIndeterminates();
	switch (_expression.getMaxExponent()) {
		case 0:
			return _simpleEquality();
		case 1:
			std::cout << "Solving degree 1 equation" << NL;
			solve_function = &Solver::_rootOne;
			break;
		case 2:
			std::cout << "Solving degree 2 equation" << NL;
			solve_function = &Solver::_rootSquare;
			break;
		default:
			throw ExponentTooHigh();
	}
	const std::string	main_variable_name = _expression.getMainIndeterminate();
	DEBUG("main indet: " << main_variable_name);
	(this->*solve_function)(main_variable_name);
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

void	Solver::_simpleEquality() const {
	std::cout << (_expression.getMap().empty() ? "True" : "False") << NL;
}

/**
 * FORMAT:
 *	bx^1 + cx^0 = 0
*/
void	Solver::_rootOne(const std::string& var) const {
	const Rational	b = _expression.getFactorFrom(var, Indeterminates::unit);
	const Rational	c = _expression.getFactorFrom(var, Indeterminates::null);

	const Rational	result = -c / b;

	std::cout << "Solution: " << var << " = " << result << NL;
}

/**
 * FORMAT:
 * 	ax^2 + bx^1 + cx^0 = 0
*/
void	Solver::_rootSquare(const std::string& var) const {
	using std::cout;
	const Rational	a = _expression.getFactorFrom(var, Indeterminates::two);
	const Rational	b = _expression.getFactorFrom(var, Indeterminates::unit);
	const Rational	c = _expression.getFactorFrom(var, Indeterminates::null);

	const Rational	discriminant = (b ^ Indeterminates::two) - (Rational(4) * a * c);
	if (discriminant > 0) {
		// x1, x2 in R
		const Rational	sqrt_delta = math::sqrt(discriminant.getVal());
		cout	<< "Solutions (Δ > 0): " << NL
				<< var << "\t= (-" << b << " - √" << discriminant
				<< ") / 2 * " << a << NL
				<< "\t= " << ((-b - sqrt_delta) / (a * Rational(2))) << NL
				<< " OR" << NL
				<< var << "\t= (-" << b << " + √" << discriminant
				<< ") / 2 * " << a << NL
				<< "\t= " << ((-b + sqrt_delta) / (a * Rational(2))) << NL;
	} else if (discriminant < 0) {
		// x1, x2 in C
		const Rational	sqrt_delta = math::sqrt(math::abs(discriminant.getVal()));
		const Rational	real = - b / (a * Rational(2));
		const Rational	im = sqrt_delta / (a * Rational(2));
		cout	<< "Solutions (Δ < 0): " << NL
				<< var << "\t= (-" << b << " - √|" << discriminant
				<< "|) / 2 * " << a << NL
				<< "\t= " << Complex(real, -im) << NL
				<< " OR" << NL
				<< var << "\t= (-" << b << " + √|" << discriminant
				<< "|) / 2 * " << a << NL
				<< "\t= " << Complex(real, im) << NL;
	} else {
		// single x 
		cout	<< "Solution (Δ == 0): " << NL
				<< var << "\t= (-" << b << ") / 2 * " << a << NL
				<< "\t= " << - b / 2 * a << NL;
	}
}