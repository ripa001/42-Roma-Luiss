/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:24 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:25 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"

WrongAnimal::WrongAnimal( void ) : type("WrongAnimal") {
	std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& wrongAnimal) {
	*this = wrongAnimal;
	std::cout << "WrongAnimal copy constructor called" << std::endl;
}

std::string	WrongAnimal::getType( void ) const{
	return this->type;
}


WrongAnimal&	WrongAnimal::operator=(WrongAnimal const &other) {
	this->type = other.type;
	return *this;
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "I'm just a simple WrongAnimal! I can't make a sound!" << std::endl;
}

WrongAnimal::~WrongAnimal( void ) {
	std::cout << "WrongAnimal destructor called" << std::endl;
	return ;
}
