/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/03/16 17:24:28 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>
#include<iostream>

#include "utils.hpp"
#include "math.hpp"

#include "rational.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include "function.hpp"
#include "atree_node.hpp"

# include "variable.hpp"
# include "add.hpp"
# include "substract.hpp"
# include "divide.hpp"
# include "multiply.hpp"
# include "negate.hpp"
# include "identifier.hpp"

#include "computor.hpp"
#include "parser.hpp"

using std::cin;
using std::cout;
using std::cerr;

void test8() {
	Computor	computor_context;
	while (!cin.eof()) {
		computor_context.show();
		try {
			cout << PROMPT;
			std::string			entry;
			std::getline(cin, entry);

			Parser				parser(entry);
			Parser::result_tree	output = parser.parse();
	
			LOG("Out of parser");

			Parser::shared_itype	res = (*output)->eval();
			(*output)->print();
			if (res != nullptr)
				cout << " = " << *res << NL;
			computor_context.flush();
		} catch (const Tokenizer::EmptyInput& empty) {
			continue;
		} catch (const std::exception& e) {
			cerr << "Error: " << e.what() << NL;
		}
	}
}

int main() {
	test8();
	return 0;
}