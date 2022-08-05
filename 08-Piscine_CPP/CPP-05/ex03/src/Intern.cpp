/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:49:53 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/05 14:49:53 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Intern.hpp"

Intern::Intern( void ) {}

Intern::Intern(Intern& other) {
	*this = other;
}

Intern::~Intern() {}

Intern &Intern::operator=(Intern &equals)
{
	(void) equals;
	return (*this);

}

static Form*	makePresidentialPardonForm(std::string const & target);
static Form*	makeRobotomyRequestForm(std::string const & target);
static Form*	makeShrubberyCreationForm(std::string const & target);

Form	*Intern::makeForm(std::string name, std::string target)
{
	Form* form;
	typedef Form* (*func)(std::string const & target);
	typedef struct { std::string form_name; func function; } FormTypes;
	
	
	form = NULL;
	FormTypes	forms[] = 
	{
		{"presidential pardon", &makePresidentialPardonForm},
		{"robotomy request", &makeRobotomyRequestForm},
		{"shrubbery creation", &makeShrubberyCreationForm}
	};

	for (int i = 0; i < 3; i++)
		if (forms[i].form_name == name)
		{
			form = forms[i].function(target); // function corrisponde alla funzione nella struct forms
			std::cout << "Intern creates " << form->getName() << std::endl;
			return (form);
		}
	std::cout << "Intern is not able to create the form asked." << std::endl;
	return (form);
}



// FUNCTIONS SUP ===============================================================

static Form*	makePresidentialPardonForm(std::string const & target) { return (new PresidentialPardonForm(target)); }
static Form*	makeRobotomyRequestForm(std::string const & target) { return (new RobotomyRequestForm(target)); }
static Form*	makeShrubberyCreationForm(std::string const & target) { return (new ShrubberyCreationForm(target)); }

// =============================================================================
