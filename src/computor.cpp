/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/14 09:36:40 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */

/**
 * Global scope context.
*/
Computor::context	Computor::_memory;

/**
 * Local context start position.
*/
size_t				Computor::_context_pos = 0;

bool				Computor::_context_active = false;

// /**
//  * Specific context.
// */
// Computor::context_map	Computor::_local_memory;

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
	// const name_type& context_name
) {
	// if (context_name.empty()) {
		// _memory.push(std::make_pair(variable_name, value));
	// } else {
		// variable	var = std::make_pair(variable_name, value);
		// _local_memory[context_name].push(var);
	// }
	_memory.push_back(std::make_pair(variable_name, value));
}

/**
 * Returns variable_name if in context.
*/
const Computor::value_ptr	Computor::find(
	const name_type& variable_name,
	bool in_context
	// const name_type& context_name
) {
	// context cpy;

	// if (context_name.empty()) {
		// cpy = _memory;
	// } else {
	// 	context_map::const_iterator	memory = _local_memory.find(context_name);
	// 	if (memory == _local_memory.end())
	// 		return nullptr;
	// 	cpy = memory->second;
	// }	
	// while (!cpy.empty()) {	
	// 	const variable&	top = cpy.top();
	// 	if (top.first == variable_name)
	// 		return top.second;
	// 	cpy.pop();
	// }

	context::const_iterator	end;

	if (in_context || !_context_active)
		end = _memory.end();
	else
		end = _memory.begin() + _context_pos;

	for (context::const_iterator it = _memory.begin();
	it != end;
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
	_context_active = true;
	_context_pos = _memory.size();
}

/**
 * Flushes all temporary contexts.
*/
void	Computor::flush() {
	// _local_memory.clear();
	// if (_context_pos) {
		if (_context_active) {
			_memory.resize(_context_pos);
			_context_active = false;
		}
		// _context_pos = 0;
	// }
}

/**
 * Displays every contexts.
*/
void	Computor::show() const {
	// context		cpy(_memory);

	std::cout << "Global context:\n";
	// while (!cpy.empty()) {
	// 	std::cout << cpy.top().first << '=' << *cpy.top().second << NL;
	// 	cpy.pop();
	// }
	for (context::const_iterator it = _memory.begin();
	it != _memory.end();
	++it) {
		std::cout << it->first << '=' << *it->second << NL;
	}
	// for (context_map::const_iterator it = _local_memory.begin();
	// 	it != _local_memory.end();
	// 	++it
	// ) {
	// 	std::cout << "Context `" << it->first << '\'' << NL;
	// 	context	current(it->second);
	// 	while (!current.empty()) {
	// 		std::cout << current.top().first << '=' << *current.top().second << NL;
	// 		current.pop();
	// 	}
	// 	std::cout <<NL;
	// }
}