/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:28:07 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 18:49:20 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.hpp"
#include "utils.hpp"
#include "parser.hpp"
#include "solver.hpp"

using std::cout;
using std::cin;
using std::cerr;

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Menu::Menu() {
	// TODO: On init, disable sigint
	// show commands
}

Menu::~Menu() {}

void	Menu::prompt() {
	cout << PROMPT;
	std::string			entry;
	std::getline(cin, entry);

	_execute(entry);
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

void	Menu::_help() {
	static const char*	help_msg =
			"Welcome to computorv2 (made with love by @etran).\n"
			"Here's what you can do with this program:\n"
			" - calculate value:		[expression] = ?\n"
			"	example:	1+2 = ?\n"
			" - solve equation:		[expression] = [expression] ?\n"
			"	example:	x+1 = 2*x ?\n"
			" - assign value:		[variable] = [expression]\n"
			"	example:	a = 2\n";

	std::cout << help_msg;
}

void	Menu::_display() {
	_computor_context.show();
}

void	Menu::_reset() {
	_computor_context.reset();
}

void	Menu::_execute(const std::string& query) {
	static const char*	queries[3] = {
		__DISPLAY_HELP,
		__DISPLAY_MEMORY,
		__RESET_MEMORY
	};
	void				(Menu::*action[3])() = {
		&Menu::_help,
		&Menu::_display,
		&Menu::_reset
	};

	for (size_t i = 0; i < 3; ++i) {
		if (query == queries[i])
			return (this->*action[i])();
	}
	return _compute(query);
}

void	Menu::_compute(const std::string& entry) {
	try {
		Parser				parser(entry);
		Parser::result_tree	output = parser.parse();

		try {
			DEBUG("Collapsing");
			Indeterminates	ind_res = (*output)->collapse();
			cout << "Expanded expression:\n" << ind_res << NL;

			if (Computor::to_solve()) {
				Solver	solver(ind_res);
				solver.solve();
			}
			DEBUG("Finished solving");
		} catch (const Indeterminates::ExpansionNotSupported& e) {
			cerr << e.what() << NL;
			if (Computor::to_solve())
				cout << "This equation cannot be solved (format not supported)." << NL;
		}

		if (!Computor::to_solve()) {
			Parser::shared_itype	res = (*output)->eval();
			if (res != nullptr) {
				(*output)->print();
				cout << " = " << *res << NL;
			}
		}
	} catch (const Tokenizer::EmptyInput& empty) {
		return;
	} catch (const std::exception& e) {
		cerr << "Error: " << e.what() << NL;
	}
	_computor_context.flush();
}