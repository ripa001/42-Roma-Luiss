#include "Fixed.hpp"

Fixed::Fixed(int i) : fixed_point(i)
{
	std::cout << "Default constructor called" << std::endl;
	*this = fixed;
}

Fixed::Fixed(constr Fixed &fixed)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_numberValue);
}

Fixed& Fixed::operator=(const Fixed &fixed)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->_numberValue = getRawBits();
	return (*this);
}

