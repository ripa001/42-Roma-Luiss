/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:05:48 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/08 11:05:48 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

void printCharUp(const char& c)
{
	std::cout << (char)toupper(c);
}

void printPlusTwo(const int& n)
{
	std::cout << n + 2 << std::endl;
}

int main(void)
{
	{
		iter("ciao! come va?", 14, printCharUp);
		std::cout << std::endl;
	}
	{
		int array[5] = {5, 10, 40, 28, -55};
		iter(array, 5, printPlusTwo);
	}
}
