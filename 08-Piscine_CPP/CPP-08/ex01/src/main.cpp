/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:42:41 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/09 11:42:41 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Span.hpp"

#define TEST_MIN 10000

int	main(void)
{
	Span x(5);

	x.addNumber(10);
	x.addNumber(11);
	x.addNumber(22);
	x.addNumber(25);
	x.addNumber(30);

	std::cout << "*** 5 ***" << std::endl
		<< "shortest: " << x.shortestSpan() << std::endl
		<< "longest: " << x.longestSpan() << std::endl;

	// elements size reached
	try
	{
		x.addNumber(25);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// invalid size
	try
	{
		Span sp(0);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// no elements
	try
	{
		Span sp(3);
		sp.longestSpan();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	{
		Span				y(TEST_MIN);
		std::vector<int>	v;


		while (v.size() < TEST_MIN)
			v.push_back(rand());

		y.addNumber(v.begin(), v.end());

		std::cout << std::endl << "*** 10 000 ***" << std::endl
			<< "shortest: " << y.shortestSpan() << std::endl
			<< "longest: " << y.longestSpan() << std::endl;
	}
}