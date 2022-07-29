/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:41 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:42 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

Animal::Animal( void ) : type("Animale") {
	std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal& animal) {
	*this = animal;
	std::cout << "Animal copy constructor called" << std::endl;
}

std::string	Animal::getType( void ) const{
	return this->type;
}


Animal&	Animal::operator=(Animal const &other) {
	this->type = other.type;
	return *this;
}

void	Animal::makeSound(void) const {
	std::cout << "I'm just a simple Animal! I can't make a sound!" << std::endl;
}

Animal::~Animal( void ) {
	std::cout << "Animal destructor called" << std::endl;
	return ;
}
