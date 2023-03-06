/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/06 17:14:13 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <stack>
# include <memory>

# include "atree_node.hpp"

class Computor {
	public:
		typedef				std::string						name;
		typedef typename	ATreeNode::shared_itype			value_ptr;
		typedef				std::pair<name, value_ptr>		variable;
		typedef				std::stack<variable>			context;

		Computor();
		virtual ~Computor();

		static void				push(const std::string& name, const value_ptr& value);
		static const value_ptr	find(const std::string& name);
		void					show() const;

		/* Memory Stack ----------------------------------------------------------- */
		private:
			static context		_memory;
};

#endif