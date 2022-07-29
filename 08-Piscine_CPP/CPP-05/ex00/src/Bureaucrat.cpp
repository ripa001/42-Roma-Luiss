/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:18:50 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:18:50 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: name(name)
	, grade(grade) {
	if (grade > 150)
		throw GradeTooLowException();
	else if (grade < 1)
		throw GradeTooHighException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade) {}

Bureaucrat::~Bureaucrat() {}

const std::string&	Bureaucrat::getName() const {
	return name;
}

int	Bureaucrat::getGrade() const {
	return grade;
}

void	Bureaucrat::incrementGrade(int change)
{
	if (this->grade - change < 1)
		throw GradeTooHighException();
	this->grade -= change;
}

void	Bureaucrat::decrementGrade(int change)
{
	
	if (this->grade + change > 150)
		throw GradeTooLowException();
	this->grade += change;
}

const char*	Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat grade too low!";
}

const char*	Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat grade too high!";
}

std::ostream& operator<<(std::ostream & os, Bureaucrat const & i) {
	return (os << (i.getName()) << ", bureaucrat grade " << (i.getGrade())) << std::endl;
}