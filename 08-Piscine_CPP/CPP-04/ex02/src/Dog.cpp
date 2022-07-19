/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 17:52:23 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog( void ) {
	std::cout << "Dog constructor called" << std::endl;
	type = "Dog";
	brain = new Brain();
}

Dog::Dog(const Dog& dog) {
	*this = dog;
	this->brain = new Brain(*dog.getBrain());
	std::cout << "Dog copy constructor called" << std::endl;
}

Brain*	Dog::getBrain( void ) const {
	return brain;
}

Dog&	Dog::operator=(Dog const &other) {
	this->type = other.type;
	this->brain = new Brain(*other.getBrain());
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
