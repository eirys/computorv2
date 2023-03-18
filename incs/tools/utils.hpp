/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/18 20:29:07 by eli              ###   ########.fr       */
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
# include <algorithm>

# include "parser_macro.hpp"

# define NL std::endl
# define FLOAT_PRECISION 3
# define PROMPT ">_ "

#ifdef __VERBOSE
# define LOG(X) std::cerr << X << NL
#else
# define LOG(X)
#endif

#ifdef __DEBUG
# define DEBUG(X) std::cerr << X << NL
#else
# define DEBUG(X)
#endif

namespace utils {

/* ========================================================================== */
/*                                  PROTOTYPE                                 */
/* ========================================================================== */

bool		isCharset(const char c, const std::string charset);
std::string	toLower(const std::string& s);
std::string	trimmed(const std::string& s);

/* ========================================================================== */
/*                                 DEFINITION                                 */
/* ========================================================================== */

inline	bool	isCharset(const char c, const std::string charset) {
	if (charset.find(c) != std::string::npos)
		return true;
	return false;
}

inline std::string	toLower(const std::string& s) {
	std::string	copy(s);
	std::transform(
		copy.begin(),
		copy.end(),
		copy.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);
	return copy;
}

inline std::string	trimmed(const std::string& s) {
	size_t	new_start = s.find_first_not_of(WHITESPACES);
	if (new_start == std::string::npos)
		return std::string();
	size_t	new_end = s.find_last_not_of(WHITESPACES);
	return s.substr(new_start, new_end + 1 - new_start);
}

} // namespace utils

#endif
