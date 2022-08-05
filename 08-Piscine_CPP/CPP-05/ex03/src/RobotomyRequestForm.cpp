/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:35:26 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/31 12:35:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): Form("RobotomyRequestForm", "default", 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : Form("RobotomyRequestForm", target, 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : Form(other){
	*this = other;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	if (this != &other) {}
	return *this;
}

void	RobotomyRequestForm::executeConcrete() const {
	std::cout << "* LOUD DRILLING NOISES *" << std::endl << this->getTarget();
	srand(time(NULL));
	if (rand() % 2)
		std::cout << " has been successfully robotimized!" << std::endl;
	else
		std::cout << " had some problems and its robotomy failed!" << std::endl;
}