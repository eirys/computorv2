/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:03:58 by eli               #+#    #+#             */
/*   Updated: 2022/12/24 21:04:29 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <map>

# include "utils.hpp"
# include "math.hpp"

# define NUMBER_STR "0123456789"
# define POLYNOMIAL_STR "0123456789X"

enum eSide {
	LEFTSIDE = 1,
	RIGHTSIDE = -1
};

class Parser {
	public:
	/* -- CONSTRUCTOR - DESTRUCTOR -------------------------------- */
		Parser(const char* input):
			_raw(input),
			_order0(0),
			_order1(0),
			_order2(0) {}

		~Parser() {}

	/* -- PARSING ------------------------------------------------- */
		void 
			parse() {
				const size_t	pos_equal = _raw.find(" = ");

				if (pos_equal == std::string::npos)
					throw std::string("Not correct format");
				_parseCoefficients(_parseTerms(_raw.substr(0, pos_equal + 1)), LEFTSIDE);
				_parseCoefficients(_parseTerms(_raw.substr(pos_equal + 3)), RIGHTSIDE);

				LOG(_order0);
				LOG(_order1);
				LOG(_order2);
				_display();
			}

	/* -- GETTERS ------------------------------------------------ */
		double
			getOrder0() const {
				return _order0;
			}
		
		double
			getOrder1() const {
				return _order1;
			}

		double
			getOrder2() const {
				return _order2;
			}

		bool
			is_trivial() const {
				if (!_raw.empty()
					&& _orderY.empty()
					&& !(_order0
						|| _order1
						|| _order2))
					return true;
				return false;
			}

	private:
	/* -- PROPERTIES ---------------------------------------------- */
		const std::string					_raw;
		double								_order0;
		double								_order1;
		double								_order2;
		std::map<int, double>				_orderY;

	/* -- MAIN PARSE FUNCTION ------------------------------------- */

		/* Parse the coefficients factorised values from each side of the equation */
		void
			_parseCoefficients(const std::list<std::string>& list, enum eSide side) {
				for (std::list<std::string>::const_iterator it = list.begin();
				it != list.end();
				++it) {
					const double value = side * _extractCoef(*it);
					const int order = _extractOrder(*it);
					switch (order) {
						case 0:
							_order0 += value;
							break;
						case 1:
							_order1 += value;
							break;
						case 2:
							_order2 += value;
							break;
						default:
							_newOrder(_orderY, order, value);
					}
				}
			}

	/* -- DISPLAY ------------------------------------------------ */

		/* Display reduced form of the equation */
		void
			_displayReducedEquation() const {
				const bool	is_positive0 = _order0 > 0;
				const bool	is_positive1 = _order1 > 0;
				const bool	is_positive2 = _order2 > 0;
				bool		has_precedent = false;
				using		std::cout;

				cout << "Reduced form: ";
				if (_order0) {
					cout << (is_positive0 ? "" : "- ")
						 << math::abs(_order0) << " * X ^ 0";
					has_precedent = true;
				}
				if (_order1) {
					if (has_precedent) {
						cout << (is_positive1 ? " + " : " - ");
					} else {
						has_precedent = true;
						cout << (is_positive1 ? "" : "- ");
					}
					cout << math::abs(_order1) << " * X ^ 1";
				}
				if (_order2) {
					if (has_precedent) {
						cout << (is_positive2 ? " + " : " - ");
					} else {
						has_precedent = true;
						cout << (is_positive2 ? "" : "- ");
					}
					cout << math::abs(_order2) << " * X ^ 2";
				}
				_displayGarbage(has_precedent);
				cout << " = 0" << NL;
			}

		/* Display the excess order terms */
		void
			_displayGarbage(bool& has_precedent) const {
				using	std::cout;

				if (_orderY.empty())
					return;
				for (std::map<int, double>::const_iterator it = _orderY.begin();
					it != _orderY.end();
					++it) {
					if (has_precedent) {
						cout << (it->second > 0 ? " + " : " - ");
					} else {
						has_precedent = true;
						cout << (it->second > 0 ? "" : "- ");
					}
					cout << math::abs(it->second) << " * X ^ " << it->first;
				}
			}

		void
			_displayOrder() const {
				using	std::cout;

				cout << "Polynomial degree: ";
				if (!_orderY.empty())
					cout << _orderY.rbegin()->first << NL;
				else if (_order2)
					cout << '2' << NL;
				else if (_order1)
					cout << '1' << NL;
				else
					cout << '0' << NL;
			}

	/* -- PARSE UTILS --------------------------------------------- */
		const std::list<std::string>
			_parseTerms(std::string copy) {
				std::list<std::string>	terms;
	
				while (!copy.empty())
					terms.push_back(_getNextTerm(copy));
				return terms;
			}
	
		std::string
			_getNextTerm(std::string& copy) {
				const size_t		sum_pos = copy.find_first_of("+-", 1);
				const std::string	term = _cutOut(copy.substr(0, sum_pos));
	
				if (sum_pos == std::string::npos)
					copy.clear();
				else
					copy = copy.substr(sum_pos);
				return term;
			}
	
		std::string
			_cutOut(const std::string& chunk) {
				const size_t	last_ws = chunk.find_last_of(POLYNOMIAL_STR);
	
				return chunk.substr(0, last_ws + 1);
			}
	
		double
			_extractCoef(const std::string& chunk) {
				const size_t	first_nb = chunk.find_first_of(NUMBER_STR);
				int				sign;
	
				if (first_nb == 2)
					sign = chunk[0] == '-' ? -1 : 1;
				else if (first_nb == 0)
					sign = 1;
				else
					throw std::string("Not correct format");
				return sign * std::stod(chunk.substr(first_nb, chunk.find(' ', first_nb)));
			}
	
		int
			_extractOrder(const std::string& chunk) {
				const size_t	var_pos = chunk.find("X ^ ");
	
				if (var_pos == std::string::npos)
					return 0;
				return std::stoi(chunk.substr(var_pos + 4));
			}
	
		void
			_newOrder(std::map<int, double>& m, const int order, const double value) {
				std::map<int, double>::iterator	it = m.find(order);
	
				if (it != m.end())
					it->second += value;
				else
					m.insert(std::pair<int, double>(order, value));
			}

	/* -- PRESENTATION ------------------------------------------- */
		void
			_display() const {
				if (is_trivial()) {
					std::cout << "0 = 0\n";
				} else {
					_displayReducedEquation();
					_displayOrder();
				}
			}
};

#endif
