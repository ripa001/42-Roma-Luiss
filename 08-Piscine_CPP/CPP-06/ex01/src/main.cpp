/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:43:02 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/07 12:43:02 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>
#include "../include/Data.hpp"


uintptr_t	serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*	deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

int	main()
{
	Data		og;
	uintptr_t	serialized;
	Data		*deserialized;

	std::cout << &og << " => " << og.value << std::endl;

	serialized = serialize(&og);

	std::cout << std::hex << std::showbase << serialized << std::dec << std::endl;

	deserialized = deserialize(serialized);

	std::cout << &deserialized << " => " << deserialized->value << std::endl;
	
	return (0);
}
