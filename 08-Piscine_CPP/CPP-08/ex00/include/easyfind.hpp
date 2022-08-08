/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:09:43 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/07 13:09:43 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_H
# define EASYFIND_H

#define RED "\033[31m"
#define NONE "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <deque>

class NotFoundException: public std::exception
{
	public:
		const char* what() const throw();
};

const char*	NotFoundException::what() const throw()
{
	return "Element not found in container";
}

template <typename T>
typename T::const_iterator	easyfind(T first, int second)
{
	typename T::iterator it = std::find(first.begin(), first.end(), second);
	if (it == first.end())
		throw NotFoundException();
	return (it);
}


#endif
