/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itype.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:25:22 by eli               #+#    #+#             */
/*   Updated: 2023/03/18 11:41:08 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITYPE_HPP
# define ITYPE_HPP

# include <memory>
# include <ostream>

class IType {
	public:
		typedef		std::unique_ptr<IType>		unique_itype;
		typedef		std::shared_ptr<IType>		shared_itype;
		typedef		std::weak_ptr<IType>		weak_itype;

		/* Virtual Destructor ----------------------------------------------------- */
		virtual ~IType();

		/* Override --------------------------------------------------------------- */
		virtual shared_itype	clone() const = 0;

		virtual shared_itype	negate() const = 0;
		virtual shared_itype	operator+(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator-(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator*(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator/(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator^(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator%(const shared_itype& rhs) const = 0;

		virtual bool			operator==(const shared_itype& rhs) const = 0;

		/* Exception -------------------------------------------------------------- */
		class UndefinedValue: public std::exception {
			public:
				const char* what() const throw() {
					return "Undefined value cast";
				}
		};

		class ImpossibleComparison: public std::exception {
			public:
				const char* what() const throw() {
					return "Impossible to compare those values";
				}
		};

	protected:
		IType();
};

/* Utils -------------------------------------------------------------------- */
std::ostream&	operator<<(std::ostream& o, const IType& x);

#endif