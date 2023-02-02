/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:45:04 by eli               #+#    #+#             */
/*   Updated: 2023/01/27 16:36:03 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.hpp"
#include <cstring>

Tokenizer::Tokenizer(const std::string& raw):
	_raw(raw),
	_current_pos(0) {
		if (raw.empty())
			throw EmptyInput();
		if (!isblank(_raw[0])) {
			_current_pos = _raw.find(WHITESPACES);	// TODO: redo
			_next_token = _raw.substr(0, _current_pos);
		}
	}

Tokenizer::~Tokenizer() {}

/* Main function ------------------------------------------------------------ */
std::string	Tokenizer::scanToken() {
	if (_current_pos == std::string::npos)
		return nullptr;

	std::string		tmp(_next_token);
	size_t			next_pos;

	if (_find(NAME)) {
		next_pos = _find_not_of(NAME);
	} else if (_find(RATIONAL)) {
		next_pos = _find_not_of(RATIONAL);
	} else if (_find(WHITESPACES)) {
		next_pos = _find_not_of(WHITESPACES);
	} else if (_find(DELIMITER)) {
		next_pos = _current_pos + 1;
	} else if (_find(SYMBOL)) {
		next_pos = _current_pos + 1;
	}
	_next_token = _raw.substr(_current_pos, next_pos);
	return tmp;
}

/* Getter ------------------------------------------------------------------- */
const std::string&	Tokenizer::getNextToken() const {
	return _next_token;
}

/* Parsing utils ------------------------------------------------------------ */
bool	Tokenizer::_find(constexpr const char* charset) const {
	return _raw.find(charset, _current_pos) != std::string::npos;
}

size_t	Tokenizer::_find_not_of(constexpr const char* charset) const {
	return _raw.find_first_not_of(charset, _current_pos);
}