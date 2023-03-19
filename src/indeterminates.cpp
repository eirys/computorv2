/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:28 by etran             #+#    #+#             */
/*   Updated: 2023/03/19 11:30:48 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indeterminates.hpp"
#include "math.hpp"

const Rational	Indeterminates::unit = Rational(1);
const Rational	Indeterminates::neg_unit = Rational(-1);

/* ========================================================================== */
/*                                   PUBLIC                                   */
/* ========================================================================== */

Indeterminates::Indeterminates() {}

Indeterminates::~Indeterminates() {}

Indeterminates::Indeterminates(const data_map& map):
	_datas(map) {}

Indeterminates::Indeterminates(const Indeterminates& x):
	_datas(x.getMap()) {}

Indeterminates::Indeterminates(
	shared_itype factor, // always a rational
	const std::string& var_name,
	Rational exponent
) {
	if (factor != nullptr
	&& std::dynamic_pointer_cast<Rational>(factor) == nullptr) {
		throw NotARational();
	} else if (factor == nullptr) {
		factor = shared_itype(new Rational(1));
	}
	key_type	weighted_value(var_name, exponent);
	key_set		keys;

	keys.insert(weighted_value);
	_datas[keys] = factor;
}

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
	data_map				new_map(getMap());
	const data_map&			other_map = other.getMap();

	for (data_map::const_iterator other_it = other_map.begin();
	other_it != other_map.end();
	++other_it) {
		data_map::iterator	this_it = _find(new_map, other_it->first);
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
				Rational	other_exp = _setHas(other_set, current_key->variable_name);
				if (other_exp != null) {
					new_key.exponent.operator+=(other_exp);
				}
				new_set.insert(new_key);
			}

			// Now simply add every other key that wasn't added (from other set)
			for (key_set::const_iterator current_key = other_set.begin();
			current_key != other_set.end();
			++current_key) {
				if (_setHas(new_set, current_key->variable_name) != null) {
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

Indeterminates	Indeterminates::operator%(const Indeterminates& other) const {
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

	for (data_map::const_iterator it = x.getMap().begin();
	it != x.getMap().end();
	++it) {
		data_map::const_iterator	copy(it);
		const key_set&				set = it->first;

		// Display factor of set
		const Rational&	factor = *std::dynamic_pointer_cast<Rational>(it->second);
		if (it == x.getMap().begin()
			|| !(factor == Indeterminates::unit || factor == Indeterminates::neg_unit))
			o << factor;

		// Display key_set
		if (!_isSetUnit(it->first)) {
			for (key_set::const_iterator ite = set.begin();
			ite != set.end();
			++ite) {
				// Display weighted value
				if (ite->variable_name == UNIT_VALUE) {
					o << Indeterminates::unit;
				} else {
					o << ite->variable_name;
				}
				if (ite->exponent != Indeterminates::unit)
					o << " ^ " << ite->exponent;
			}
		}

		// Inbetween terms
		if (++copy != x.getMap().end()) {
			const Rational&	next_factor = *std::dynamic_pointer_cast<Rational>(copy->second);
			if (next_factor <= Indeterminates::neg_unit)
				o << " - ";
			else
				o << " + ";
		}
	}
	return o;
}

/**
 * TODO: remove
 * Display a WeightedValue:
 * 	- variable
 * 	- exponent
*/
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_type& x) {
	if (x.variable_name == UNIT_VALUE) {
		o << '1';
	} else {
		o << x.variable_name;
	}
	if (x.exponent != 1)
		o << " ^ " << x.exponent;
	return o;
}

/**
 * TODO: remove
 * Display every key_type of a set.
*/
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_set& x) {
	for (Indeterminates::key_set::const_iterator it = x.begin();
	it != x.end();
	++it)
		o << *it;
	return o;
}

/**
 * TODO: remove
 * Display a pair:
 * 	- key_set,
 * 	- shared_itype
*/
std::ostream&	operator<<(std::ostream& o, const Indeterminates::data_map_element& x) {
	const Rational& r = *std::dynamic_pointer_cast<Rational>(x.second);
	bool	is_factor_unit = r == Indeterminates::unit || r == Indeterminates::neg_unit;
	bool	is_value_unit = _isSetUnit(x.first);
	if (!is_factor_unit && !is_value_unit) {
		o << *x.second << x.first;
	} else if (!is_factor_unit) {
		o << *x.second;
	} else {
		o << x.first;
	}
	return o;
}

/* Utils -------------------------------------------------------------------- */

/**
 * Returns value of exponent if the set contains the expected name.
 * Else returns -1.
*/
Rational	_setHas(
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
	return Indeterminates::neg_unit;
}

Indeterminates::data_map::iterator	_find(
	Indeterminates::data_map& map,
	const Indeterminates::key_set& set
) {
	for (Indeterminates::data_map::iterator it = map.begin();
	it != map.end();
	++it) {
		if (it->first.size() != set.size())
			continue;

		Indeterminates::key_set::const_iterator	it1 = it->first.begin();
		Indeterminates::key_set::const_iterator	it2 = set.begin();

		while (it1 != it->first.end()) {
			if (!(*it1 == *it2))
				break;
			++it1;
			++it2;
		}
		if (it1 == it->first.end())
			return it;
	}
	return map.end();
}

/**
 * Return true if the set = { <1, 1> }
*/
bool	_isSetUnit(const Indeterminates::key_set& set) {
	if (set.size() == 1) {
		if (set.begin()->variable_name == UNIT_VALUE
		&& set.begin()->exponent == Indeterminates::unit)
			return true;
	}
	return false;
}