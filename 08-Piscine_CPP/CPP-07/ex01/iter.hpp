/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:04:56 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/08 11:04:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <string>
#include <iostream>
template<typename T>
void	iter(const T* array, size_t length, void function(const T&))
{
	for (size_t i = 0; i < length; i++)
		function(array[i]);
}

#endif
