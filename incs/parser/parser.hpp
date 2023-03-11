/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:04:05 by eli               #+#    #+#             */
/*   Updated: 2023/03/11 18:52:35 by etran            ###   ########.fr       */
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
		unique_node			(Parser::*_parsefn)(const std::string&);
		/**
		 * TODO:
		 * 	Once expression parsed, need to do sth with it accordingly
		*/
		// void				(Parser::*_execute)();

		/* Parse Function Helper -------------------------------------------------- */
		unique_node			_parseA(const std::string& context_name);
		unique_node			_parseS(const std::string& context_name);
		unique_node			_parseE(const std::string& context_name);
		unique_node			_parseF(const std::string& context_name);
		unique_node			_parseT(const std::string& context_name);

		/* Utils ------------------------------------------------------------------ */
		unique_node			_parseFunction(const std::string& func_name);
		unique_node			_parseSimpleValue(const std::string& context_name);
		unique_node			_parseMatrix();
		Matrix::row			_parseMatrixRow();
};

#endif