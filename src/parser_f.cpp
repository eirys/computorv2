/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:31:17 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 23:01:34 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_f.hpp"

ParserF::ParserF(Tokenizer& tokenizer):
	_tokenizer(tokenizer) {}

ParserF::~ParserF() {}

/* -------------------------------------------------------------------------- */

ParserF::shared_node	ParserF::parse() {
	std::string	token;

	while((token = _tokenizer.scanToken())!= nullptr) {
		
	}
}