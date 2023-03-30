/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 13:22:43 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "identifier.hpp"
#include "variable.hpp"
#include "add.hpp"
#include "substract.hpp"
#include "multiply.hpp"
#include "divide.hpp"
#include "modulo.hpp"
#include "power.hpp"
#include "negate.hpp"
#include "image.hpp"
#include "equality.hpp"
#include "utils.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Parser::Parser(const std::string& raw):
	_tokenizer(raw),
	_ret(EEMPTY) {
		if (raw.find(EQUAL) != std::string::npos) {
			// There's a `=`
			if (raw.find(QUESTION_MARK) != std::string::npos) {
				// There is an `?`
				_parsefn = &Parser::_parseS;
			} else {
				// There's no `?`
				_parsefn = &Parser::_parseA;
			}
		} else {
			throw IncorrectSyntax("Missing `=` sign	");
		}
	}

Parser::~Parser() {}

/* Main Function ------------------------------------------------------------ */

Parser::result_tree Parser::parse() {
	unique_node	result = (this->*_parsefn)();
	LOG("Getting main tree now");

	if (_ret != EEMPTY)
		throw IncorrectSyntax("Unexpected token");	
	if (result == nullptr)
		throw EmptyContent();

	result_tree	tree = std::make_shared<unique_node>(std::move(result));
	return tree;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

/* Parsing Differentiation -------------------------------------------------- */

/**
 * Solver parsing
 *
 * GRAMMAR:
 * S	: E = E ?
 * 		| E = ?
*/
Parser::unique_node	Parser::_parseS() {
	unique_node	lhs = _parseE();
	unique_node	result;

	if (lhs == nullptr)
		throw IncorrectSyntax("Left hand side expression incorrect");
	if (_ret != EEMPTY && _token == EQUAL) {
		// Equality
		unique_node	rhs = _parseE();
		if (rhs == nullptr) {
			if (_token == QUESTION_MARK) {
				// Computation
				_ret = _tokenizer.scanToken(_token);
				return lhs;
			}
			throw IncorrectSyntax("Right hand side expression incorrect");
		} else {
			Computor::toggle_equation();
		}
		Equality	eq(std::move(lhs), std::move(rhs));
		result = eq.toNode();
	}
	if (_ret == EEMPTY || _token != QUESTION_MARK)
		throw IncorrectSyntax("Bad equation syntax");
	_ret = _tokenizer.scanToken(_token);
	return result;
}

/**
 * Assignation parsing
 *
 * GRAMMAR:
 * A	: Identifier = E
*/
Parser::unique_node	Parser::_parseA() {
	LOG("In _parseA");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		unique_node		a;
		std::string		identifier(_token);
		_ret = _tokenizer.scanToken(_token);
		if (_token == EQUAL) {
			// Simple variable
			a = _parseE();
		} else if (_token == L_PARENTHESIS) {
			// Function
			if (_context.empty())
				_context = identifier;
			a = _parseFunction();
		}
		if (a == nullptr)
			throw IncorrectSyntax("Unexpected token after variable name");
		Identifier	id(identifier, std::move(a), _context, _var_name);

		_var_name.clear();
		return id.toNode();
	}
	throw IncorrectSyntax("Bad assignation");
}

/* Parse Function Helper ---------------------------------------------------- */

