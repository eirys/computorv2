/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:59 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 14:56:13 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Parser::Parser(const std::string& raw):
	_tokenizer(raw) {}

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
	Tokenizer::ETokenType	ret = _tokenizer.scanToken(_token);

	while (!_token.empty()) {
		if (ret == ENAME) {
			return createIdentifier(_token);
		} else if (ret == ERATIONAL) {
			Rational	value(std::stold(_token));
			return createVariable(value);
		} else if (ret == EDELIMITER) {
			if (_token == L_PARENTHESIS) {
				_tokenizer.scanToken(_token);
			}
		}

		ret = _tokenizer.scanToken(_token);
	}
	return nullptr;
}

/* Expression --------------------------------------------------------------- */

Parser::shared_node	Parser::parseE() {
	return nullptr;
}

/* Term --------------------------------------------------------------------- */

Parser::shared_node	Parser::parseT() {
	return nullptr;
}