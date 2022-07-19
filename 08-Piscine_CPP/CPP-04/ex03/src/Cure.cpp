/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:12:15 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 13:12:15 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cure.hpp"

Cure::Cure( void ) : AMateria("cure") {
	std::cout << "Cure constructor called" << std::endl;
}

Cure::Cure(Cure &copy) : AMateria() {
	*this = copy;
	std::cout << "Cure copy constructor called" << std::endl;
}

Cure&	Cure::operator=(Cure const &other) {
	this->_type = other._type;
	return *this;
}

Cure*	Cure::clone() const
{
	Cure	*cure = new Cure();

	return (cure);
}

void	Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

Cure::~Cure( void ) {
	std::cout << "Cure destructor called" << std::endl;
	return ;
}
