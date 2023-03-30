/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:22 by etran             #+#    #+#             */
/*   Updated: 2023/03/30 14:54:36 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDETERMINATES_HPP
# define INDETERMINATES_HPP

# include <set>
# include <map>

# include "itype.hpp"
# include "rational.hpp"

# define UNIT_VALUE "1"

/**
 * The developped expression.
 * 
 * key_set			: an indeterminated factor OR unit value (ex: `b`, `a^2`, `1`)
 * key_type			: a set of indeterminated factors (ex: `ab^2`)
 * data_map_element	: a pair of <key_type, shared_rational>
 * 
 * ex:
 * 	a+2-3+a = 2a - 1
 * 	(a*b)^2 = 2ab + a^2 + b^2
*/
class Indeterminates {
	public:
		struct WeigthedValue {
			WeigthedValue(const std::string& var_name, Rational exponent):
				variable_name(var_name),
				exponent(exponent) {}
			bool	operator==(const WeigthedValue& rhs) const {
				return variable_name == rhs.variable_name && exponent == rhs.exponent;
			}
			bool	operator<(const WeigthedValue& rhs) const {
				if (variable_name != rhs.variable_name)
					return variable_name < rhs.variable_name;
				return exponent < rhs.exponent;
			}
			
			const std::string	variable_name;
			Rational			exponent;
		};

		typedef typename	IType::shared_itype							shared_itype;
		typedef				std::shared_ptr<Rational>					shared_rational;
		typedef				WeigthedValue								key_type;
		typedef				std::set<key_type>							key_set;

		typedef				std::map<key_set, shared_rational>			data_map;
		typedef				std::pair<key_set, shared_rational>			data_map_element;

		Indeterminates();
		Indeterminates(const data_map& x);
		Indeterminates(const Indeterminates& x);
		Indeterminates(
			shared_rational factor,
			const std::string& var_name = std::string(UNIT_VALUE),
			Rational exponent = Indeterminates::unit
		);

		Indeterminates&	operator=(const Indeterminates& x);

		virtual ~Indeterminates();

		/* Arith Operators -------------------------------------------------------- */
		Indeterminates			operator-() const;
		Indeterminates			operator+(const Indeterminates& other) const;
		Indeterminates			operator-(const Indeterminates& other) const;
		Indeterminates			operator*(const Indeterminates& other) const;
		Indeterminates			operator/(const Indeterminates& other) const;
		Indeterminates			operator^(const Indeterminates& other) const;
		Indeterminates			inject(const Indeterminates& other) const;

		/* Tools ------------------------------------------------------------------ */
		size_t					getNbIndeterminates() const;
		int						getMaxExponent() const;
		Rational				getFactorFrom(
									const std::string& variable_name,
									const Rational& exponent
								) const;
		const data_map&			getMap() const;
		const std::string		getMainIndeterminate() const;

		#ifdef __DEBUG
		void					show() const;
		#endif

		/* Exception -------------------------------------------------------------- */
		class ExpansionNotSupported: public std::exception {
			public:
				const char* what() const throw() {
					return "This expression's expansion is not supported";
				}
		};

		/* Static Value ----------------------------------------------------------- */
		static const Rational	unit;
		static const Rational	neg_unit;
		static const Rational	null;
		static const Rational	two;

	private:
		data_map				_datas;

		bool					_isUnit() const;
};

/* Other -------------------------------------------------------------------- */

std::ostream&	operator<<(std::ostream& o, const Indeterminates& x);

#ifdef __DEBUG
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_type& x);
std::ostream&	operator<<(std::ostream& o, const Indeterminates::key_set& x);
std::ostream&	operator<<(
	std::ostream& o,
	const Indeterminates::data_map_element& x
);
#endif

/* Utils -------------------------------------------------------------------- */

Rational		_setHas(
	const Indeterminates::key_set& set,
	const std::string& variable_name
);

bool			_isSetUnit(const Indeterminates::key_set& set);

#endif