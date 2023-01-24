/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_e.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:17:43 by eli               #+#    #+#             */
/*   Updated: 2023/01/24 11:27:20 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_E_HPP

# include "tokenizer.hpp"

class ParserE {
	public:
		ParserE(Tokenizer& tokenizer);
		virtual~ParserE();

		// parse()

	private:
		Tokenizer&	_tokenizer;
};

#endif