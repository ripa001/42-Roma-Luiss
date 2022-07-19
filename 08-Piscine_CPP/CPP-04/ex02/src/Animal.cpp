/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:06 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 17:48:37 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

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
