/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:18 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:18 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat( void ) : Animal() {
	std::cout << "Cat constructor called" << std::endl;
	type = "Cat";
}

Cat::Cat(const Cat& cat) : Animal() {
	*this = cat;
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat&	Cat::operator=(Cat const &other) {
	this->type = other.type;
	return *this;
}

void	Cat::makeSound( void ) const {
	std::cout << "Miao miao!" << std::endl;
}

Cat::~Cat( void ) {
	std::cout << "Cat destructor called" << std::endl;
	return ;
}
