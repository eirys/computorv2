/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:22 by etran             #+#    #+#             */
/*   Updated: 2023/03/18 22:21:54 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDETERMINATES_HPP
# define INDETERMINATES_HPP

# include <set>
# include <map>

# include "itype.hpp"
# include "rational.hpp"

# define UNIT_VALUE "1"

class Indeterminates {
	public:
		struct WeigthedValue {
			WeigthedValue(const std::string& var_name, Rational exponent):
				variable_name(var_name),
				exponent(exponent) {}

			const std::string	variable_name;
			Rational			exponent;

			bool	operator==(const WeigthedValue& rhs) const {
				return variable_name == rhs.variable_name && exponent == rhs.exponent;
			}
			bool	operator<(const WeigthedValue& rhs) const {
				if (variable_name != rhs.variable_name)
					return variable_name < rhs.variable_name;
				return exponent < rhs.exponent;
			}
		};

		typedef typename	IType::shared_itype							shared_itype;
		typedef				WeigthedValue								key_type;
		typedef				std::set<key_type>							key_set;

		typedef				std::map<key_set, shared_itype>				data_map;
		typedef				std::pair<key_set, shared_itype>			data_map_element;

		Indeterminates();
		Indeterminates(const data_map& x);
		Indeterminates(const Indeterminates& x);
		Indeterminates(
			shared_itype factor,
			const std::string& var_name = std::string(UNIT_VALUE),
			Rational exponent = Rational(1)
		);

		virtual ~Indeterminates();

		/* Functions -------------------------------------------------------------- */

		Indeterminates			operator-() const;
		Indeterminates			operator+(const Indeterminates& other) const;
		Indeterminates			operator-(const Indeterminates& other) const;
		Indeterminates			operator*(const Indeterminates& other) const;
		Indeterminates			operator/(const Indeterminates& other) const;
		Indeterminates			operator^(const Indeterminates& other) const;
		Indeterminates			operator%(const Indeterminates& other) const;

		/* Getter ----------------------------------------------------------------- */
		const data_map&			getMap() const;

		/* Exception -------------------------------------------------------------- */
		class NotARational: public std::exception {
			public:
				const char* what() const throw() {
					return "Not a rational";
				}
		};

		/* Static Value ----------------------------------------------------------- */
		static const Rational	unit;
		static const Rational	neg_unit;

	private:
		data_map				_datas;
};

/* Other -------------------------------------------------------------------- */

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x);
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_type& x);
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_set& x);
std::ostream&	operator<<(
	std::ostream& o,
	const Indeterminates::data_map_element& x
);

/* Utils -------------------------------------------------------------------- */

Rational		_setHas(
	const Indeterminates::key_set& set,
	const std::string& variable_name
);

Indeterminates::data_map::iterator	_find(
	Indeterminates::data_map& map,
	const Indeterminates::key_set& key
);

bool	_isFactorUnit(const Indeterminates::shared_itype& set);
bool	_isSetUnit(const Indeterminates::key_set& set);

#endif