/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:06:08 by etran             #+#    #+#             */
/*   Updated: 2023/03/06 17:14:20 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

/* Context ------------------------------------------------------------------ */
Computor::context	Computor::_memory;

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