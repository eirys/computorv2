/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_macro.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:58:05 by eli               #+#    #+#             */
/*   Updated: 2023/01/27 16:38:30 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MACRO_HPP
# define PARSER_MACRO_HPP

# define LETTER			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define DIGIT			"0123456789"

# define UNDERSCORE		"_"
# define L_PARENTHESIS	"("
# define R_PARENTHESIS	")"
# define L_BRACKET		"["
# define R_BRACKET		"]"
# define COMA			","
# define DOT			"."
# define SEMICOLON		";"

/* Symbols */
# define EQUAL			"="
# define MULTIPLIER		"*"
# define DIVIDER		"/"
# define ADDITION		"+"
# define SUBSTRACTION	"-"
# define NEGATE			"-"
# define MODULO			"%"
# define POWER			"^"
# define IMAGINARY_I	"i"


/* Tokenizer elements */
# define WHITESPACES	"\t "
# define RATIONAL		DIGIT DOT
# define NAME			LETTER UNDERSCORE
# define DELIMITER		L_PARENTHESIS R_PARENTHESIS L_BRACKET R_BRACKET COMA SEMICOLON
# define SYMBOL			EQUAL MULTIPLIER DIVIDER ADDITION\
						SUBSTRACTION MODULO POWER

#endif