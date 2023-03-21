/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/21 18:15:38 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"
#include "indeterminates.hpp"
#include "solver.hpp"

/* Context ------------------------------------------------------------------ */

/**
 * Global scope context.
*/
Computor::context		Computor::_memory;

/**
 * Specific named subcontexts.
*/
Computor::context_map	Computor::_subcontexts;

bool					Computor::_equality = false;

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
	name_type		variable_name_lower = utils::toLower(variable_name);

	if (context_name.empty()) {
		// Global context
		// Erase previous occurence
		for (context::reverse_iterator it = _memory.rbegin();
		it != _memory.rend();
		++it) {
			if (it->first.first == variable_name_lower) {
				it->second = value;
				return;
			}
		}
		name_duo	names = std::make_pair(variable_name_lower, variable_name);
		_memory.push_back(std::make_pair(names, value));
	} else {
		name_duo	names = std::make_pair(utils::toLower(context_name), context_name);

		// Find expected context
		context_map::iterator	context_list = _subcontexts.find(names);
		if (context_list == _subcontexts.end())
			throw std::exception();
		for (subcontext::iterator it = context_list->second.begin();
		it != context_list->second.end();
		++it) {
			if (it->first.first == variable_name_lower) {
				// Erase previous occurence
				it->second = value;
				return;
			}
		}
		throw UnknownFunctionElement(variable_name);
	}
}

/**
 * Returns variable_name if in context.
*/
const Computor::value_ptr	Computor::find(
	const name_type& variable_name,
	const name_type& context_name
) {
	name_type	lowered_name = utils::toLower(variable_name);

	if (context_name.empty()) {
		// Variable set in global context
		for (context::const_reverse_iterator it = _memory.rbegin();
		it != _memory.rend();
		++it) {
			if (it->first.first == lowered_name)
				return it->second;
		}
		return nullptr;
	} else {
		name_duo	context_names = std::make_pair(
										utils::toLower(context_name),
										context_name
									);
		// Check if set in specific context
		context_map::const_iterator	context_it = _subcontexts.find(context_names);
		if (context_it == _subcontexts.end()) {
			// No such context
			return nullptr;
		}
		for (subcontext::const_iterator it = context_it->second.begin();
		it != context_it->second.end();
		++it) {
			if (it->first.first == lowered_name)
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
	name_duo	context_names = std::make_pair(
								utils::toLower(context_name),
								context_name
							);
	name_duo	variable_names = std::make_pair(
		utils::toLower(variable_name),
		variable_name
	);

	context_map::iterator	context = _subcontexts.find(context_names);
	if (context != _subcontexts.end()) {
		// Context already exists: update variable name
		context->second.clear();
	}

	variable	var(variable_names, nullptr);
	_subcontexts[context_names].push_front(var);
}

/**
 * Alerts that the following interminate is an expression to solve.
*/
void	Computor::create_equality() {
	_solve = true;
	_equality = true;
}

void	Computor::solve(const Indeterminates& expression) {
	typedef	Indeterminates::data_map	data_map;

	using std::cout;
	using std::cerr;

	if (_equality) {
		Solver	solver(expression);
		_solve = solver.solve();
	}
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
	_equality = false;
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
			if (it->first.first == ite->first.first) {
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
		cout << it->first.second << '=' << *it->second << NL;
	}

	for (context_map::const_iterator it = _subcontexts.begin();
	it != _subcontexts.end();
	++it) {
		cout << "-- context `" << it->first.second << "` --" << NL;
		for (subcontext::const_iterator ite = it->second.begin();
		ite != it->second.end();
		++ite) {
			cout << ite->first.second;
			if (ite->second != nullptr)
				cout << '=' << *ite->second << NL;
			else
				cout << NL;
		}
	}
	cout << "===========================\n";
}