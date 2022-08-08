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
#include "../include/easyfind.hpp"

void	displayInt(int i)
{
	std::cout << i << " ";
}

int		main(void)
{
	{
		std::vector<int> a;
		for (int i = 0; i < 10; i++)
			a.push_back(i + 1);

		std::cout << std::endl << CYAN << "**** Vector ****  " << NONE << std::endl << std::endl;
		std::cout << "Vector info: " << std::endl;
		for_each(a.begin(), a.end(), displayInt);
		std::cout << std::endl;

		std::cout << std::endl << YELLOW << "easyfind(a, 5) " << NONE << std::endl;
		std::cout << *(easyfind(a, 5)) << std::endl; 
		try
		{
			std::cout << std::endl << YELLOW << "easyfind(a, 50) " << NONE << std::endl ;
			std::cout << *(easyfind(a, 50)) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		std::cout <<  std::endl << "-----------------------------------------------" << std::endl;
		std::cout << std::endl << CYAN << "**** List ****  " << NONE << std::endl ;
		std::list<int> b;
		for (int i = 0; i < 10; i++)
			b.push_back(i + 1);
		std::cout << "List info: " << std::endl;
		for_each(b.begin(), b.end(), displayInt);
		std::cout << std::endl;

		std::cout << std::endl << YELLOW << "easyfind(b, 5) " << NONE << std::endl;
		std::cout << *(easyfind(b, 5)) << std::endl; 
		try
		{
			std::cout << std::endl << YELLOW << "easyfind(b, 50) " << NONE << std::endl;
			std::cout << *(easyfind(b, 50)) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		std::cout <<  std::endl << "-----------------------------------------------" << std::endl;
		std::cout << std::endl << CYAN << "**** Deque ****  " << NONE << std::endl ;
	
		std::deque<int> deque;
		for (int i = 0; i < 10; i++)
			deque.push_back(i);
		std::cout << "Deque info: " << std::endl << std::endl;
		for_each(deque.begin(), deque.end(), displayInt);
		std::cout << std::endl << YELLOW << "easyfind(deque, 5) " << NONE << std::endl;
		std::cout << *(easyfind(deque, 5)) << std::endl; 
		try
		{
			std::cout << std::endl << YELLOW << "easyfind(deque, 50) " << NONE << std::endl;
			std::cout << *(easyfind(deque, 50)) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

}
