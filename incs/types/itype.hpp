/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itype.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:25:22 by eli               #+#    #+#             */
/*   Updated: 2023/03/08 21:40:30 by eli              ###   ########.fr       */
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

		virtual shared_itype	operator+(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator-(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator*(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator/(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator^(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator%(const shared_itype& rhs) const = 0;

	protected:
		IType();
};

/* Utils -------------------------------------------------------------------- */
std::ostream&	operator<<(std::ostream& o, const IType& x);

#endif