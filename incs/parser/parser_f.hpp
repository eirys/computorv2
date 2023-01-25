/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_f.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:27:10 by eli               #+#    #+#             */
/*   Updated: 2023/01/25 01:41:30 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_F_HPP
# define PARSER_F_HPP

# include "tokenizer.hpp"
# include "atree_node.hpp"

/**
 *  F		= Identifier
 * 			| Variable
 * 			| ( E )
 * 			| [ [ Rational ] ]
 * 			| - F
*/
class ParserF {
	public:
		typedef typename	ATreeNode::shared_node	shared_node;

		ParserF(Tokenizer& tokenizer);
		virtual ~ParserF();

		shared_node			parse();
				
	private:
		Tokenizer&			_tokenizer;

};

#endif