/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:31:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/27 14:53:26 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_f.hpp"

ParserF::ParserF(Tokenizer& tokenizer):
	_tokenizer(tokenizer) {}

ParserF::~ParserF() {}

/* -------------------------------------------------------------------------- */

ParserF::shared_node	ParserF::parse() {
	std::string	token;

	while((token = _tokenizer.scanToken()).c_str() != nullptr) {
		/* Name */
		if (token.find(LETTER) != std::string::npos) {
			std::string	next_element = _tokenizer.getNextToken();
			/* Identifier */
			// if (_isIdentifier(token))
		}
		/**
		 * if token == identifier {
		 * 	if next token == '='
		 * 		identifier
		 * 	else
		 * 		parse function
		 * }
		 * else if token == variable
		 * 	return variable
		 * else if token == Parenthesis
		 * 	return expression
		 * else if token == -
		 * 	return negate, F
		*/
	}
	return nullptr;
}

// bool	ParserF::_isIdentifier(const std::string& str) const {
// 
// }