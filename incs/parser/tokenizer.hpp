/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:58:58 by eli               #+#    #+#             */
/*   Updated: 2023/03/21 12:26:07 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_HPP

# include <list>
# include <string>

# include "parser_macro.hpp"

enum TokenType {
	EWHITESPACE,
	ENAME,
	ERATIONAL,
	EIMAGINARY,
	EDELIMITER,
	ESYMBOL,
	EEXPRESSION,
	EEMPTY
};

class Tokenizer {
	public:
		typedef	enum TokenType		e_tokentype;
		
		Tokenizer(const std::string& raw);
		virtual ~Tokenizer(); 

		/* Main function ---------------------------------------------------------- */
		e_tokentype				scanToken(std::string& holder);

		/* Exception -------------------------------------------------------------- */
		class BadFormat: public std::exception {
			public:
				const char* what() const throw() {
					return "Input has bad format";
				}
		};

		class EmptyInput: public std::exception {
			public:
				const char* what() const throw() {
					return "Input is empty";
				}

		};

	private:
		const std::string		_raw;
		size_t					_current_pos;

		/* Parsing utils ---------------------------------------------------------- */
		bool					_find(const char* charset) const;
		size_t					_find_not_of(
									const char* charset,
									size_t pos = std::string::npos
								) const;
		std::string				_update_token(const size_t& next_pos) const;
};

#endif