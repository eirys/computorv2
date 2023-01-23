/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:35:23 by eli               #+#    #+#             */
/*   Updated: 2023/01/23 19:40:48 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string>
#include<iostream>

#include "rational.hpp"
#include "complex.hpp"
#include "utils.hpp"
#include "math.hpp"
#include "matrix.hpp"
#include "function.hpp"
#include "tree.hpp"
#include "atree_node.hpp"

using std::cout;

void test1() {
  		Matrix	m1 = Matrix::matrix { { 2, 2 },
									  { 1, 1 } };
		Matrix	m2 = Matrix::matrix { { 5, 4, 3 },
									  { 1, 2, 0 } };

		cout << m1;

		cout << m2;

		Matrix m3 = m1 * m2;

		cout << m3;

		Matrix m4(2, Rational(1));

		Matrix m5 = m1 * m4;

		cout << m5;
}

void test2() {
		Rational tmp(6);

		Complex b(tmp);
		cout << b << NL;
		
		b*= Complex(1, 1);

		cout << b << NL;

		b*= b;
		cout << b << NL;

		b/=b;
		cout << b << NL;

}

void test3() {
	Matrix m = Matrix::matrix { { 1, 22, 1 } };
	cout << m;

	m+=m;

	cout << m;

	m = m * m[0][0];
	cout << m;
}

void test4() {
	Matrix m = Matrix::matrix { { 1, 11, 22 } };
	Complex c(5, 2);
	Rational r(2);

	cout << (m * r);
	cout << (r * m);
	cout << (m * Rational(1));
	cout << (Rational(1) * m);
	
	cout << (m * m[0][1]);

	cout << (c * r) << NL;
	cout << (r * c) << NL;
	cout << (c * Rational(1)) << NL;
	cout << (Rational(1) * c) << NL;

	cout << (c * c.getReal()) << NL;
}

void test5() {
	Complex		a(1, 1);
	Rational	b(6);
	cout << "test5" << NL;
	cout << (b ^ 2) << NL;
	cout << (a ^ 2) << NL;
}

void test6() {
	typedef ATreeNode<Rational>		atreenode;
	typedef ATreeNode<Complex>		atreenode_c;

	std::shared_ptr<atreenode>		sa;
	std::shared_ptr<atreenode>		sb;

	std::shared_ptr<atreenode_c>	sc;
	std::shared_ptr<atreenode_c>	sd;
	
	sa.reset(new Variable<Rational>(25));
	sb.reset(new Variable<Rational>(25));

	sc.reset(new Variable<Complex>(Complex(1, 1)));
	sd.reset(new Variable<Complex>(Complex(2, 2)));

	Add<Rational>		add(sa, sb);
	Negate<Rational>	neg(sa);
	Substract<Rational>	sub(sa, sb);
	Multiply<Rational>	mul(sa, sb);
	Divide<Rational>	div(sa, sb);


	Add<Complex>		add_c(sc, sd);
	cout << add_c.eval()<<NL;

	// cout << div.eval()<< NL;
}

int main() {
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	test6();
	return 0;
}