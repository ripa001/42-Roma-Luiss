/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:46 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:48 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog( void ) : Animal() {
	std::cout << "Dog constructor called" << std::endl;
	type = "Dog";
	brain = new Brain();
}

Dog::Dog(const Dog& dog) : Animal() {
	*this = dog;
	this->brain = new Brain(*dog.getBrain());
	std::cout << "Dog copy constructor called" << std::endl;
}

Brain*	Dog::getBrain( void ) const {
	return brain;
}

Dog&	Dog::operator=(Dog const &other) {
	this->type = other.type;
	this->brain = other.brain;
	return *this;
}

void	Dog::makeSound( void ) const {
	std::cout << "Woaf woaf!" << std::endl;
}

Dog::~Dog( void ) {
	std::cout << "Dog destructor called" << std::endl;
	delete brain;
	return ;
}
