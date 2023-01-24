/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:58:58 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 11:27:02 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_HPP

# include <list>
# include <string>

# define WHITESPACES "\t "

class Tokenizer {
	public:
		Tokenizer(const std::string& raw);
		virtual ~Tokenizer(); 

		std::string				scanToken();

		class BadFormat: public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Input has bad format";
				}
		};

	private:
		const std::string		_raw;
		size_t					_current_pos;
		std::string				_next_token;
};

#endif