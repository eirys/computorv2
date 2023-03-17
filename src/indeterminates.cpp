/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:28 by etran             #+#    #+#             */
/*   Updated: 2023/03/17 19:18:15 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indeterminates.hpp"

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Indeterminates::Indeterminates(
	shared_itype factor,
	Rational exponent,
	const std::string& var_name
) {
	key_type	weighted_value(var_name, exponent);
	key_set		keys;

	keys.insert(weighted_value);
	_datas[keys] = factor;
}

Indeterminates::Indeterminates(const data_map& map):
	_datas(map) {}

Indeterminates::Indeterminates(const Indeterminates& x):
	_datas(x.getMap()) {}

Indeterminates::~Indeterminates() {}

/* Operators ---------------------------------------------------------------- */

Indeterminates	Indeterminates::operator-() const {
	data_map			new_map(getMap());

	for (data_map::iterator it = new_map.begin();
	it != new_map.end();
	++it) {
		it->second = (it->second->negate())->clone(); 
	}
	return Indeterminates(new_map);
}

Indeterminates	Indeterminates::operator+(const Indeterminates& other) const {
	data_map			new_map(getMap());
	const data_map&		other_map = other.getMap();

	for (data_map::const_iterator other_it = other_map.begin();
	other_it != other_map.end();
	++other_it) {
		data_map::iterator	this_it = new_map.find(other_it->first);

		if (this_it != new_map.end()) {
			// If new_map has this key, add their factors
			this_it->second = (*this_it->second + other_it->second)->clone();
		} else {
			// Insert the new set
			new_map.insert(*other_it);
		}
	}
	return Indeterminates(new_map);
}

Indeterminates	Indeterminates::operator-(const Indeterminates& other) const {
	Indeterminates	other_copy = other.operator-();

	return this->operator+(other_copy);
}

Indeterminates	Indeterminates::operator*(const Indeterminates& other) const {
	data_map					new_map;
	Rational					null(-1);

	const data_map&				this_map = getMap();
	const data_map&				other_map = other.getMap();

	for (data_map::const_iterator this_it = this_map.begin();
	this_it != this_map.end();
	++this_it) {
		const key_set&		current_set = this_it->first;

		for (data_map::const_iterator other_it = other_map.begin();
		other_it != other_map.end();
		++other_it) {
			const key_set&	other_set = other_it->first;
			key_set			new_set;

			// Add every key from this_set, and do exponents collision
			for (key_set::const_iterator current_key = current_set.begin();
			current_key != current_set.end();
			++current_key) {
				key_type	new_key(*current_key);
				Rational	other_exp = _set_has(other_set, current_key->variable_name);
				if (other_exp != null) {
					new_key.exponent.operator+=(other_exp);
				}
				new_set.insert(new_key);
			}

			// Now simply add every other key that wasn't added (from other set)
			for (key_set::const_iterator current_key = other_set.begin();
			current_key != other_set.end();
			++current_key) {
				if (_set_has(new_set, current_key->variable_name) != null) {
					continue;
				}
				new_set.insert(*current_key);
			}

			new_map[new_set] = (*this_it->second * other_it->second)->clone();
		}

	}
	return Indeterminates(new_map);
}

Indeterminates	Indeterminates::operator/(const Indeterminates& other) const {
	(void)other;
	return Indeterminates(*this);
}
Indeterminates	Indeterminates::operator^(const Indeterminates& other) const {
	(void)other;
	return Indeterminates(*this);
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

/**
 * Returns value of exponent if the set contains the expected name.
 * Else returns -1.
*/
Rational	_set_has(
	const Indeterminates::key_set& set,
	const std::string& variable_name
) {
	typedef Indeterminates::key_set		key_set;

	for (key_set::const_iterator it = set.begin();
	it != set.end();
	++it) {
		if (it->variable_name == variable_name)
			return it->exponent;
	}
	return Rational(-1);
}