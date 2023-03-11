/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/11 23:03:00 by eli              ###   ########.fr       */
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
			// _execute = &Parser::
		} else {
			_parsefn = &Parser::_parseE;
		}
	}

Parser::~Parser() {}

/* Main Function ------------------------------------------------------------ */

Parser::result_tree Parser::parse() {
	unique_node	result = (this->*_parsefn)("");
	LOG("Getting main tree now");
	result_tree	tree = std::make_shared<unique_node>(std::move(result));

	if (*tree == NULL)
		throw EmptyContent();
	return tree;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

/**
 * Solver parsing
 *
 * GRAMMAR:
 * S	: E = ?
*/
Parser::unique_node	Parser::_parseS(const std::string& context_name) {
	(void)context_name;
	return nullptr;
}

/**
 * Assignation parsing
 *
 * GRAMMAR:
 * A	: ID = E
*/
Parser::unique_node	Parser::_parseA(const std::string& context_name) {
	LOG("In _parseA");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Identifier
		std::string		identifier(_token);
		_ret = _tokenizer.scanToken(_token);
		unique_node	value;
		if (_token == EQUAL) {
			// Simple variable
			value = _parseE(context_name);
		} else if (_token == L_PARENTHESIS) {
			// Function
			value = _parseFunction(identifier);
			LOG("Left parsefunction");
		}
		if (value == nullptr)
			throw IncorrectSyntax("Expected expression after `=`");
		Identifier	id(identifier, std::move(value), context_name);
		return id.toNode();
	}
	throw IncorrectSyntax("Bad assignation");
}

/**
 * Expression parsing
 *
 * GRAMMAR:
 * E	: T + T
 * 		| T - T
 * 		| T
*/
Parser::unique_node	Parser::_parseE(const std::string& context_name) {
	LOG("In _parseE");
	unique_node	a = _parseT(context_name);

	while (_ret != EEMPTY) {
		if (_token == ADDITION) {
			// T + T
			unique_node b = _parseT(context_name);
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `+`");
			Add	add(std::move(a), std::move(b));
			a = add.toNode();
		} else if (_token == SUBSTRACTION) {
			// T - T
			unique_node	b = _parseT(context_name);
			if (b == nullptr)
				throw IncorrectSyntax("Expecting term after `-`");
			Substract	sub(std::move(a), std::move(b));
			a = sub.toNode();
		} else if (_ret != EEMPTY) {
			throw IncorrectSyntax("Unexpected token: `" + _token + "`");
		} else {
			break;
		}
	}
	_ret = EEXPRESSION;
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
 * 		| Image
 **/
Parser::unique_node	Parser::_parseF(const std::string& context_name) {
	LOG("In _parseF");
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Identifier
		// Identifier	id(_token, nullptr);
		// _ret = _tokenizer.scanToken(_token);
		// return id.toNode();

		std::string		id_name(_token);
		_ret = _tokenizer.scanToken(_token);
		if (_token == L_PARENTHESIS) {
			// Image
			unique_node	a = _parseF(context_name);
			if (a == nullptr)
				throw Parser::IncorrectSyntax("Expecting value inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				Image	img(id_name, std::move(a));
				return img.toNode();
				// Identifier	func_id(id_name, std::move(a));
				// return func_id.toNode();
			}
			throw Parser::IncorrectSyntax("Expecting closing parenthesis `)`");
		}
		Identifier		id(id_name, nullptr, context_name);
		return id.toNode();

	} else if (_ret == ERATIONAL || _ret == EIMAGINARY) {
		// Rational || Imaginary
		return _parseSimpleValue(context_name);
	} else if (_ret == EDELIMITER) {
		if (_token == L_PARENTHESIS) {
			// Parenthesis
			unique_node	a = _parseE(context_name);
			if (a == nullptr)
				throw Parser::IncorrectSyntax("Expecting content inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
			throw Parser::IncorrectSyntax("Expecting final `)`");
		} else if (_token == L_BRACKET) {
			// Matrix
			return _parseMatrix();
		}
	} else if (_ret == ESYMBOL) {
		// Negate operation
		if (_token == NEGATE) {
			_ret = _tokenizer.scanToken(_token);
			Negate	negation(_parseF(context_name));
			return negation.toNode();
		}
	}
	return nullptr;
}

/**
 * Term parsing
 *
 * GRAMMAR:
 * 	T	: F * T
 * 		| F / T
 * 		| F % T
 * 		| F ^ T
 * 		| F
*/
Parser::unique_node	Parser::_parseT(const std::string& context_name) {
	LOG("In _parseT");
	unique_node	a = _parseF(context_name);

	if (a == nullptr)
		throw IncorrectSyntax("Expecting value before `" + _token + "`");
	if (_token == MULTIPLICATION) {
		// F * T
		unique_node	b = _parseT(context_name);
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after `*`");
		Multiply	mul(std::move(a), std::move(b));
		return mul.toNode();
	} else if (_token == DIVISION) {
		// F / T
		unique_node	b = _parseT(context_name);
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after `/`");
		Divide		div(std::move(a), std::move(b));
		return div.toNode();
	} else if (_token == MODULO) {
		// F % T
		unique_node b = _parseT(context_name);
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after `%`");
		Modulo		mod(std::move(a), std::move(b));
		return mod.toNode();
	} else if (_token == POWER) {
		// F ^ T
		unique_node b = _parseT(context_name);
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after `^`");
		Power		pow(std::move(a), std::move(b));
		return pow.toNode();
	}
	return a;
}

/* Utils -------------------------------------------------------------------- */

Parser::unique_node	Parser::_parseFunction(const std::string& func_name) {
	LOG("In _parseFunction");
	// Function
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		// Variable name
		// Identifier			var_name(_token, nullptr, func_name);
		std::string			var_name(_token);
		_ret = _tokenizer.scanToken(_token);
		if (_token != R_PARENTHESIS)
			throw IncorrectSyntax("Expecting `)`");
		_ret = _tokenizer.scanToken(_token);
		if (_token != EQUAL)
			throw IncorrectSyntax("Expecting `=`");

		// Body
		unique_node			body = _parseE(func_name);
		if (body == nullptr)
			throw IncorrectSyntax("Expecting function body after `=`");

		Function::tree_head	tree = std::make_shared<unique_node>(std::move(body));
		Function			fun(func_name, var_name, tree);
		return createVariable(fun);
	}
	throw IncorrectSyntax("Expecting variable name in parenthesis");
}

Parser::unique_node	Parser::_parseSimpleValue(const std::string& context_name) {
	if (_ret == ERATIONAL) {
		Rational	value(std::stold(_token));
		_ret = _tokenizer.scanToken(_token);
		return createVariable(value);
	} else if (_ret == EIMAGINARY) {
		Complex		value(0, 1);
		_ret = _tokenizer.scanToken(_token);
		if (_token == MULTIPLICATION) {
			// i * F
			unique_node	b = _parseT(context_name);
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
			if (_token == COMA) {
				_ret = _tokenizer.scanToken(_token);
				if (_token == L_BRACKET)
					continue;
				throw IncorrectSyntax("Expecting `[`");
			} else if (_token == R_BRACKET) {
				break;
			} else {
				throw IncorrectSyntax("Expecting `,` or `]`");
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
		} else {
			throw IncorrectSyntax("Expecting value inside bracket");
		}
	}
	return row;
}