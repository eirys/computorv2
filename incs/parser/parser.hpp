/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/03/30 13:06:11 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "computor.hpp"
# include "tokenizer.hpp"
# include "atree_node.hpp"

class Parser {
	public:
		typedef typename	ATreeNode::unique_node	unique_node;
		typedef typename	ATreeNode::tree_head	result_tree;
		typedef typename	Tokenizer::e_tokentype	e_tokentype;
		typedef typename	ATreeNode::shared_itype	shared_itype;

		Parser(const std::string& raw);
		virtual ~Parser();

		/* Main Function ---------------------------------------------------------- */
		result_tree			parse();

		/* Exception -------------------------------------------------------------- */
		class IncorrectSyntax: public std::exception {
			public:
				IncorrectSyntax() = delete;
				IncorrectSyntax(const std::string&& specificity):
					_specificity("Incorrect syntax: " + specificity) {}

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

		std::string			_context;
		std::string			_var_name;

		/* Parsing Differentiation ------------------------------------------------ */
		unique_node			_parseA();
		unique_node			_parseS();
		
		/* Parse Function Helper -------------------------------------------------- */
		unique_node			_parseE();
		unique_node			_parseT();
		unique_node			_parseP();
		unique_node			_parseF();

		/* Utils ------------------------------------------------------------------ */
		unique_node			_parseFunction();
		unique_node			_parseSimpleValue();
		unique_node			_parseMatrix();
		Matrix::row			_parseMatrixRow();
		void				_parseEqm();
};

#endif