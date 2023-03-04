/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/02/12 10:59:32 by eli              ###   ########.fr       */
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

/**
 * 
*/
class Parser {
	public:
		typedef typename	ATreeNode::unique_node	unique_node;
		typedef typename	Tokenizer::e_tokentype	e_tokentype;

		Parser(const std::string& raw);
		virtual ~Parser();

		/* Parsing Functions ------------------------------------------------------ */
		unique_node			parseE();

		/* Exception -------------------------------------------------------------- */
		class IncorrectSyntax: public std::exception {
			public:
				IncorrectSyntax() = delete;
				IncorrectSyntax(const std::string&& specificity):
					_specificity("Not a correct syntax: " + specificity) {}

				const char* what() const throw() {
					return _specificity.c_str();
				}
			private:
				const std::string	_specificity;
		};

	private:
		Tokenizer			_tokenizer;
		std::string			_token;
		e_tokentype			_ret;

		/* Parse Function Helper -------------------------------------------------- */
		unique_node			_parseF();
		unique_node			_parseT();

		/* Utils ------------------------------------------------------------------ */
		Complex				_convertTokenToImaginary() const;
};

#endif