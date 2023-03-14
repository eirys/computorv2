/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/14 12:34:30 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <list>
# include <iostream>
# include <iomanip>
# include <sstream>
# include <string>
# include <memory>

# define NL std::endl
# define FLOAT_PRECISION 3
# define PROMPT ">_ "

#ifdef DEBUG
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif

namespace utils {

/* ========================================================================== */
/*                                  PROTOTYPE                                 */
/* ========================================================================== */

template <typename T>
	void display(const std::list<T>& l);

/* ========================================================================== */
/*                                 DEFINITION                                 */
/* ========================================================================== */

template <typename T>
	inline void display(const std::list<T>& l) {
		for (typename std::list<T>::const_iterator it = l.begin(); it != l.end(); ++it)
			std::cout << '[' << *it << "] ";
		std::cout << std::endl;
	}

inline bool	isCharset(const char c, const std::string charset) {
	if (charset.find(c) != std::string::npos)
		return true;
	return false;
}

} // namespace utils

#endif
