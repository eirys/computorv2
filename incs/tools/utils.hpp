/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2023/01/08 20:38:24 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <list>
# include <iostream>
# include <string>

# define NL std::endl

#if DEBUG == 1
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif

namespace utils {

	/* -- PROTOTYPE ----------------------------------------------- */

	template <typename T>
		void display(const std::list<T>& l);

	/* -- DEFINITION ---------------------------------------------- */

	template <typename T>
		inline void display(const std::list<T>& l) {
			for (typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
				std::cout << '[' << *it << "] ";
			std::cout << std::endl;
		}

	// size_t skipWhitespaces(const std::string&& buf, size_t hint = 0) {
	// 	return buf.find_first_not_of("\t ", hint);
	// }

	//TODO
	template <typename T, typename U>
		inline bool irreducible(T& a, U& b) {
			(void)a;
			(void)b;
			return false;
		}
}

#endif
