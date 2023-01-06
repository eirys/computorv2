/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/06 22:50:55 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>
#include<iostream>

#include "rational.hpp"
#include "complex.hpp"
#include "utils.hpp"

int main() {
	Complex a;
	Complex b;

	Rational c("236.66");
	Rational d(499.0);

	std::cout << (a == b) << NL;
	std::cout << c.getVal() << NL;

	c = 200.025l;
	std::cout << c << NL;

	c = d;
	std::cout << c << NL;
}