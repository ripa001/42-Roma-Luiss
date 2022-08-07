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

#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"

Base * generate(void) {
	int i = rand();

	switch (i % 3)
	{
	case 0:
		return (new A());
	case 1:
		return (new B());
	default:
		return (new C());
	}
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A";
	else if (dynamic_cast<B*>(p))
		std::cout << "B";
	else if (dynamic_cast<C*>(p))
		std::cout << "C";
	else
		std::cout << "unknown";
	std::cout << std::endl;
}

void	identify(Base& p)
{
	try {
		void(dynamic_cast<A&>(p));
		std::cout << "A" << std::endl;
		return ;
	} catch(std::exception& e) {}

	try {
		void(dynamic_cast<B&>(p));
		std::cout << "B" << std::endl;
		return ;
	} catch(std::exception& e) {}

	try {
		void(dynamic_cast<C&>(p));
		std::cout << "C" << std::endl;
		return ;
	} catch(std::exception& e) {}

	std::cout << "unknown" << std::endl;
}

int	main()
{
	Base*	foo = generate();
	Base*	a = new A();


	identify(foo);
	identify(*foo);
	identify(a);
	identify(*a);

	delete foo;
	delete a;
}
