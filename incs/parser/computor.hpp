/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/15 21:34:26 by eli              ###   ########.fr       */
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

/**
 * Contexts handler.
 * 
 * Allows saving variable in memory and then some.
*/
class Computor {
	public:
		typedef typename	ATreeNode::shared_itype			value_ptr;
		typedef				std::string						name_type;
		typedef				std::pair<name_type, value_ptr>	variable;
		typedef				std::vector<variable>			context;
		typedef				std::list<variable>				subcontext;
		typedef				std::map<name_type, subcontext>	context_map;

		Computor();
		virtual ~Computor();

		/* Tools ------------------------------------------------------------------ */
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
									//TODO: set multiple later
								);
		void					flush();
		void					prune();

		/* Menu ------------------------------------------------------------------- */
		void					reset();

		/* Utils ------------------------------------------------------------------ */
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
};

#endif