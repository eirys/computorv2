/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/09 14:36:14 by eli              ###   ########.fr       */
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

	Matrix m(2,4);

	m[1][0] = 1.574584475;
	m[0][3] = 175;

	Matrix p(3);
	cout << m;
	cout << p;
	return 0;
}