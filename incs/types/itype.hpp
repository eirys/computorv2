/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itype.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eli <eli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:25:22 by eli               #+#    #+#             */
/*   Updated: 2023/01/21 21:56:41 by eli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITYPE_HPP
# define ITYPE_HPP

# include <memory>

class IType {
	public:
		typedef typename	std::unique_ptr<IType>		unique_itype;
		typedef typename	std::shared_ptr<IType>		shared_itype;
		typedef typename	std::weak_ptr<IType>		weak_itype;

		virtual ~IType() {}

		virtual shared_itype	operator+(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator-(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator*(const shared_itype& rhs) const = 0;
		virtual shared_itype	operator/(const shared_itype& rhs) const = 0;
};


#endif