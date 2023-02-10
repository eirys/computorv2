/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 14:56:02 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP

# include "tokenizer.hpp"

class Parser {
	public:
		typedef typename	ATreeNode::shared_node	shared_node;

		Parser(const std::string& raw);
		virtual ~Parser();

		/* Parsing Functions ------------------------------------------------------ */
		shared_node			parseE();
		shared_node			parseF();
		shared_node			parseT();

		/* Exception -------------------------------------------------------------- */
		class IncorrectSyntax: public std::exception {
			public:
				constexpr const char* what() const throw() {
					return "Not a correct syntax";
				}
		};

	private:
		Tokenizer			_tokenizer;
		std::string			_token;

};

#endif