/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/15 17:40:31 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */

/**
 * Global scope context.
*/
Computor::context		Computor::_memory;

Computor::context_map	Computor::_subcontexts;

/**
 * Subcontext start position.
*/
// Computor::context_pos	Computor::_subcontext_pos;

/**
 * Number of active subcontext.
*/
// uint_fast16_t			Computor::_active_context = 0;

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
	const value_ptr& value,
	const name_type& context_name
) {

	if (context_name.empty()) {
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
	} else {
		// Create a new context
		_subcontexts[context_name].push_back(std::make_pair(variable_name, value));
	}
/* 	if (_active_context > 0) {
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
 */
}

/**
 * Returns variable_name if in context.
*/
const Computor::value_ptr	Computor::find(
	const name_type& variable_name,
	const name_type& context_name
) {

	if (context_name.empty()) {
		// Variable set in global context
		for (context::const_reverse_iterator it = _memory.rbegin();
		it != _memory.rend();
		++it) {
			if (it->first == variable_name)
				return it->second;
		}
		return nullptr;
	} else {
		// Check if set in specific context
		context_map::const_iterator	context_it = _subcontexts.find(context_name);
		if (context_it == _subcontexts.end()) {
			// No such context
			return nullptr;
		}
		for (context::const_reverse_iterator it = context_it->second.rbegin();
		it != _memory.rend();
		++it) {
			if (it->first == variable_name)
				return it->second;
		}
		return nullptr;

	}

	// context::const_reverse_iterator	start;

	// if (!context_name.empty() || _active_context == 0)
	// 	start = _memory.rbegin();
	// else
	// 	start = _memory.rend() - _subcontext_pos.back();

	// for (context::const_reverse_iterator it = start;
	// it != _memory.rend();
	// ++it) {
	// 	if (it->first == variable_name)
	// 		return it->second;
	// }
	// return nullptr;
}

/**
 * Locks a new _context_pos.
*/
// void	Computor::create_context() {
	// _active_context += 1;
	// _subcontext_pos.push_back(_memory.size());
// }

/**
 * Flushes all temporary contexts.
*/
void	Computor::flush() {
	for (context_map::iterator it = _subcontexts.begin();
	it != _subcontexts.end();
	++it) {
		it->second.clear();
	}
	// while (_active_context > 0) {
	// 	_memory.resize(_subcontext_pos.back());
	// 	_subcontext_pos.pop_back();
	// 	--_active_context;
	// }
}

/**
 * Displays global context.
*/
void	Computor::show() const {
	using std::cout;
	cout << "==== Global context: ====\n";
	for (context::const_reverse_iterator it = _memory.rbegin();
	it != _memory.rend();
	++it) {
		cout << it->first << '=' << *it->second << NL;
	}

	for (context_map::const_iterator it = _subcontexts.begin();
	it != _subcontexts.end();
	++it) {
		cout << "-- context `" << it->first <<'`' << NL;
		for (context::const_reverse_iterator ite = it->second.rbegin();
		ite != it->second.rend();
		++ite)
			cout << ite->first << '=' << *ite->second << NL;
	}
	cout << "===========================\n";
}