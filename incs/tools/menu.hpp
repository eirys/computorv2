/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:24:59 by eli               #+#    #+#             */
/*   Updated: 2023/04/04 15:59:45 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_HPP
# define MENU_HPP

# include <signal.h>
# include "computor.hpp"

# define __DISPLAY_HELP		"help"
# define __DISPLAY_MEMORY	"display"
# define __DISPLAY_COMMANDS	"commands"
# define __RESET_MEMORY		"reset"

enum SignalState {
	INIT_SIGNAL,
	RESET_SIGNAL
};

class Menu {
	public:
		typedef		enum SignalState		SignalState;
		Menu();
		~Menu();

		/* Main Function ---------------------------------------------------------- */
		void				prompt();
		bool				triggered();
		static void			trigger();

	private:
		Computor			_computor_context;
		struct sigaction	_old_sigint;
		static bool			_sigint_triggered;

		void				_help();
		void				_display();
		void				_reset();
		void				_commands();
		void				_execute(const std::string& query);
		void				_compute(const std::string& entry);

		void				_setupSignal(SignalState value);
};

#endif