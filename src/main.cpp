/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 18:48:31 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>

#define __ARGUMENTS_COMPUTOR "Argument was unexpected\n"
#define __DANGEROUS_COMPUTOR "Dangerous maneuver...\n"

void	puterror(const char* msg) {
	write(STDERR_FILENO, msg, strlen(msg));
}

#include "utils.hpp"
#include "math.hpp"

#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include "function.hpp"
#include "atree_node.hpp"

#include "computor.hpp"
#include "parser.hpp"
#include "menu.hpp"

using std::cin;
using std::cout;
using std::cerr;

int main(int ac, char* const* av) {
	if (ac != 1) {
		puterror(__ARGUMENTS_COMPUTOR);
		std::exit(EXIT_FAILURE);
	} else if (!isatty(STDIN_FILENO)) {
		puterror(__DANGEROUS_COMPUTOR);
		std::exit(EXIT_FAILURE);
	}

	(void)av;

	Menu		menu_handler;

	while (!cin.eof()) {
		menu_handler.prompt();
/* 		try {
			// cout << PROMPT;
			// std::string			entry;
			// std::getline(cin, entry);

			Parser				parser(entry);
			Parser::result_tree	output = parser.parse();
			// LOG("Out of parser");

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
			continue;
		} catch (const std::exception& e) {
			cerr << "Error: " << e.what() << NL;
		}
		menu_handler.flush(); */
	}
	cout << "quit\n";
	return 0;
}