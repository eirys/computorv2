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
	unique_node	a = _parseT();

	while (_ret != EMPTY) {
		if (_token == ADDITION) {
			// T + T
			LOG("Addition");
			unique_node b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting variable after `+`");
			Add	add(std::move(a), std::move(b));
			a = add.toNode();
		} else if (_token == SUBSTRACTION) {
			// T - T
			LOG("Subs");
			unique_node	b = _parseT();
			if (b == nullptr)
				throw IncorrectSyntax("Expecting variable after `-`");
			Substract	sub(std::move(a), std::move(b));
			a = sub.toNode();
		} else {
			LOG("No'in");
			break;
		}
	}
	return a;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

/* Factor ------------------------------------------------------------------- */

/**
 * GRAMMAR:
 * F	: Identifier
 * 		| Variable
 * 		| i * F
 * 		| ( E )
 * 		| - F
 **/
Parser::unique_node	Parser::_parseF() {
	LOG("In _parseF");
	_ret = _tokenizer.scanToken(_token);	

	if (_ret == ENAME) {
		// Identifier
		Identifier	id(_token);
		_ret = _tokenizer.scanToken(_token);
		return id.toNode();
	} else if (_ret == ERATIONAL) {
		// Variable (Rational)
		Rational	value(std::stold(_token));
		_ret = _tokenizer.scanToken(_token);
		return createVariable(value);
	} else if (_ret == EIMAGINARY) {
		// Variable (Complex)
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
	} else if (_ret == EDELIMITER) {
		// Parenthesis
		if (_token == L_PARENTHESIS) {
			unique_node	a = parseE();
			if (a == nullptr)
				throw Parser::IncorrectSyntax("Expecting content inside parenthesis");
			if (_token == R_PARENTHESIS) {
				_ret = _tokenizer.scanToken(_token);
				return a;
			}
			throw Parser::IncorrectSyntax("Expecting final `)`");
		}
	} else if (_ret == ESYMBOL) {
		// Negate operation
		if (_token == NEGATE) {
			_ret = _tokenizer.scanToken(_token);
			Negate	negation(_parseF());
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
Parser::unique_node	Parser::_parseT() {
	LOG("In _parseT");
	unique_node	a = _parseF();

	if (_token == MULTIPLICATION) {
		// F * T
		unique_node	b = _parseT();
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after *");
		Multiply	mul(std::move(a), std::move(b));
		return mul.toNode();
	} else if (_token == DIVISION) {
		// F / T
		unique_node	b = _parseT();
		if (b == nullptr)
			throw IncorrectSyntax("Expecting value after /");
		Divide		div(std::move(a), std::move(b));
		return div.toNode();
	}
	return a;
}

Complex	Parser::_convertTokenToImaginary() const {
	const size_t	i_pos = _token.find('i');
	if (_token.find('i', i_pos + 1) != std::string::npos)
		throw Parser::IncorrectSyntax("Too many `i` in complex value, expecting only one");

	Rational	i_value;
	if (i_pos == 0) {
		i_value = std::stold(_token.substr(i_pos + 1));
	} else if (i_pos == _token.size()) {
		i_value = std::stold(_token);
	} else {
		throw Parser::IncorrectSyntax("Expecting `i` to be at the start or end of value");
	}
	return Complex(0, i_value);
	// if (i_pos != 0 && i_pos != _token.size())
	// 	throw Parser::IncorrectSyntax("Expecting `i` to be at the start or end of value");
}