/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/11 19:31:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */
Computor::context		Computor::_memory;
Computor::context_map	Computor::_local_memory;

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Computor::Computor() {}

Computor::~Computor() {}

/* Function ----------------------------------------------------------------- */

void	Computor::push(
	const name_type& variable_name,
	const value_ptr& value,
	const name_type& context_name
) {
	if (context_name.empty()) {
		LOG("Pushing value to global context");
		_memory.push(std::make_pair(variable_name, value));
	} else {
		LOG("Pushing value " << variable_name << "=" << *value << " to context: " << context_name);
		// context_map::iterator	memory = _local_memory.find(context_name);
		// if (memory == _local_memory.end())
			// throw ContextInexistent();
		variable	var = std::make_pair(variable_name, value);
		_local_memory[context_name].push(var);
	}
}

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

void	Computor::show() const {
	context		cpy(_memory);

	std::cout << "==== Current state: ====\n";
	while (!cpy.empty()) {
		std::cout << cpy.top().first << '=' << *cpy.top().second << NL;
		cpy.pop();
	}

	for (context_map::const_iterator it = _local_memory.begin();
		it != _local_memory.end();
		++it
	) {
		std::cout << '\'' << it->first << '\'' << NL;
		context	current(it->second);
		while (!current.empty()) {
			std::cout << current.top().first << '=' << *current.top().second << NL;
			current.pop();
		}
	}

}

// void	Computor::push_context(
// 	const Identifier& context_name,
// 	const name_type& name,
// 	const value_ptr& value
// ) {
// 	context_map::iterator	local = _local_memory.find(context_name);
// 	if (local != _local_memory.end()) {
// 		// Il existe deja un contexte avec ce nom
// 		if (local->second.)
// 	} else {
// 		// Il n'y en a pas
// 		Computor::variable	var_pair = std::make_pair(name, value);
// 		_local_memory[context_name] = context();
// 	}
// }