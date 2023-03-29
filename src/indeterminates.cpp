/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:28 by etran             #+#    #+#             */
/*   Updated: 2023/03/29 13:42:43 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indeterminates.hpp"
#include "math.hpp"

const Rational	Indeterminates::unit = Rational(1);
const Rational	Indeterminates::neg_unit = Rational(-1);
const Rational	Indeterminates::null = Rational();
const Rational	Indeterminates::two = Rational(2);

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
	shared_rational factor,
	const std::string& var_name,
	Rational exponent
) {
	if (factor == nullptr) {
		factor = std::make_shared<Rational>(Indeterminates::unit);
	}
	key_type	weighted_value(var_name, exponent);
	key_set		keys;

	keys.insert(weighted_value);
	_datas[keys] = factor;
}

Indeterminates&	Indeterminates::operator=(const Indeterminates& x) {
	if (this->getMap() == x.getMap())
		return *this;
	_datas = x.getMap();
	return *this;
}

/* Arith Operators ---------------------------------------------------------- */

Indeterminates	Indeterminates::operator-() const {
	data_map			new_map(getMap());

	for (data_map::iterator it = new_map.begin();
	it != new_map.end();
	++it) {
		it->second = std::make_shared<Rational>(it->second->operator-());
	}
	return Indeterminates(new_map);
}

