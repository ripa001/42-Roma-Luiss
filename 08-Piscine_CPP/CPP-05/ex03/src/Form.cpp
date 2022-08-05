/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:00:34 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 13:00:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Form.hpp"

Form::Form() : isSigned(false), gradeToSign(0), gradeToExecute(0) {}

Form::Form(const std::string& name, const std::string& target, int gradeSign, int gradeToExecute)
	: name(name)
	, target(target)
	, isSigned(false)
	, gradeToSign(gradeSign)
	, gradeToExecute(gradeToExecute) {
	if (gradeToSign > 150  || gradeToExecute > 150)
		throw GradeTooLowException();
	else if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
}

Form::Form(const Form& other) : name(other.name), target(other.target), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

Form::~Form() {}

const std::string&	Form::getName() const {
	return name;
}

const std::string&	Form::getTarget() const {
	return target;
}

int	Form::getGradeToSign() const {
	return gradeToSign;
}

bool	Form::getIsSigned() const {
	return isSigned;
}

int	Form::getGradeToExecute() const {
	return gradeToExecute;
}


void	Form::beSigned(const Bureaucrat& bureaucrat) {
	if (isSigned)
		throw AlreadySignedException();
	if (gradeToSign < bureaucrat.getGrade())
		throw GradeTooLowException();
	this->isSigned = true;
}

void Form::executeConcrete() const{}

void	Form::execute(const Bureaucrat& executor) const {
	if (!isSigned)
		throw ExecuteUnsignedException();
	if (gradeToExecute < executor.getGrade())
		throw GradeTooLowException();
	executeConcrete();
}

const char*	Form::GradeTooLowException::what() const throw() {
	return "<Form> grade too low";
}

const char*	Form::GradeTooHighException::what() const throw() {
	return "<Form> grade too High!";
}

const char*	Form::AlreadySignedException::what() const throw() {
	return "<Form> cannot sign a form twice!";
}

const char*	Form::ExecuteUnsignedException::what() const throw() {
	return "<Form> cannot execute an unsigned form!";
}

std::ostream& operator<<(std::ostream & os, Form const & i) {
	return (os << (i.getName()) << ", form signed: " << (i.getIsSigned()) << ", grade to sign it " << (i.getGradeToSign()) << ", to execute it " << (i.getGradeToExecute()) << std::endl);
}