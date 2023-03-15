/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/15 21:37:20 by eli              ###   ########.fr       */
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
		// Global context
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
		// Check if context is valid before doing anything
		bool	valid = false;
		for (context::const_iterator it =_memory.begin();
		it != _memory.end();
		++it) {
			if (it->first == context_name) {
				valid = true;
				break;
			}
		}
		if (!valid)
			throw std::exception(); //TODO

		// Find expected context
		context_map::iterator	context_list = _subcontexts.find(context_name);
		if (context_list == _subcontexts.end())
			throw std::exception();	//TODO
		for (subcontext::iterator it = context_list->second.begin();
		it != context_list->second.end();
		++it) {
			if (it->first == variable_name) {
				// Erase previous occurence
				it->second = value;
				return;
			}
		}
		throw UnknownFunctionElement(variable_name);
		// _subcontexts[context_name].push_back(std::make_pair(variable_name, value));
	}
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
		for (subcontext::const_iterator it = context_it->second.begin();
		it != context_it->second.end();
		++it) {
			if (it->first == variable_name)
				return it->second;
		}
		return nullptr;
	}
}

/**
 * Locks a new _subcontext list.
*/
void	Computor::create_context(
	const name_type& context_name,
	const name_type& variable_name
) {
	if (_subcontexts.find(context_name) != _subcontexts.end()) {
		// Context already exists
		return;
	}
	variable	var(variable_name, nullptr);
	_subcontexts[context_name].push_front(var);
}

/**
 * Flushes all temporary contexts.
*/
void	Computor::flush() {
	for (context_map::iterator it = _subcontexts.begin();
	it != _subcontexts.end();
	++it) {
		for (subcontext::iterator ite = it->second.begin();
		ite != it->second.end();
		++ite) {
			ite->second = nullptr;
		}
	}
}

/**
 * Removes invalid contexts.
*/
void	Computor::prune() {
	context_map::iterator	it = _subcontexts.begin();

	bool	valid;

	while (it != _subcontexts.end()) {
		valid = false;
		// For every subcontext
		for (context::const_iterator ite = _memory.begin();
		ite != _memory.end();
		++ite) {
			// For every memory element
			if (it->first == ite->first) {
				// Subcontext is valid
				valid = true;
				break;
			}
		}
		if (!valid) {
			_subcontexts.erase(it++);
		} else {
			++it;
		}
	}
}


/// TODO: For future menu
/**
 * Resets memory.
*/
void	Computor::reset() {
	return;
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
		cout << "-- context `" << it->first << "` --" << NL;
		for (subcontext::const_iterator ite = it->second.begin();
		ite != it->second.end();
		++ite)
			cout << ite->first << '=' << *ite->second << NL;
	}
	cout << "===========================\n";
}