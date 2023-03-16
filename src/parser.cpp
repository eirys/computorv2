/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/16 16:36:14 by etran            ###   ########.fr       */
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
			// There is an `=`
			if (raw.find(QUESTION_MARK) != std::string::npos) {
				_parsefn = &Parser::_parseS;
			} else {
				_parsefn = &Parser::_parseA;
			}
		} else {
			_parsefn = &Parser::_parseC;
		}
	}

Parser::~Parser() {}

/* Main Function ------------------------------------------------------------ */

Parser::result_tree Parser::parse() {
	unique_node	result = (this->*_parsefn)();
	LOG("Getting main tree now");

	if (_ret != EEMPTY)
		throw IncorrectSyntax("Unexpected token");	
	if (result == NULL)
		throw EmptyContent();

	result_tree	tree = std::make_shared<unique_node>(std::move(result));
	return tree;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

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
		if (rhs == nullptr)
			throw IncorrectSyntax("Right hand side expression incorrect");
		Equality	eq(std::move(lhs), std::move(rhs));
		result = eq.toNode();
	} else {
		/// TODO: Solve
	}
	if (_ret == EEMPTY || _token != QUESTION_MARK)
		throw IncorrectSyntax("Bad equation syntax");
	return result;
}

/**
 * Assignation parsing
 *
 * GRAMMAR:
 * A	: ID = E
*/
Parser::unique_node	Parser::_parseA() {
	LOG("In _parseA");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Identifier
		unique_node		a;
		std::string		identifier(_token);
		std::string		var_name;	// potentially empty
		_ret = _tokenizer.scanToken(_token);
		if (_token == EQUAL) {
			// Simple variable
			a = _parseE();
		} else if (_token == L_PARENTHESIS) {
			// Function
			_context = identifier;
			a = _parseFunction(var_name);

			Computor::create_context(identifier, var_name);
		}
		if (a == nullptr)
			throw IncorrectSyntax("Unexpected token");
		Identifier	id(identifier, std::move(a), _context, var_name);
		return id.toNode();
	}
	throw IncorrectSyntax("Bad assignation");
}

/**
 * Computation parsing
 *
 * GRAMMAR:
 * C	: E
*/
Parser::unique_node	Parser::_parseC() {
	unique_node	ret = _parseE();

	if (_ret != EEMPTY)
		throw IncorrectSyntax("Unexpected token: `" + _token + "`");
	return ret;
}

/**
 * Expression parsing
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
		throw IncorrectSyntax("Unexpected token: `" + _token + "`");
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
 * Factor parsing
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
				Image	img(id_name, std::move(a));
				return img.toNode();
			}
			throw IncorrectSyntax("Expecting closing parenthesis `)`");
		}
		if (utils::toLower(id_name) == utils::toLower(_context))
			throw IncorrectSyntax("Function definition invalid");
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

/**
 * Term parsing
 *
 * GRAMMAR:
 * 	T	: F
 * 		| T * F
 * 		| T / F
 * 		| T % F
 * 		| T ^ F
*/
Parser::unique_node	Parser::_parseT() {
	LOG("In _parseT");
	unique_node	a = _parseF();

	if (a == nullptr)
		throw IncorrectSyntax("Unexpected token");
	while (1) {
		if (_token == MULTIPLICATION) {
			// T * F
			unique_node	b = _parseF();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `*`");
			Multiply	mul(std::move(a), std::move(b));
			a = mul.toNode();
		} else if (_token == DIVISION) {
			// T / F
			unique_node	b = _parseF();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `/`");
			Divide		div(std::move(a), std::move(b));
			a = div.toNode();
		} else if (_token == MODULO) {
			// T % F
			unique_node b = _parseF();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting value after `%`");
			Modulo		mod(std::move(a), std::move(b));
			a = mod.toNode();
		} else if (_token == POWER) {
			// T ^ F
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

/* Utils -------------------------------------------------------------------- */

Parser::unique_node	Parser::_parseFunction(
	std::string& var_name
) {
	LOG("In _parseFunction");
	// Function
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Variable name
		var_name = _token;
		_ret = _tokenizer.scanToken(_token);
		if (_token != R_PARENTHESIS)
			throw IncorrectSyntax("Expecting `)`");
		_ret = _tokenizer.scanToken(_token);
		if (_token != EQUAL)
			throw IncorrectSyntax("Expecting `=`");

		// Body
		unique_node			body = _parseE();
		if (body == nullptr)
			throw IncorrectSyntax("Expecting function body after `=`");
		_context.clear();

		Function::tree_head	tree = std::make_shared<unique_node>(std::move(body));
		Function			fun(var_name, tree);

		return createVariable(fun);
	}
	throw IncorrectSyntax("Expecting variable name in parenthesis");
}

Parser::unique_node	Parser::_parseSimpleValue() {
	if (_ret == ERATIONAL) {
		// Rational
		if (_token.size() >= 60)
			throw IncorrectSyntax("Value too big");
		try {
			Rational	value(std::stold(_token));
			_ret = _tokenizer.scanToken(_token);
			return createVariable(value);
		} catch (const std::invalid_argument& e) {
			throw IncorrectSyntax("Unexpected token");
		}
	} else if (_ret == EIMAGINARY) {
		Complex		value(0, 1);
		_ret = _tokenizer.scanToken(_token);
		if (_token == MULTIPLICATION) {
			// i * F
			unique_node	b = _parseT();
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