/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/30 14:55:27 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <list>
# include <utility>
# include <string>
# include <vector>
# include <map>

# include "atree_node.hpp"

class Indeterminates;

/**
 * Contexts handler.
 * 
 * Allows saving variable in memory and then some.
*/
class Computor {
	public:

		typedef typename	ATreeNode::shared_itype			value_ptr;
		typedef				std::string						name_type;
		typedef				std::pair<name_type, name_type>	name_duo;
		typedef				std::pair<name_duo, value_ptr>	variable;

		typedef				std::vector<variable>			context;
		typedef				std::list<variable>				subcontext;

		struct NameDuoComparator {
			bool operator() (const name_duo& lhs, const name_duo& rhs) {
				return lhs.first < rhs.first;
			}
		};
		typedef				NameDuoComparator				name_comp;
		typedef				std::map<
								name_duo,
								subcontext,
								name_comp
							>								context_map;
		typedef				std::set<name_duo, name_comp>	name_set;

		Computor();
		virtual ~Computor();

		/* Context Manipulation --------------------------------------------------- */
		static void				push(
									const name_type& variable_name,
									const value_ptr& value,
									const name_type& context_name = name_type()
								);
		static const value_ptr	find(
									const name_type& variable_name,
									const name_type& context_name = name_type()
								);
		static void				create_context(
									const name_type& context_name,
									const name_type& variable_name
								);
		static subcontext		find_context(const name_type& context_name);

		/* Computing Tools -------------------------------------------------------- */
		static void				toggle_equation();
		static void				toggle_computing();
		static bool				to_solve();
		static bool				to_compute();

		/* Utils ------------------------------------------------------------------ */
		void					flush();
		void					prune();

		/* Menu Tools ------------------------------------------------------------- */
		void					reset();
		void					show() const;

		/* Exception -------------------------------------------------------------- */
		class UnknownFunctionElement: public std::exception {
			public:
				UnknownFunctionElement() = delete;
				UnknownFunctionElement(const name_type& element):
					_spec("Unknown function element: `" + element + "`") {}

				const char* what() const throw() {
					return _spec.c_str();
				}
			private:
				const name_type	_spec;
		};

	private:
		static context			_memory;
		static context_map		_subcontexts;
		static bool				_solve;
		static bool				_compute;
};

#endif