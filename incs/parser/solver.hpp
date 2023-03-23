/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:02:01 by etran             #+#    #+#             */
/*   Updated: 2023/03/23 14:58:25 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "indeterminates.hpp"

class Solver {
	public:
		Solver(const Indeterminates& expression):
			_expression(expression) {}
		virtual ~Solver() {}

		/* Main Function ---------------------------------------------------------- */

		bool	solve() const {
			using std::cout;

			void	(Solver::*solve_function)(const std::string&) const;

			if (_expression.getNbIndeterminates() > 1)
				throw TooManyIndeterminates();
			switch (_expression.getMaxExponent()) {
				case 0:
					return false;
				case 1:
					cout << "Solving degree 1 equation" << NL;
					solve_function = &Solver::_rootOne;
					break;
				case 2:
					cout << "Solving degree 2 equation" << NL;
					solve_function = &Solver::_rootSquare;
					break;
				default:
					throw ExponentTooHigh();
			}
			const std::string	main_variable_name = _expression.getMainIndeterminate();
			DEBUG("main indet: " << main_variable_name);
			(this->*solve_function)(main_variable_name);

			return true;
		}

		/* Exception -------------------------------------------------------------- */
		class Unsolvable: public std::exception {
			protected:
				Unsolvable(): _specifics("Can't be solved: ") {}

				std::string	_specifics;
		};
		class TooManyIndeterminates: public Unsolvable {
			public:
				TooManyIndeterminates() {
					_specifics +=
						"This equation contains too many indeterminates";
				}
				const char* what() const throw() {
					return _specifics.c_str();
				}
		};
		class ExponentTooHigh: public Unsolvable {
			public:
				ExponentTooHigh() {
					_specifics +=
						"This polynomial's degree is too high.";
				}
				const char* what() const throw() {
					return _specifics.c_str();
				}
		};

	private:
		const Indeterminates&	_expression;

		/**
		 * FORMAT:
		 *	bx^1 + cx^0 = 0
		*/
		void	_rootOne(const std::string& var) const {
			using std::cout;

			const Rational	b = _expression.getFactorFrom(var, Indeterminates::unit);
			const Rational	c = _expression.getFactorFrom(var, Indeterminates::null);

			const Rational	result(-c/b);

			cout << "Solution: " << var << " = " << result << NL;
		}

		void	_rootSquare(const std::string& var) const {
			using std::cout;
			(void)var;
		}

		long double	_getDelta() const {
			// Rational	delta = 1;
			return 1;
		}
};

#endif