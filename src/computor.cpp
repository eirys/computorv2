/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/09 15:24:54 by etran            ###   ########.fr       */
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

void	Computor::push(const std::string& name, const value_ptr& value) {
	_memory.push(std::make_pair(name, value));
}

const Computor::value_ptr	Computor::find(const std::string& name) {
	context		cpy(_memory);

	while (!cpy.empty()) {
		const variable&	top = cpy.top();
		if (top.first == name) {
			return top.second;
		}
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
}

void	Computor::push_context(
	const Identifier& context_name,
	const name_type& name,
	const value_ptr& value
) {
	context_map::iterator	local = _local_memory.find(context_name);
	if (local != _local_memory.end()) {
		// Il existe deja un contexte avec ce nom
		if (local->second.)
	} else {
		// Il n'y en a pas
		Computor::variable	var_pair = std::make_pair(name, value);
		_local_memory[context_name] = context();
	}
}

void	Computor::