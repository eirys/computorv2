/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:28:07 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 12:34:07 by eli              ###   ########.fr       */
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
	cout <<	"Welcome to computorv2 (v1.0.0, 2023) made with love by @etran.\n"
			"Type '" __DISPLAY_COMMANDS
			"' to display the list of available commands.\n";
	// TODO: On init, disable sigint
	// show commands
}

Menu::~Menu() {}

void	Menu::prompt() {
	cout << PROMPT;
	std::string			entry;
	std::getline(cin, entry);

	_execute(utils::trimmed(entry));
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

void	Menu::_help() {
	static const char*	help_msg =
		"Here's what you can do with this program:\n"
		"Computorv2 is a computation program. You can:"
		"    calculate value:"
		"\t[expression] = ?\n"
		"\t(example: `1+2 = ?`)\n"
		"    solve equation (1st and 2nd degree polynomials in R only):"
		"\t[expression] = [expression] ?\n"
		"\t(example: `x+1 = 2*x ?`)\n"
		"    assign value:"
		"\t[variable] = [expression]\n"
		"\t(example: `a = 2`)\n\n"
		"note: Computorv2 supports complexes and matrixes too.\n"
		"\t(example: `c = 12.5 + 3*i`  `m = [[1, 0]; [0, 13]]`)\n";

	cout << help_msg;
}

void	Menu::_display() {
	cout << "Memory state:\n";
	_computor_context.show();
}

void	Menu::_reset() {
	_computor_context.reset();
	cout << "Memory was reset\n";
}

void	Menu::_commands() {
	static const char*	cmd_list =
		"\n    Available commands:\n"
		"      " __DISPLAY_HELP		"\t\tquick explanation of this project\n"
		"      " __DISPLAY_COMMANDS	"\t\tlists available commands\n"
		"      " __DISPLAY_MEMORY	"\t\tdisplays current memory state\n"
		"      " __RESET_MEMORY		"\t\tresets current memory state\n";
	cout << cmd_list << NL;
}

void	Menu::_execute(const std::string& query) {
	static const char*	queries[4] = {
		__DISPLAY_HELP,
		__DISPLAY_MEMORY,
		__RESET_MEMORY,
		__DISPLAY_COMMANDS
	};

	static void			(Menu::*action[4])() = {
		&Menu::_help,
		&Menu::_display,
		&Menu::_reset,
		&Menu::_commands
	};

	for (size_t i = 0; i < 4; ++i) {
		if (query == queries[i])
			return (this->*action[i])();
	}
	return _compute(query);
}

void	Menu::_compute(const std::string& entry) {
	try {
		Parser				parser(entry);
		Parser::result_tree	output = parser.parse();

		Indeterminates	ind_res;

		try {
			DEBUG("Collapsing");
			ind_res = (*output)->collapse();
			cout	<< "Expanded expression:\n" << ind_res
					<< (Computor::to_solve() ? " = 0" : "") << NL;
		} catch (const Indeterminates::ExpansionNotSupported& e) {
			cerr << e.what() << NL;
			if (Computor::to_solve())
				cout << "This equation cannot be solved (format not supported)." << NL;
		}

		if (Computor::to_solve()) {
			Solver	solver(ind_res);
			solver.solve();
			DEBUG("Finished solving");
		} else {
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