/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:46:16 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 12:50:54 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include "rational.hpp"
# include "utils.hpp"
// # include "tree_node.hpp"

class Complex/* : virtual public TreeNode  */{
	public:
		Complex();
		virtual ~Complex();

		Complex(const Complex& x);
		Complex(const Rational& x, const Rational& y = Rational(0));
		Complex(const std::string&& buf);

		Complex& 		operator=(const Complex& rhs);
		Complex& 		operator=(const Rational& rhs);

		// Arith. operators
		Complex			conjugate() const;

		Complex&		operator+=(const Complex& rhs);
		Complex			operator+(const Complex& rhs) const;

		Complex&		operator-=(const Complex& rhs);
		Complex			operator-(const Complex& rhs) const;
		Complex			operator-() const;

		Complex&		operator*=(const Complex& rhs);
		Complex			operator*(const Complex& rhs) const;
		
		Complex&		operator/=(const Complex& rhs);
		Complex			operator/(const Complex& rhs) const;

		Complex&		operator^=(const Rational& rhs);
		Complex			operator^(const Rational& rhs) const;

		Complex&		operator%=(const Rational& rhs);
		Complex			operator%(const Rational& rhs) const;

		// Getter
		Rational		getReal() const;
		Rational		getImaginary() const;

		// Tools
		bool			operator!() const;
		bool			isComplex() const;
		bool			isReal() const;
		bool			isImaginary() const;

	private:
		Rational		_re;
		Rational		_im;

		void			_parseBuf(const std::string& buf);
};

bool					operator==(const Complex& x, const Complex& y);
bool					operator!=(const Complex& x, const Complex& y);

std::ostream&			operator<<(std::ostream& o, const Complex& x);

#endif