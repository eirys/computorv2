/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:24:59 by eli               #+#    #+#             */
/*   Updated: 2023/03/29 18:48:07 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_HPP
# define MENU_HPP

# include "computor.hpp"

# define __DISPLAY_HELP		"help"
# define __DISPLAY_MEMORY	"display"
# define __RESET_MEMORY		"reset"

class Menu {
	public:
		Menu();
		~Menu();

		void		prompt();

	private:
		void		_execute(const std::string& query);
		void		_help();
		void		_display();
		void		_reset();
		void		_compute(const std::string& entry);

		Computor	_computor_context;
};


#endif