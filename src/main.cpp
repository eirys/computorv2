/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 22:28:57 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>
#include<iostream>

#include "rational.hpp"
#include "complex.hpp"
#include "utils.hpp"
#include "math.hpp"
#include "matrix.hpp"

using std::cout;

int main() {

	Matrix m(4, Rational(1));

	m[1][0] = 1.574584475;
	m[0][3] = 175;

	Matrix p(4, Rational(1));
	cout << m;
	cout << p;

	Rational a(36);
	p *= a;
	cout << p;

	try {
	Matrix tmp = Matrix::matrix { {a, a, a},
								  {a, a, a} };
	cout << tmp;
	}catch(const std::exception& e) {
		std::cerr << e.what() << NL;
	}

	cout << m;
	Matrix d = m.transpose();
	d += p;
	cout << d;

	return 0;
}