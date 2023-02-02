/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:27:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/27 13:58:53 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_F_HPP
# define PARSER_F_HPP

# include "tokenizer.hpp"
# include "atree_node.hpp"
# include "parser_macro.hpp"

/**
 *  F		: Identifier
 * 			| Variable
 * 			| ( E )
 * 			| - F
 * 			| Function?
*/
class ParserF {
	public:
		typedef typename	ATreeNode::shared_node	shared_node;

		ParserF(Tokenizer& tokenizer);
		virtual ~ParserF();

		shared_node			parse();

		class IncorrectSyntax: public std::exception {
			public:
				constexpr const char* what() const throw() {
					return "Not a correct syntax";
				}
		};

	private:
		Tokenizer&			_tokenizer;

		bool					_isIdentifier(const std::string& token) const;
};

#endif