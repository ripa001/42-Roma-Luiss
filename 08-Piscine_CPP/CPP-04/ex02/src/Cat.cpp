/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:11 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 12:07:11 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat( void ) {
	std::cout << "Cat constructor called" << std::endl;
	type = "Cat";
	brain = new Brain();
}

Cat::Cat(const Cat& cat) {
	*this = cat;
	// this->brain = new Brain(*cat.getBrain());
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat&	Cat::operator=(Cat const &other) {
	this->type = other.type;
	this->brain = new Brain(*other.getBrain());
	return *this;
}

Brain*	Cat::getBrain( void ) const {
	return brain;
}

void	Cat::makeSound( void ) const {
	std::cout << "Miao miao!" << std::endl;
}

Cat::~Cat( void ) {
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
	return ;
}
