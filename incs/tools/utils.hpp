/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:26:40 by eli               #+#    #+#             */
/*   Updated: 2023/03/16 10:51:12 by etran            ###   ########.fr       */
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
std::string	toLower(std::string& s);

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

} // namespace utils

#endif
