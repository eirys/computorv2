/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:28 by etran             #+#    #+#             */
/*   Updated: 2023/03/16 14:03:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indeterminates.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Indeterminates::Indeterminates (
	shared_itype factor,
	Rational exponent,
	const std::string& var_name
) {
	key_type	weighted_value(var_name, exponent);
	key_set		keys;

	keys.insert(weighted_value);
	_datas[keys] = factor;
}

Indeterminates::Indeterminates(const Indeterminates& x):
	_datas(x.getMap()) {}

Indeterminates::~Indeterminates() {}

/* Operators ---------------------------------------------------------------- */

Indeterminates	Indeterminates::operator+(const Indeterminates& other) const {
	Indeterminates				copy(*this);
	data_map&					this_map = copy._datas;
	const data_map&				other_map = other.getMap();
	data_map::iterator			this_it(this_map.begin());
	data_map::const_iterator	other_it(other_map.begin());
	std::list<data_map_element>	to_add;

	while (this_it != _datas.end() && other_it != other_map.end()) {
		// For each element of this map
		if (this_it->first == other_it->first) {
			// If the set already exists, just add factors
			this_it->second = (*this_it->second + other_it->second)->clone();
		} else {
			// Else, save the pair to be added later
			to_add.push_front(*other_it);
		}
		++this_it;
		++other_it;
	}
	this_map.insert(to_add.begin(), to_add.end());
	return copy;
}

Indeterminates	Indeterminates::operator-(const Indeterminates& other) const {
	(void)other;
	return *this;
}

/* Getter ------------------------------------------------------------------- */

const Indeterminates::data_map&	Indeterminates::getMap() const {
	return _datas;
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x) {
	typedef typename	Indeterminates::data_map	data_map;
	typedef typename	Indeterminates::key_set		key_set;

	const data_map&	map = x.getMap();

	for (data_map::const_iterator it = map.begin();
	it != map.end();
	++it) {
		data_map::const_iterator	copy(it);
		const key_set&	current_set = it->first;
		o << *it->second << " * (";
		for (key_set::const_iterator ite = current_set.begin();
		ite != current_set.end();
		++ite) {
			key_set::const_iterator	copy2(ite);
			o << ite->variable_name << " ^ " << ite->exponent;
			if (++copy2 != current_set.end())
				o << " + ";
		}
		o << ")";
		if (++copy != map.end())
			o << " + ";
	}
	return o;
}