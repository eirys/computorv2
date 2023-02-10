/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:58:58 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 12:03:29 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_HPP

# include <list>
# include <string>

# include "parser_macro.hpp"

class Tokenizer {
	public:
		Tokenizer(const std::string& raw);
		virtual ~Tokenizer(); 

		/* Main function ---------------------------------------------------------- */
		std::string				scanToken();

		/* Getter ----------------------------------------------------------------- */
		const std::string&		getNextToken() const;

		/* Exception -------------------------------------------------------------- */
		class BadFormat: public std::exception {
			public:
				constexpr const char* what() const throw() {
					return "Input has bad format";
				}
		};

		class EmptyInput: public std::exception {
			public:
				constexpr const char* what() const throw() {
					return "Input is empty";
				}

		};

	private:
		const std::string		_raw;
		size_t					_current_pos;
		std::string				_next_token;

		/* Parsing utils ---------------------------------------------------------- */
		bool					_find(const char* charset) const;
		size_t					_find_not_of(const char* charset) const;
		std::string				_update_token(const size_t& next_pos) const;
};

#endif