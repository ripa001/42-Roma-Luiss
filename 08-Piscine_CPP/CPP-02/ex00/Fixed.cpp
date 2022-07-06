#include "Fixed.hpp"

Fixed::Fixed( void ) : _numberValue(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed) {
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed &fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->_numberValue = fixed.getRawBits();
	return (*this);
}
int	Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_numberValue);
}

void Fixed::setRawBits(int const raw) {
	this->_numberValue = raw;
}