Indeterminates	Indeterminates::operator+(const Indeterminates& other) const {
	data_map				new_map(getMap());
	const data_map&			other_map = other.getMap();

	for (data_map::const_iterator other_it = other_map.begin();
	other_it != other_map.end();
	++other_it) {

		data_map::iterator	this_it = new_map.find(other_it->first);
		if (this_it != new_map.end()) {
			// If new_map has this key, add their factors
			Rational	new_factor(*this_it->second + *other_it->second);
			if (new_factor == Indeterminates::null) {
				// Remove it from map
				new_map.erase(this_it);
			} else {
				this_it->second = std::make_shared<Rational>(new_factor);
			}
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
	const data_map&				this_map = getMap();
	const data_map&				other_map = other.getMap();

	for (data_map::const_iterator this_element = this_map.begin();
	this_element != this_map.end();
	++this_element) {
		const key_set&		current_set = this_element->first;

		for (data_map::const_iterator other_element = other_map.begin();
		other_element != other_map.end();
		++other_element) {
			const key_set&	other_set = other_element->first;
			key_set			new_set;

			// Add every key from this_set, and do exponents collision
			for (key_set::const_iterator current_key = current_set.begin();
			current_key != current_set.end();
			++current_key) {
				key_type	new_key(*current_key);

				// Add to term if value is not 1
				if (current_key->variable_name != UNIT_VALUE) {
					Rational	other_exp = _setHas(other_set, current_key->variable_name);
					if (other_exp != Indeterminates::neg_unit) {
						new_key.exponent.operator+=(other_exp);
					}
					new_set.insert(new_key);
				}
			}

			// Now simply add every other term that wasn't added (from other set) except unit
			for (key_set::const_iterator current_key = other_set.begin();
			current_key != other_set.end();
			++current_key) {
				if (_setHas(new_set, current_key->variable_name) != Indeterminates::neg_unit) {
					// Already added
					continue;
				}
				if (current_key->variable_name != UNIT_VALUE)
					new_set.insert(*current_key);
			}

			// The result term is null
			if (new_set.empty())
				new_set.insert(key_type(UNIT_VALUE, Indeterminates::unit));

			shared_rational	new_factor;
			if (new_map.find(new_set) != new_map.end()) {
				// We already computed this value
				new_factor = std::make_shared<Rational>(
					*new_map[new_set] + *other_element->second
				);
			} else {
				new_factor = std::make_shared<Rational>(
					*this_element->second * *other_element->second
				);
			}
			new_map[new_set] = new_factor;
		}

	}
	return Indeterminates(new_map);
}

Indeterminates	Indeterminates::operator/(const Indeterminates& other) const {
	data_map			new_map(other.getMap());

	for (data_map::iterator it = new_map.begin();
	it != new_map.end();
	++it) {
		it->second = std::make_shared<Rational>(Indeterminates::unit / *it->second);
	}

	return this->operator*(Indeterminates(new_map));
}

Indeterminates	Indeterminates::operator^(const Indeterminates& other) const {
	// Support only trivial exponentiation
	if (!other._isUnit())
		throw ExpansionNotSupported();

	const Rational&	other_factor = *other.getMap().begin()->second;

	if (!other_factor.isInteger())
		throw math::operation_undefined();

	int	factor = static_cast<int>(other_factor.getVal());

	if (factor < 0)
		throw math::operation_undefined();

	Indeterminates	result(std::make_shared<Rational>(Indeterminates::unit));
	for (int i = 0; i < factor; ++i)
		result = result * Indeterminates(getMap());
	return result;
}

void	Indeterminates::show() const {
	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {

		std::cout << *it->second  << " * [";

		for (key_set::const_iterator ite = it->first.begin();
		ite != it->first.end();
		++ite) {
			std::cout << *ite << ',';
		}

		std::cout << ']' << NL;

	}
}

/**
 * Inject an indeterminate in another.
 * A bit overkill since the program won't support multiple indeterminates xd.
 *  
 * A(x) = ax2 + bx + c		
 * B(x) = dx2 + ex + f
 * 
 * The result it provides:
 *	A(B(x))	= a(dx2 + ex + f)2 + b(dx2 + ex + f) + c
 *			= ...
*/
Indeterminates	Indeterminates::inject(const Indeterminates& other) const {
	switch (getNbIndeterminates()) {
		case 0:
			return Indeterminates(*this);
		case 1:
			break;
		default:	// Can't support injection of too many indeterminates
			throw ExpansionNotSupported();
	}

	Indeterminates		result;
	const std::string	var_name = getMainIndeterminate();

	for (data_map::const_iterator this_element = _datas.begin();
	this_element != _datas.end();
	++this_element) {
		Indeterminates	new_term(this_element->second);
		
		Rational		exponent = _setHas(this_element->first, var_name);
		if (exponent != Indeterminates::neg_unit) {
			shared_rational	exp_ptr = std::make_shared<Rational>(exponent);
			new_term = (new_term * other) ^ Indeterminates(exp_ptr);
		}
		result = result + new_term;
	}
	return result;
}

/* Getter ------------------------------------------------------------------- */

/**
 * Return biggest exponent in the data_map.
*/
int	Indeterminates::getMaxExponent() const {
	Rational	max_exp = Indeterminates::null;

	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {
		const key_set&	current_set = it->first;

		for (key_set::const_iterator ite = current_set.begin();
		ite != current_set.end();
		++ite) {
			if (ite->exponent > Indeterminates::two) {
				return -1;
			} else if (ite->variable_name != UNIT_VALUE
				&& ite->exponent > max_exp) {
				max_exp = ite->exponent;
			}
		}
	}
	return static_cast<int>(max_exp.getVal());
}

/**
 * Returns the number of indeterminates.
*/
size_t	Indeterminates::getNbIndeterminates() const {
	std::set<std::string>		name_list;

	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {
		const key_set&	current_set = it->first;

		for (key_set::const_iterator ite = current_set.begin();
		ite != current_set.end();
		++ite) {
			if (ite->variable_name != UNIT_VALUE
			&& name_list.find(ite->variable_name) == name_list.end())
				name_list.insert(ite->variable_name);
		}
	}
	return name_list.size();
}

/**
 * Returns factor associated with a variable and specific exponent.
*/
Rational	Indeterminates::getFactorFrom(
	const std::string& variable_name,
	const Rational& exponent
) const {
	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {
		for (key_set::const_iterator ite = it->first.begin();
		ite != it->first.end();
		++ite) {
			if ((ite->variable_name == UNIT_VALUE && exponent == Indeterminates::null)
				|| (ite->variable_name == variable_name && ite->exponent == exponent))
				return *it->second;
		}
	}
	return Indeterminates::null;
}

const std::string	Indeterminates::getMainIndeterminate() const {
	for (data_map::const_iterator it = _datas.begin();
	it != _datas.end();
	++it) {
		for (key_set::const_iterator ite = it->first.begin();
		ite != it->first.end();
		++ite) {
			if (ite->variable_name != UNIT_VALUE)
				return ite->variable_name;
		} 
	}
	DEBUG("Shouldn't ever happen");
	throw std::exception(); //TODO
}

const Indeterminates::data_map&	Indeterminates::getMap() const {
	return _datas;
}

/* ========================================================================== */
/*                                   PRIVATE                                  */
/* ========================================================================== */

bool	Indeterminates::_isUnit() const {
	if (_datas.size() == 1) {
		if (_isSetUnit(_datas.begin()->first))
			return true;
	}
	return false;
}

/* ========================================================================== */
/*                                    OTHER                                   */
/* ========================================================================== */

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x) {
	typedef typename	Indeterminates::data_map	data_map;
	typedef typename	Indeterminates::key_set		key_set;

	if (x.getMap().empty())
		return (o << '0');
	for (data_map::const_reverse_iterator it = x.getMap().rbegin();
	it != x.getMap().rend();
	++it) {
		data_map::const_reverse_iterator	copy(it);
		const key_set&						set = it->first;
		bool								has_factor = false;

		// Display factor of set
		const Rational&	factor = *std::dynamic_pointer_cast<Rational>(it->second);
		if (!(factor == Indeterminates::neg_unit || factor == Indeterminates::unit)) {
			o << factor;
			has_factor = true;
		} else if (factor == Indeterminates::neg_unit) {
			o << '-';
		}

		// Display key_set
		for (key_set::const_iterator ite = set.begin();
		ite != set.end();
		++ite) {

			bool	display_exponent = ite->exponent != Indeterminates::unit;
			if (ite->variable_name == UNIT_VALUE && has_factor)
				continue;

			// Display weighted value
			if (display_exponent)
				o << '(';
			o << ite->variable_name;
			if (display_exponent)
				o << "^" << ite->exponent << ')';
		}

		// Inbetween terms
		if (++copy != x.getMap().rend()) {
			const Rational&	next_factor = *std::dynamic_pointer_cast<Rational>(copy->second);
			if (next_factor > Indeterminates::null)
				o << "+";
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
	// if (x.exponent != 1)
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
		o << *it << ',';
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

/**
 * Return true if the set == { <1, 1> }
*/
bool	_isSetUnit(const Indeterminates::key_set& set) {
	if (set.size() == 1) {
		if (set.begin()->variable_name == UNIT_VALUE
		&& set.begin()->exponent == Indeterminates::unit)
			return true;
	}
	return false;
}