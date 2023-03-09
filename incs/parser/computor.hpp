/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/09 15:23:34 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <stack>
# include <memory>
# include <map>

# include "atree_node.hpp"
# include "identifier.hpp"

class IdentifierComparator {
	bool	operator() (const Identifier& x, const Identifier& y) const {
		return x.getName() < y.getName();
	}
};

class Computor {
	public:
		typedef typename	ATreeNode::shared_itype			value_ptr;
		typedef				std::string						name_type;
		typedef				std::pair<name_type, value_ptr>	variable;
		typedef				std::stack<variable>			context;
		typedef				std::map<Identifier,
								context,
								IdentifierComparator>		context_map;

		Computor();
		virtual ~Computor();

		static void				push(const std::string& name, const value_ptr& value);
		static const value_ptr	find(const std::string& name);
		void					show() const;
		static void				push_context(
									const Identifier& context_name,
									const name_type& name,
									const value_ptr& value = nullptr
								);
		static const value_ptr	find_context(
									const Identifier& context_name,
									const name_type& name
								);

	private:
		static context			_memory;
		static context_map		_local_memory;
};

#endif