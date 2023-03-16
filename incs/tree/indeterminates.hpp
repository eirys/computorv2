/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:22 by etran             #+#    #+#             */
/*   Updated: 2023/03/16 12:15:42 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDETERMINATES_HPP
# define INDETERMINATES_HPP

# include <set>
# include <map>

# include "itype.hpp"
# include "rational.hpp"

class Indeterminates {
	public:
		struct WeigthedValue {
			/* Constructor ------------------------------------------------------------- */
			WeigthedValue(const std::string& var_name, Rational exponent):
				variable_name(var_name),
				exponent(exponent) {}

			/* Attributes -------------------------------------------------------------- */
			const std::string	variable_name;	// address of the shared_ptr
			Rational			exponent;		// exponent

			bool	operator==(const WeigthedValue& rhs) const {
				return variable_name == rhs.variable_name && exponent == rhs.exponent;
			}

			bool	operator<(const WeigthedValue& rhs) const {
				return variable_name < rhs.variable_name && exponent < rhs.exponent;
			}
		};

		typedef typename	IType::shared_itype							shared_itype;
		typedef				WeigthedValue								key_type;
		typedef				std::set<key_type>							key_set;
		typedef				std::map<key_set, shared_itype>				data_map;
		typedef				std::pair<key_set, shared_itype>			data_map_element;

		/* Constructor ------------------------------------------------------------ */
		Indeterminates(
			shared_itype factor,
			Rational exponent = Rational(1),
			const std::string& var_name = std::string("1")
		);

		Indeterminates(const Indeterminates& x);

		/* Destructor ------------------------------------------------------------- */
		virtual ~Indeterminates();

		/* Functions -------------------------------------------------------------- */
		// Indeterminates&		operator+=(const Indeterminates& other);
		Indeterminates		operator+(const Indeterminates& other) const;
		Indeterminates		operator-(const Indeterminates& other) const;
		Indeterminates		operator*(const Indeterminates& other) const;
		Indeterminates		operator/(const Indeterminates& other) const;
		Indeterminates		operator+(const Indeterminates& other) const;
		Indeterminates		operator%(const Indeterminates& other) const;

		/* Getter ----------------------------------------------------------------- */
		const data_map&		getMap() const;

	private:
		data_map			_datas;
};

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x);

#endif