/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:57:02 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/08 11:57:02 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     //SCOPE
//     {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;//
//     return 0;
// }

#define RED "\033[31m"
#define NONE "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

int			main(void)
{
	int	i;
	Array<int>		tab(5);
	Array<char>		tab_char(3);
	Array<char>		tab_char2(3);
	Array<float>	tab_float;

	tab[0] = 0;
	tab[1] = 1;
	tab[2] = 2;
	tab[3] = 3;
	tab[4] = 4;
	
	std::cout << CYAN << "--- Test 1 ---" << NONE << std::endl;
	std::cout << "size: " << tab.size() << std::endl;
	for (i = 0; i < (int)tab.size(); i++)
	{
		if (i == 0)
			std::cout << "value: [";
		if (i >= 0 && i < (int)(tab.size() - 1))
			std::cout << tab[i] << ", ";
		else
			std::cout << tab[i] << "]" << std::endl;
	}
	try
	{
		std::cout << tab[5] << std::endl;
	}
	catch(std::exception const &e)
	{
		std::cout << RED << "Get element from unset cell" << NONE << std::endl;
		std::cerr << e.what() << '\n';
	}
	

	tab_char[0] = 'a';
	tab_char[1] = 'b';
	tab_char[2] = 'c';
	std::cout << std::endl << std::endl;
	std::cout << CYAN << "--- Test 2 tab_char---" << NONE << std::endl;
	std::cout << "size: " << (int)tab_char.size() << std::endl;
	for (i = 0; i < (int)tab_char.size(); i++)
	{
		if (i == 0)
			std::cout << "value: [";
		if (i >= 0 && i < (int)(tab_char.size() - 1))
			std::cout << tab_char[i] << ", ";
		else
			std::cout << tab_char[i] << "]" << std::endl;
	}
	try
	{
		std::cout << tab_char[5] << std::endl;
	}
	catch(std::exception const &e)
	{
		std::cout << RED << "Get element from unset cell" << NONE << std::endl;
		std::cerr << e.what() << '\n';
	}

	std::cout << std::endl << std::endl;
	std::cout << CYAN << "--- Test 3 ---" << NONE << std::endl;
	try {
		std::cout << tab_float[0] << std::endl;}
	catch(std::exception const &e) {
		std::cout << RED << "Get element of empty array" << NONE << std::endl;
		std::cerr << e.what() << '\n'; }

	std::cout << std::endl << std::endl;
	std::cout << CYAN << "--- Test 4 ---" << NONE << std::endl;
	std::cout << "assignation (=) tab_char2 = tab_char" << std::endl;
	tab_char2 = tab_char;
	for (i = 0; i < (int)tab_char2.size(); i++)
	{
		if (i == 0)
			std::cout << "value: [";
		if (i >= 0 && i < (int)(tab_char2.size() - 1))
			std::cout << tab_char2[i] << ", ";
		else
			std::cout << tab_char2[i] << "]" << std::endl;
	}

	std::cout << std::endl << std::endl;
	std::cout << CYAN << "--- Test 5 ---" << NONE << std::endl;
	std::cout << "constructor copy tab_char3(tab_char2)" << std::endl;
	Array<char>		tab_char3(tab_char2);
	for (i = 0; i < (int)tab_char3.size(); i++)
	{
		if (i == 0)
			std::cout << "value: [";
		if (i >= 0 && i < (int)(tab_char3.size() - 1))
			std::cout << tab_char3[i] << ", ";
		else
			std::cout << tab_char3[i] << "]" << std::endl;
	}
	return 0;
}
