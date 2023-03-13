/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/03/13 19:14:01 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "computor.hpp"
# include "tokenizer.hpp"
# include "atree_node.hpp"

/**
 * 
*/
class Parser {
	public:
		typedef typename	ATreeNode::unique_node	unique_node;
		typedef typename	ATreeNode::tree_head	result_tree;
		typedef typename	Tokenizer::e_tokentype	e_tokentype;

		Parser(const std::string& raw);
		virtual ~Parser();

		/* Main Function ---------------------------------------------------------- */
		result_tree			parse();

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

		class EmptyContent: public std::exception {
			const char* what() const throw() {
				return "Empty content";
			}
		};

	private:
		Tokenizer			_tokenizer;
		std::string			_token;
		e_tokentype			_ret;
		unique_node			(Parser::*_parsefn)();

		/* Parse Function Helper -------------------------------------------------- */
		unique_node			_parseA();
		unique_node			_parseS();
		unique_node			_parseE();
		unique_node			_parseF();
		unique_node			_parseT();

		/* Utils ------------------------------------------------------------------ */
		unique_node			_parseFunction(std::string& var_name);
		unique_node			_parseSimpleValue();
		unique_node			_parseMatrix();
		Matrix::row			_parseMatrixRow();
};

#endif