/**
 * Expression parsing (P)
 *
 * GRAMMAR:
 * E	: T + T
 * 		| T - T
 * 		| T
*/
Parser::unique_node	Parser::_parseE() {
	LOG("In _parseE");
	unique_node	a = _parseT();

	if (a == nullptr)
		return a;
	while (_ret != EEMPTY) {
		if (_token == ADDITION) {
			// T + T
			unique_node b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `+`");
			Add	add(std::move(a), std::move(b));
			a = add.toNode();
		} else if (_token == SUBSTRACTION) {
			// T - T
			unique_node	b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `-`");
			Substract	sub(std::move(a), std::move(b));
			a = sub.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Term parsing (MD)
 *
 * GRAMMAR:
 * 	T	: P
 * 		| T * P
 * 		| T / P
 * 		| T % P
*/
Parser::unique_node	Parser::_parseT() {
	LOG("In _parseT");
	unique_node	a = _parseP();

	if (a == nullptr)
		return a;
	while (1) {
		if (_token == MULTIPLICATION) {
			// T * F
			unique_node	b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `*`");
			Multiply	mul(std::move(a), std::move(b));
			a = mul.toNode();
		} else if (_token == DIVISION) {
			// T / F
			unique_node	b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `/`");
			Divide		div(std::move(a), std::move(b));
			a = div.toNode();
		} else if (_token == MODULO) {
			// T % F
			unique_node b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `%`");
			Modulo		mod(std::move(a), std::move(b));
			a = mod.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Exponentiation parsing (E)
 * 
 * GRAMMAR:
 * 	P	: F ^ F
 * 		: F
*/
Parser::unique_node	Parser::_parseP() {
	unique_node	a = _parseF();

	if (a == nullptr)
		return a;
	while (1) {
		if (_token == POWER) {
			// F ^ F
			unique_node b = _parseF();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `^`");
			Power		pow(std::move(a), std::move(b));
			a = pow.toNode();
		} else {
			break;
		}
	}
	return a;
}

/**
 * Factor parsing (AS)
 *
 * GRAMMAR:
 * F	: Identifier
 * 		| Variable
 * 		| i * F
 * 		| ( E )
 * 		| - F
 * 		| + F
 * 		| Image
 **/
Parser::unique_node	Parser::_parseF() {
	LOG("In _parseF");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		std::string		id_name(_token);
		_ret = _tokenizer.scanToken(_token);
		if (_token == L_PARENTHESIS) {
			// Image
			unique_node	a = _parseE();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting value inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				Image	img(id_name, std::move(a), _context);
				return img.toNode();
			}
			throw IncorrectSyntax("Expecting closing parenthesis `)`");
		}
		if (utils::toLower(id_name) == utils::toLower(_context)) {
			// Function is recursive
			throw IncorrectSyntax("Function definition invalid");
		}
		Identifier		id(id_name, nullptr, _context);
		return id.toNode();

	} else if (_ret == ERATIONAL || _ret == EIMAGINARY) {
		// Rational || Imaginary
		return _parseSimpleValue();
	} else if (_ret == EDELIMITER) {
		if (_token == L_PARENTHESIS) {
			// Parenthesis
			unique_node	a = _parseE();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting content inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
			throw IncorrectSyntax("Expecting final `)`");
		} else if (_token == L_BRACKET) {
			// Matrix
			return _parseMatrix();
		}
	} else if (_ret == ESYMBOL) {
		// Negate operation
		if (_token == NEGATE) {
			unique_node	a = _parseF();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting value after `-`");
			Negate	negation(std::move(a));
			return negation.toNode();
		} else if (_token == ADDITION) {
			unique_node a = _parseF();
			if (a == nullptr)
				throw IncorrectSyntax("Expecting value after `+`");
			return a;
		}
	}
	return nullptr;
}

/* Utils -------------------------------------------------------------------- */

Parser::unique_node	Parser::_parseFunction() {
	LOG("In _parseFunction");
	// Function
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Variable name
		_var_name = _token;
		_ret = _tokenizer.scanToken(_token);
		if (_token != R_PARENTHESIS)
			throw IncorrectSyntax("Expecting `)`, got `" + _token + " instead`");

		if (utils::toLower(_var_name) == utils::toLower(_context))
			throw IncorrectSyntax("Function variable can't be name like the function itself");

		_ret = _tokenizer.scanToken(_token);
		if (_token != EQUAL)
			throw IncorrectSyntax("Expecting `=` right after function declaration");

		// Body
		unique_node			body = _parseE();
		if (body == nullptr)
			throw IncorrectSyntax("Expecting function body after `=`");
		_context.clear();

		Function::tree_head	tree = std::make_shared<unique_node>(std::move(body));
		Function			fun(_var_name, tree);

		return createVariable(fun);
	}
	throw IncorrectSyntax("Expecting variable name in parenthesis");
}

Parser::unique_node	Parser::_parseSimpleValue() {
	if (_ret == ERATIONAL) {
		// Rational
		if (_token.size() >= 10)
			throw IncorrectSyntax("Value too big");
		try {
			Rational	value(std::stold(_token));
			_ret = _tokenizer.scanToken(_token);
			return createVariable(value);
		} catch (const std::invalid_argument& e) {
			return nullptr;
		}
	} else if (_ret == EIMAGINARY) {
		Complex		value(0, 1);
		_ret = _tokenizer.scanToken(_token);
		if (_token == MULTIPLICATION) {
			// i * F
			unique_node	b = _parseP();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after *");
			Multiply	mul(createVariable(value), std::move(b));
			return mul.toNode();
		}
		return createVariable(value);
	}
	return nullptr;
}

Parser::unique_node Parser::_parseMatrix() {
	Matrix::matrix	rows;
	_ret = _tokenizer.scanToken(_token);

	if (_token == L_BRACKET) {
		while (true) {
			// Parse a new row
			rows.push_back(_parseMatrixRow());
			_ret = _tokenizer.scanToken(_token);
			if (_token == SEMICOLON) {
				_ret = _tokenizer.scanToken(_token);
				if (_token == L_BRACKET)
					continue;
				throw IncorrectSyntax("Expecting `[`");
			} else if (_token == R_BRACKET) {
				break;
			} else {
				throw IncorrectSyntax("Expecting `;` or `]`");
			}
		}
		_ret = _tokenizer.scanToken(_token);
		return createVariable(Matrix(std::move(rows)));
	}
	return nullptr;
}

Matrix::row Parser::_parseMatrixRow() {
	Matrix::row		row;

	while (true) {
		_ret = _tokenizer.scanToken(_token);
		if (_ret == ERATIONAL) {
			// Rational
			Rational	value(std::stold(_token));
			_ret = _tokenizer.scanToken(_token);
			row.push_back(value);
			if (_token == COMA) {
				continue;
			} else if (_token == R_BRACKET) {
				break;
			} else {
				throw IncorrectSyntax("Expecting `,` or `]`");
			}
		} else if (_ret != EEMPTY) {
			throw IncorrectSyntax("Unexpected token");
		} else {
			throw IncorrectSyntax("Expecting value inside bracket");
		}
	}
	return row;
}

void	Parser::_parseEqm() {
	if (_token == EQUAL) {
		_tokenizer.scanToken(_token);
		if (_token != QUESTION_MARK)
			throw IncorrectSyntax("Expecting `?` or expression after `=`");
	}
}