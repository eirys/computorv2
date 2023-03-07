/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:22 by etran             #+#    #+#             */
/*   Updated: 2023/03/07 18:43:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDETERMINATES_HPP
# define INDETERMINATES_HPP

# include <set>
# include <map>

# include "itype.hpp"

struct VariableWithExponent {
	/* Constructor ------------------------------------------------------------- */
	VariableWithExponent(const std::string& var_name, int exponent):
		variable_name(var_name),
		exponent(exponent) {}

	/* Attributes -------------------------------------------------------------- */
	const std::string	variable_name; // address of the shared_ptr
	int					exponent; // exponent
}

class KeysetComparator {
	typedef				VariableWithExponent					key_type;
	typedef				std::set<key_type>						key_set;

	bool operator() (const key_set& lhs, const key_set& rhs) const {
		return std::equal(lhs, rhs);
	}
}

class Indeterminates {
	public:
		typedef typename	IType::shared_itype								shared_itype;
		typedef				VariableWithExponent							key_type;

		typedef				std::set<key_type>								key_set;
		typedef				std::map<key_set, shared_itype, key_comparator>	data_map;

		/* Constructor ------------------------------------------------------------ */
		Indeterminates(const std::string& var_name,
			int exponent, shared_itype value) {
				key_type	key(var_name, exponent);
				_datas[key] = value;
			}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Indeterminates() {}

		/* Functions -------------------------------------------------------------- */
		Indeterminates	operator+(const Indeterminates& other) const {
			const data_map&		other_map = other.getMap();

			for (data_map::const_iterator it = other_map.begin();
			it != other_map.end();
			++it) {
				_datas[it->first] = it->second;
			}
		}

		const data_map&		getMap() const {
			return _datas;
		}

	private:
		data_map			_datas;

		bool				_contains(const key_set& other_set) const {
			for (data_map::const_iterator it = _datas.begin();
			it != _datas.end();
			++it) {
				size_t		contains = it->first.size();

				for (key_set::const_iterator ite = it->first.begin();
				ite != it->first.end();
				++ite) {

				}
			}
		}
}

#endif