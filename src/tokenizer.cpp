/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:45:04 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 10:16:10 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.hpp"
#include <cstring>

Tokenizer::Tokenizer(const std::string& raw):
	_raw(raw),
	_current_pos(0) {
		if (!isblank(_raw[0])) {
			_current_pos = _raw.find(WHITESPACES);
			_next_token = _raw.substr(0, _current_pos);
		}
	}

Tokenizer::~Tokenizer() {}

/* Function ----------------------------------------------------------------- */

std::string	Tokenizer::scanToken() {
	if (_current_pos == std::string::npos)
		return nullptr;
	size_t			next_pos = _raw.find(WHITESPACES, _current_pos + 1);
	std::string		tmp(_next_token);
	_next_token = _raw.substr(_current_pos, next_pos);
	return tmp;
}