/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:31:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/26 18:09:22 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_f.hpp"

ParserF::ParserF(Tokenizer& tokenizer):
	_tokenizer(tokenizer) {}

ParserF::~ParserF() {}

/* -------------------------------------------------------------------------- */

ParserF::shared_node	ParserF::parse() {
	return nullptr;
	// std::string	token;

	// while((token = _tokenizer.scanToken()) != nullptr) {
		
	// }
}