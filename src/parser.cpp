/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/03 23:44:44 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Parser::Parser(const std::string& raw):
	_tokenizer(raw),
	_ret(EMPTY) {}

Parser::~Parser() {}

/* Expression --------------------------------------------------------------- */

/**
 * GRAMMAR:
 * E	: T + T
 * 		| T - T
 * 		| T
 * 
*/
Parser::unique_node	Parser::parseE() {
	LOG("In parseE");
	unique_node	a = parseT();

	while (_ret != EMPTY) {
		if (_token == ADDITION) {
			// T + T
			LOG("Addition");
			unique_node b = parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting variable after +");
			Add	add(std::move(a), std::move(b));
			a = add.toNode();
		} else if (_token == SUBSTRACTION) {
			// T - T
			LOG("Subs");
			unique_node	b = parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting variable after -");
			Substract	sub(std::move(a), std::move(b));
			a = sub.toNode();
		} else if (_token == WHITESPACES) {
			// Whitespace
			LOG("WS");
			_tokenizer.scanToken(_token);
			continue;
		} else {
			LOG("No'in");
			break;
		}
	}
	return a;
}


/* Factor ------------------------------------------------------------------- */

/**
 * GRAMMAR:
 * F	: Identifier
 * 		| Variable
 * 		| ( E )
 * 		| - F
 * 
 * MODEL:
 * if token == identifier {
 * 	if next token == '='
 * 		identifier
 * 	else
 * 		function (TODO: define alg)
 * }
 * else if token == variable (TODO: Complex/Matrix identification)
 * 	return variable
 * else if token == Parenthesis
 * 	scantoken,
 * 	a = parseExpression,
 * 	if a == null: error
 *	if token == ) 
 *		scantoken()
 *		return a
 * else
 * 	error
 * else if token == -
 * 	return negate, F
*/
Parser::unique_node	Parser::parseF() {
	LOG("In parseF");
	_ret = _tokenizer.scanToken(_token);	

	if (_ret == ENAME) {
		Identifier	id(_token);
		_ret = _tokenizer.scanToken(_token);
		return id.toNode();
	} else if (_ret == ERATIONAL) {
		Rational	value(std::stold(_token));
		_ret = _tokenizer.scanToken(_token);
		return createVariable(value);
	} else if (_ret == EDELIMITER) {
		if (_token == L_PARENTHESIS) {
			unique_node	a = parseE();
			if (a == nullptr)
				throw Parser::IncorrectSyntax("Expecting content inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
			throw Parser::IncorrectSyntax("Expecting final )");
		}
	} else if (_ret == ESYMBOL) {
		if (_token == NEGATE) {
			_ret = _tokenizer.scanToken(_token);
			Negate	negation(parseF());
			return negation.toNode();
		}
	}
	return nullptr;
}


/* Term --------------------------------------------------------------------- */

/**
 * GRAMMAR:
 * 	T	: F * T
 * 		| F / T
 * 		| F
*/
Parser::unique_node	Parser::parseT() {
	// _ret = _tokenizer.scanToken(_token);
	LOG("In parseT");
	unique_node	a = parseF();

	if (_token == MULTIPLICATION) {
		// _ret = _tokenizer.scanToken(_token);
		unique_node	b = parseT();
		if (b == nullptr)
			throw IncorrectSyntax("EXpecting value after *");
		Multiply	mul(std::move(a), std::move(b));
		return mul.toNode();
	} else if (_token == DIVISION) {
		// _ret = _tokenizer.scanToken(_token);
		unique_node	b = parseT();
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after /");
		Divide		div(std::move(a), std::move(b));
		return div.toNode();
	}
	return a;
}