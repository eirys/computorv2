/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:02:01 by etran             #+#    #+#             */
/*   Updated: 2023/03/21 18:25:19 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "indeterminates.hpp"

class Solver {
	public:
		Solver(const Indeterminates& expression):
			_expression(expression.) {}
		virtual ~Solver();

		bool	solve() const {
			switch (_expression.getMaxIndex()) {
				case 0:
					// verify equality
					return false;
				case 1:
					rootOne();
					break;
				case 2:
					rootSquare();
					break;
				default:
					cerr << "This expression cannot be solved." << NL;
			}
			return true;
		}

	private:
		const Indeterminates	_expression;

		void	_rootOne() const {
			
		}

		void	_rootSquare() const {

		}
};

#endif