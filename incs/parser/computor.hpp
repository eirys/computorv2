/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/11 15:56:51 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <stack>
# include <memory>
# include <map>

# include "atree_node.hpp"

class Computor {
	public:
		typedef typename	ATreeNode::shared_itype			value_ptr;
		typedef				std::string						name_type;
		typedef				std::pair<name_type, value_ptr>	variable;
		typedef				std::stack<variable>			context;
		typedef				std::map<name_type, context>	context_map;

		Computor();
		virtual ~Computor();

		/* ------------------------------------------------------------------------ */
		static void				push(
									const name_type& variable_name,
									const value_ptr& value,
									const name_type& context_name = std::string()
								);
		static const value_ptr	find(
									const name_type& variable_name,
									const name_type& context_name = std::string()
								);
		void					show() const;
		// static void				push_context(
		// 							const name_type& context_name,
		// 							const name_type& variable_name,
		// 							const value_ptr& value = nullptr
		// 						);
		// static const value_ptr	find_context(
		// 							const name_type& context_name,
		// 							const name_type& variable_name
		// 						);

		/* Exception -------------------------------------------------------------- */
		class ContextInexistent: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Context does not exist";
				}
		};

	private:
		static context			_memory;
		static context_map		_local_memory;
};

#endif