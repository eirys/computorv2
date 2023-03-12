/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/12 14:17:38 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */

/**
 * Global scope context.
*/
Computor::context		Computor::_memory;

/**
 * Specific context.
*/
Computor::context_map	Computor::_local_memory;

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
		_memory.push(std::make_pair(variable_name, value));
	} else {
		variable	var = std::make_pair(variable_name, value);
		_local_memory[context_name].push(var);
	}
}

/**
 * Returns variable_name if in context.
*/
const Computor::value_ptr	Computor::find(
	const name_type& variable_name,
	const name_type& context_name
) {
	context cpy;

	if (context_name.empty()) {
		cpy = _memory;
	} else {
		context_map::const_iterator	memory = _local_memory.find(context_name);
		if (memory == _local_memory.end())
			return nullptr;
		cpy = memory->second;
	}
	while (!cpy.empty()) {
		const variable&	top = cpy.top();
		if (top.first == variable_name)
			return top.second;
		cpy.pop();
	}
	return nullptr;
}

/**
 * Flushes all temporary contexts.
*/
void	Computor::flush() {
	_local_memory.clear();
}

/**
 * Displays every contexts.
*/
void	Computor::show() const {
	context		cpy(_memory);

	std::cout << "Global context:\n";
	while (!cpy.empty()) {
		std::cout << cpy.top().first << '=' << *cpy.top().second << NL;
		cpy.pop();
	}

	for (context_map::const_iterator it = _local_memory.begin();
		it != _local_memory.end();
		++it
	) {
		std::cout << "Context `" << it->first << '\'' << NL;
		context	current(it->second);
		while (!current.empty()) {
			std::cout << current.top().first << '=' << *current.top().second << NL;
			current.pop();
		}
		std::cout <<NL;
	}

}