/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:56:48 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/08 10:56:48 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template <typename T>

void	swap(T &first, T &second)
{
	T temp = first;
	first = second;
	second = temp;
}

template <typename T> T min(T first, T second)
{
	return (first < second ? first : second);
}

template <typename T> T max(T first, T second)
{
	return (first > second ? first : second);
}

#endif