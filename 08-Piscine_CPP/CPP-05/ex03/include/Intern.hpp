/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:22:58 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:22:58 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_CLASS_HPP
# define INTERN_CLASS_HPP

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Form;

class Intern
{
	private:
		// Form	*makeShrubberyCreationForm(std::string target);
		// Form	*makePresidentialPardonForm(std::string target);
		// Form	*makeRobotomyRequestForm(std::string target);

	public:
		Form	*makeForm(std::string name, std::string target);
		
		Intern();
		Intern(Intern& other);
		virtual ~Intern();

		Intern &operator=(Intern &equals);
};

#endif