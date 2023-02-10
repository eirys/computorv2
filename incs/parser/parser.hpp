/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/02/10 23:07:16 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP

# include "tokenizer.hpp"

# include "atree_node.hpp"
# include "identifier.hpp"
# include "variable.hpp"
# include "add.hpp"
# include "substract.hpp"
# include "multiply.hpp"
# include "divide.hpp"
# include "negate.hpp"

class Parser {
	public:
		typedef typename	ATreeNode::shared_node	shared_node;
		typedef typename	Tokenizer::e_tokentype	e_tokentype;

		Parser(const std::string& raw);
		virtual ~Parser();

		/* Parsing Functions ------------------------------------------------------ */
		shared_node			parseF();
		shared_node			parseE();
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
		e_tokentype			_ret;
};

#endif