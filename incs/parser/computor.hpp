/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/14 12:03:38 by etran            ###   ########.fr       */
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
		typedef				std::vector<variable>			context;
		typedef				std::list<size_t>				context_pos;

		Computor();
		virtual ~Computor();

		/* ------------------------------------------------------------------------ */
		static void				push(
									const name_type& variable_name,
									const value_ptr& value
								);
		static const value_ptr	find(
									const name_type& variable_name,
									bool in_context = false
								);
		static void				create_context();
		static void				flush();
		void					show() const;

	private:
		static context			_memory;
		static context_pos		_subcontext_pos;
		static uint_fast16_t	_active_context;
};

#endif