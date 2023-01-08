/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/08 01:10:27 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>
#include<iostream>

#include "rational.hpp"
#include "complex.hpp"
#include "utils.hpp"
#include "math.hpp"


using std::cout;

int main() {
	// Complex a = Complex(20, -4);
	// Complex d = Complex(3, 2);
	Complex a(2, 3);
	Complex d(0, 4);
	cout <<a<<NL;
	cout <<d<<NL;

	cout << (a/d) << NL;
	return 0;
}