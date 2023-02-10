/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 23:07:46 by eli              ###   ########.fr       */
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

/* Factor ------------------------------------------------------------------- */
/**
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
Parser::shared_node	Parser::parseF() {
	_ret = _tokenizer.scanToken(_token);

	if (_ret == ENAME) {
		Identifier	id(_token);
		return id.toNode();
	} else if (_ret == ERATIONAL) {
		Rational	value(std::stold(_token));
		return createVariable(value);
	} else if (_ret == EDELIMITER) {
		if (_token == L_PARENTHESIS) {
			shared_node	a = parseE();
			if (a == nullptr)
				throw Parser::IncorrectSyntax();
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
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

/* Expression --------------------------------------------------------------- */

Parser::shared_node	Parser::parseE() {
	shared_node	a = parseT();

	while (true) {
		if (_token == "+") {
			_ret = _tokenizer.scanToken(_token);
			shared_node b = parseT();
			Add		add(a, b)
		}
	}
	return nullptr;
}

/* Term --------------------------------------------------------------------- */

Parser::shared_node	Parser::parseT() {
	return nullptr;
}