/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:31 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/19 20:24:03 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Ice.hpp"

Ice::Ice( void ) : AMateria("ice") {
	std::cout << "Ice constructor called" << std::endl;
}

Ice::Ice(Ice &copy): AMateria() {
	*this = copy;
	std::cout << "Ice copy constructor called" << std::endl;
}

Ice&	Ice::operator=(Ice const &other) {
	this->_type = other._type;
	return *this;
}

Ice*	Ice::clone() const
{
	Ice	*ice = new Ice();

	return (ice);
}

void	Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

Ice::~Ice( void ) {
	std::cout << "Ice destructor called" << std::endl;
	return ;
}
