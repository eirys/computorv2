/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:00:06 by eli               #+#    #+#             */
/*   Updated: 2023/01/08 21:23:41 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP

# include "rational.hpp"
class Matrix {
	public:
		typedef				std::vector<Rational>		line;

		Matrix();
		virtual ~Matrix();

		explicit Matrix(size_t n, size_t p);

	private:
		size_t				_n;
		size_t				_p;
		std::vector<row>	_matrix;


};

#endif