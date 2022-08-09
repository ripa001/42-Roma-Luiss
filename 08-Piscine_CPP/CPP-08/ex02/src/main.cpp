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

#include "../include/MutantStack.hpp"

#define RED "\033[31m"
#define NONE "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

int main()
{
	std::cout << std::endl;

	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);

	std::cout << std::endl;
	std::cout << "\033[32m" << "-------------------------------------------" << "\033[0m" << std::endl;

	MutantStack<int> a;
	std::list<int> b;

	a = mstack;
	b.push_back(5);
	b.push_back(17);
	b.back();
	b.pop_back();
	b.push_back(3);
	b.push_back(5);
	b.push_back(737);
	b.push_back(0);

	MutantStack<int>::iterator itStack = mstack.begin();
	MutantStack<int>::iterator itendStack = mstack.end();
	std::list<int>::iterator itList = b.begin();
	std::list<int>::iterator itendList = b.end();

	std::cout << "\033[34m" << "Size Stack:   " << mstack.size() << "     |   Size List:   " << b.size() << std::endl;
	while ((itStack != itendStack) && (itList != itendList))
	{
		std::cout << std::setw(19) << *itStack << " | " << *itList << std::endl;
		itStack++;
		itList++;
	}
	std::cout << "\033[0m" << std::endl;
}
