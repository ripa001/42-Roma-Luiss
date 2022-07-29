/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:26 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

WrongCat::WrongCat( void ) : WrongAnimal() {
	std::cout << "WrongCat constructor called" << std::endl;
	type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& cat) : WrongAnimal() {
	*this = cat;
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat&	WrongCat::operator=(WrongCat const &other) {
	this->type = other.type;
	return *this;
}

void	WrongCat::makeSound( void ) const {
	std::cout << "Miao miao!" << std::endl;
}

WrongCat::~WrongCat( void ) {
	std::cout << "WrongCat destructor called" << std::endl;
	return ;
}
