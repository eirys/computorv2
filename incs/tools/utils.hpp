/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 00:10:19 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <list>
# include <iostream>
# include <iomanip>
# include <sstream>
# include <string>

# define NL std::endl
# define FLOAT_PRECISION 3

#if DEBUG == 1
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif


namespace utils {

/* -- PROTOTYPE ----------------------------------------------- */

template <typename T>
	void display(const std::list<T>& l);
	
template <typename T>
	size_t getWidth(const T& val);

/* -- DEFINITION ---------------------------------------------- */

template <typename T>
	inline void display(const std::list<T>& l) {
		for (typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
			std::cout << '[' << *it << "] ";
		std::cout << std::endl;
	}

template <typename T>
inline size_t getWidth(const T& val) {
	std::ostringstream o;

	o << std::setprecision(FLOAT_PRECISION) << val;
	return o.str().size();
}


} // namespace utils

#endif
