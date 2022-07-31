/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:43:57 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:43:57 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"

int main()
{
	Bureaucrat				a;
	Bureaucrat				b;
	Bureaucrat				c;
	
	ShrubberyCreationForm	e;
	RobotomyRequestForm		f;
	PresidentialPardonForm	g;

	std::cout << "**** Constructor ****" << std::endl << std::endl;
	try
	{
		Bureaucrat Luca("Luca", 1);
		a = Luca;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat Cipo("Cipo", 150);
		c = Cipo;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat Francesco("Francesco", 43);
		b = Francesco;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl << "**** Info ****  " << std::endl << std::endl;

	std::cout << a;
	std::cout << b;
	std::cout << c;
	std::cout << std::endl;
	std::cout << e;
	std::cout << std::endl;
	std::cout << f;
	std::cout << std::endl;
	std::cout << g;
	std::cout << std::endl << "**** Testing ****  "  << std::endl << std::endl;

	b.executeForm(e);
	std::cout << std::endl;
	a.signForm(e);
	b.signForm(e);
	c.signForm(e);
	std::cout << std::endl;
	a.executeForm(e);
	b.executeForm(e);
	std::cout << std::endl;
	a.executeForm(f);
	std::cout << std::endl;
	c.signForm(f);
	a.signForm(f);
	b.signForm(f);
	std::cout << std::endl;
	a.executeForm(f);
	b.executeForm(f);
	std::cout << std::endl;
	b.executeForm(g);
	std::cout << std::endl;
	c.signForm(g);
	a.signForm(g);
	b.signForm(g);
	std::cout << std::endl;
	a.executeForm(g);
	b.executeForm(g);
	std::cout << std::endl;

	std::cout << std::endl << "**** Destructor ****"  << std::endl << std::endl;
	// delete *z;
	// delete *f;
	return 0;
}
