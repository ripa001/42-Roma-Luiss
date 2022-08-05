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

#include "../include/Intern.hpp"

static void testForm(Bureaucrat& bur, Form* form)
{
    std::cout << std::endl << "Sign & Execute \033[33m" << form->getName() << "\033[0m : " << std::endl;
    bur.signForm(*form);
    bur.executeForm(*form);
}

static void testIntern(Intern& intern, const std::string &form_name, const std::string &target_name)
{
    Bureaucrat sign("Bob", 1);
    Form *totest = NULL;

    std::cout << std::endl;
    totest = intern.makeForm(form_name, target_name);

    if (totest)
    {
        testForm(sign, totest);
        delete totest;
    }
}

int main()
{
    Intern someRandomIntern;

    std::cout << std::endl << "\033[31mNormal\033[0m tests : " << std::endl;
    testIntern(someRandomIntern, "presidential pardon", "Michelon");
    testIntern(someRandomIntern, "robotomy request", "Bender");
    testIntern(someRandomIntern, "shrubbery creation", "Maison");

    std::cout << std::endl << "\033[31mDoesn't exist\033[0m tests : " << std::endl;
    testIntern(someRandomIntern, "doesn't exist", "NOP");

    return (0);
}