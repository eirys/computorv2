/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:02:01 by etran             #+#    #+#             */
/*   Updated: 2023/03/29 12:49:48 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "indeterminates.hpp"

class Solver {
	public:
		Solver(const Indeterminates& expression);
		virtual ~Solver();

		/* Main Function ---------------------------------------------------------- */

		void	solve() const;

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

		void	_simpleEquality() const;
		void	_rootOne(const std::string& var) const;
		void	_rootSquare(const std::string& var) const;
};

#endif