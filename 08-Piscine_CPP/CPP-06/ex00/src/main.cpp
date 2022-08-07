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

#include <iostream>
#include <limits>
#include <string>
#include <bits/stdc++.h>

void	toChar(double val)
{
	char	c = static_cast<char>(val);

	if (val != val || !isascii(val))
		std::cout << "impossible";
	else if (isprint(c))
		std::cout << "'" << c << "'";
	else
		std::cout << "Non displayable";
}

void	toInt(double val)
{
	int	i = static_cast<int>(val);

	if (val != val || val < INT_MIN || val > INT_MAX)
		std::cout << "impossible";
	else
		std::cout << i;
}

void	toFloat(double val)
{
	float	f = static_cast<float>(val);

	std::cout << f << "f";
}

int main(int ac, char **av)
{
	if (ac < 2)
		return 1;

	double	val = atof(av[1]);

	std::cout.precision(1);
	std::cout << std::fixed;

	std::cout << "char" << ": ";
	toChar(val);
	std::cout << std::endl;

	std::cout << "int" << ": ";
	toInt(val);
	std::cout << std::endl;

	std::cout << "float" << ": ";
	toFloat(val);
	std::cout << std::endl;

	std::cout << "double" << ": ";
	std::cout << val << std::endl;
}
