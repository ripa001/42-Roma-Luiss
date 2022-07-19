/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:43 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/19 19:24:25 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AMateria.hpp"

AMateria::AMateria( void ) : _type("AMateria") {
	std::cout << "AMateria constructor called" << std::endl;
}

AMateria::AMateria(const AMateria& aMateria) {
	*this = aMateria;
	std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria::AMateria(const std::string& type): _type(type) {
	std::cout << "AMateria constructor called" << std::endl;
}

std::string const & AMateria::getType( void ) const{
	return this->_type;
}

void	AMateria::setType(std::string type) {
	this->_type = type;
}


void AMateria::use(ICharacter& target)
{
	(void)target;
}

AMateria&	AMateria::operator=(AMateria const &other) {
	this->_type = other._type;
	return *this;
}

AMateria::~AMateria( void ) {
	std::cout << "AMateria destructor called" << std::endl;
	return ;
}
