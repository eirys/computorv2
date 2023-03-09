/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indeterminates.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:22 by etran             #+#    #+#             */
/*   Updated: 2023/03/08 21:47:57 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDETERMINATES_HPP
# define INDETERMINATES_HPP

# include <set>
# include <map>

# include "itype.hpp"
# include "rational.hpp"

struct VariableWithExponent {
	/* Constructor ------------------------------------------------------------- */
	VariableWithExponent(const std::string& var_name, Rational exponent):
		variable_name(var_name),
		exponent(exponent) {}

	/* Attributes -------------------------------------------------------------- */
	const std::string	variable_name;	// address of the shared_ptr
	Rational			exponent;		// exponent

	bool	operator==(const VariableWithExponent& rhs) const {
		return variable_name == rhs.variable_name && exponent == rhs.exponent;
	}

	bool	operator<(const VariableWithExponent& rhs) const {
		return variable_name < rhs.variable_name && exponent < rhs.exponent;
	}
};


// class KeysetComparator {
// 	public:
// 		typedef				VariableWithExponent					key_type;
// 		typedef				std::set<key_type>						key_set;

// 		bool operator() (const key_set& lhs, const key_set& rhs) const {
// 			key_set::const_iterator it_lhs = lhs.begin();
// 			key_set::const_iterator	it_rhs = rhs.begin();

// 			while (it_lhs != lhs.end()) {

// 			}
// 			return true;
// 		}
// }


class Indeterminates {
	public:
		typedef typename	IType::shared_itype								factor;
		typedef				VariableWithExponent							key_type;
		// typedef				KeysetComparator								key_comparator;

		typedef				std::set<key_type>								key_set;
		typedef				std::pair<key_set, factor>						key_value_pair;
		typedef				std::map<key_set, factor>						data_map;

		/* Constructor ------------------------------------------------------------ */
		Indeterminates(const std::string& var_name,
			int exponent, factor value) {
				key_type	weighted_value(var_name, exponent);
				key_set		keys;

				keys.insert(weighted_value); 
				_datas[keys] = value;
			}

		Indeterminates(const Indeterminates& x): _datas(x.getMap()) {}

		/* Destructor ------------------------------------------------------------- */
		virtual ~Indeterminates() {}

		/* Functions -------------------------------------------------------------- */
		Indeterminates&	operator+=(const Indeterminates& other) {
			const data_map&				other_map = other.getMap();
			data_map::iterator			it_left(_datas.begin());
			data_map::const_iterator	it_right(other_map.begin());
			std::list<key_value_pair>	to_add;

			while (it_left != _datas.end() && it_right != other_map.end()) {
				// Pour chq element de la map
				if (it_left->first == it_right->first) {
					// Si le set est deja present, additionner les factors
					it_left->second = (*it_left->second + it_right->second)->clone();
				} else {
					// Sinon, ajouter ce set plus tard
					to_add.push_front(*it_right);
				}
				++it_left;
				++it_right;
			}
			_datas.insert(to_add.begin(), to_add.end());
			return *this;
		}
		
		Indeterminates	operator+(const Indeterminates& other) const {
			Indeterminates		cpy(*this);

			return cpy.operator+=(other);
		}

		/* Getter ----------------------------------------------------------------- */
		const data_map&		getMap() const {
			return _datas;
		}

	private:
		data_map			_datas;

		/**
		 * Returns true if this->_datas already stores other_set.
		*/
		// bool				_contains(const key_set& other_set) const {
		// 	for (data_map::const_iterator it = _datas.begin();
		// 	it != _datas.end();
		// 	++it) {
		// 		const key_set&	current_set = it->first;

		// 		for (key_set::const_iterator ite = it->first.begin();
		// 		ite != it->first.end();
		// 		++ite) {
		// 			if (key_comparator(current_set, *ite))
		// 				return true;
		// 		}
		// 	}
		// 	return false;
		// }
};

#endif