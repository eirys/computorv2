/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:03:06 by etran             #+#    #+#             */
/*   Updated: 2023/03/04 21:28:03 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <stack>
# include <memory>

# include "variable.hpp"

class Computor {
	public:
		typedef			std::shared_ptr<Variable>		variable_ptr;
		typedef			std::stack<variable_ptr>		context;

		Computor();
		virtual ~Computor();

		const context&					getMemory() const;

	private:
		context							_memory;
};

#endif