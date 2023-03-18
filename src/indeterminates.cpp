/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:28 by etran             #+#    #+#             */
/*   Updated: 2023/03/18 18:58:39 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indeterminates.hpp"

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
	typedef std::list<data_map_element>		data_list;

	data_map				new_map(getMap());
	const data_map&			other_map = other.getMap();

	data_list				to_insert;

	for (data_map::const_iterator other_it = other_map.begin();
	other_it != other_map.end();
	++other_it) {
		// Search for current key in new_map
		data_map::iterator	this_it = _find(new_map, other_it->first);

		DEBUG("Other set:");
		std::cout << *other_it <<NL;

		if (this_it != new_map.end()) {
			// If new_map has this key, add their factors
			DEBUG("found value");
			this_it->second = (*this_it->second + other_it->second)->clone();
			// this_it->second = _add_factors(this_it->second, other_it->second);
		} else {
			// Insert the new set
			DEBUG("inserted");
			to_insert.push_back(*other_it);
		}
	}
	for (data_list::const_iterator it = to_insert.begin();
	it != to_insert.end();
	++it) {
		DEBUG("inserting :\n"<<*it);
		key_set		key_copy(it->first);
		new_map[key_copy] = it->second;
		DEBUG("Inserted: " << key_copy << " =  "<< *new_map[key_copy]);
	}
	// new_map.insert(to_insert.begin(), to_insert.end());

	DEBUG(NL << "New map:\n" << new_map << NL);

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

Indeterminates	Indeterminates::operator%(const Indeterminates& other) const {
	(void)other;
	return Indeterminates(*this);
}

/* Getter ------------------------------------------------------------------- */

const Indeterminates::data_map&	Indeterminates::getMap() const {
	return _datas;
}

/* Tools -------------------------------------------------------------------- */

void	Indeterminates::show() const {
	using std::cout;

	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {

		if (it->second == nullptr) {
			cout << "null";
		} else {
			cout << *it->second;
		}
		cout << ":\n";

		for (key_set::const_iterator ite = it->first.begin();
		ite != it->first.end();
		++ite) {
			cout << "- [" << ite->variable_name << "] ^ " << ite->exponent << NL;
		}

		cout << NL;
	}
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x) {
	for (Indeterminates::data_map::const_iterator it = x.getMap().begin();
	it != x.getMap().end();
	++it) {
		Indeterminates::data_map::const_iterator	copy(it);
		o << *it;
		if (++copy != x.getMap().end())
			o << " + ";
	}
	return o;
}

std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_type& x) {
	if (x.variable_name == UNIT_VALUE) {
		o << "1";
	} else {
		o << x.variable_name;
	}
	if (x.exponent != 1)
		o << " ^ " << x.exponent;
	return o;
}

std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_set& x) {
	for (Indeterminates::key_set::const_iterator it = x.begin();
	it != x.end();
	++it) {
		// Indeterminates::key_set::const_iterator	copy(it);
		// if (it == x.begin())
			// o << '(';
		o << *it;
		// if (++copy == x.end())
			// o << ')';
	}
	return o;
}

std::ostream&	operator<<(std::ostream& o, const Indeterminates::data_map_element& x) {
	if (*std::dynamic_pointer_cast<Rational>(x.second) != Rational(1))
		o << *x.second << " * ";
	o << x.first;
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

Indeterminates::shared_itype	_add_factors(
	const Indeterminates::shared_itype& val_ptr1,
	const Indeterminates::shared_itype& val_ptr2
) {
	if (val_ptr1 != nullptr && val_ptr2 != nullptr)
		return (*val_ptr1 + val_ptr2)->clone();
	else if (val_ptr1 != nullptr)
		return val_ptr1->clone();
	else
		return val_ptr2->clone();
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