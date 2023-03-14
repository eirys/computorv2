/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/14 11:53:11 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */

/**
 * Global scope context.
*/
Computor::context		Computor::_memory;

/**
 * Subcontext start position.
*/
Computor::context_pos	Computor::_subcontext_pos;

/**
 * Number of active subcontext.
*/
uint_fast16_t			Computor::_active_context = 0;

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Computor::Computor() {}

Computor::~Computor() {}

/* Function ----------------------------------------------------------------- */

/**
 * Pushes new value to context.
*/
void	Computor::push(
	const name_type& variable_name,
	const value_ptr& value
) {
	if (_active_context > 0) {
		// Don't erase previous occurence if in context
		_memory.push_back(std::make_pair(variable_name, value));
	} else {
		// Erase previous occurence
		for (context::reverse_iterator it = _memory.rbegin();
		it != _memory.rend();
		++it) {
			if (it->first == variable_name) {
				it->second = value;
				return;
			}
		}
		_memory.push_back(std::make_pair(variable_name, value));
	}
}

/**
 * Returns variable_name if in context.
*/
const Computor::value_ptr	Computor::find(
	const name_type& variable_name,
	bool in_context
) {
	context::const_reverse_iterator	start;

	if (in_context || _active_context == 0)
		start = _memory.rbegin();
	else
		start = _memory.rend() - _subcontext_pos.back();

	for (context::const_reverse_iterator it = start;
	it != _memory.rend();
	++it) {
		if (it->first == variable_name)
			return it->second;
	}
	return nullptr;
}

/**
 * Locks a new _context_pos.
*/
void	Computor::create_context() {
	_active_context += 1;
	_subcontext_pos.push_back(_memory.size());
}

/**
 * Flushes all temporary contexts.
*/
void	Computor::flush() {
	while (_active_context > 0) {
		_memory.resize(_subcontext_pos.back());
		_subcontext_pos.pop_back();
		--_active_context;
	}
}

/**
 * Displays global context.
*/
void	Computor::show() const {
	std::cout << "Global context:\n";
	for (context::const_reverse_iterator it = _memory.rbegin();
	it != _memory.rend();
	++it) {
		std::cout << it->first << '=' << *it->second << NL;
	}
}