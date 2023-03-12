/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/03/12 14:07:27 by eli              ###   ########.fr       */
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

using std::cout;
using std::cerr;

void test8() {
	Computor	computor_context;
	while (true) {
		computor_context.show();
		try {
			std::string			entry;
			std::getline(std::cin, entry);

			Parser				parser(entry);
			Parser::result_tree	output = parser.parse();
	
			LOG("Out of parser");

			(*output)->print();
			cout << " = " << *(*output)->eval() << NL;
			Computor::flush();
		} catch (const Tokenizer::EmptyInput& empty) {
			break;
		} catch (const Parser::EmptyContent& ws) {
			continue;
		} catch (const std::exception& e) {
			cerr << e.what() << NL;
		}
	}
}

int main() {
	test8();
	return 0;
}