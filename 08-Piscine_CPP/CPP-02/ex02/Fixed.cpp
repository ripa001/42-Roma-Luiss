#include "Fixed.hpp"

Fixed::Fixed( void ) : _numberValue(0){}

Fixed::Fixed(const int val) : _numberValue(val << this->_fractBits){}

Fixed::Fixed(const float val) : _numberValue(roundf(val * (1 << this->_fractBits))){}

Fixed::Fixed(const Fixed &fixed) {
	*this = fixed;
}

Fixed::~Fixed( void ){}

Fixed& Fixed::operator=(const Fixed &fixed) {
	this->_numberValue = fixed.getRawBits();
	return (*this);
}

int	Fixed::getRawBits( void ) const {
	return (this->_numberValue);
}

void Fixed::setRawBits(int const raw) {
	this->_numberValue = raw;
}

int	Fixed::toInt( void ) const {
	return (this->_numberValue >> this->_fractBits);
}

float	Fixed::toFloat( void ) const {
	return ((float)this->_numberValue / ( 1 << this->_fractBits));
}

std::ostream& operator<<(std::ostream & os, Fixed const & i) {
	return (os << (i.toFloat()));
}

Fixed & Fixed::operator++() //++a {
	_numberValue++;
	return(* this);
}

Fixed Fixed::operator++ (int) //a++ {
	Fixed temp = *this;
	++*this;
	return (temp);
}

Fixed & Fixed::operator-- () //--a {
	_numberValue--;
	return(* this);
}

Fixed Fixed::operator-- (int) //a-- {
	Fixed temp = *this;
	--*this;
	return (temp);
}

Fixed Fixed::operator* (const Fixed &fixed) {
	Fixed ret;

	ret.setRawBits(((this->_numberValue) * (fixed._numberValue)) >> 8);
	return (ret);
}

Fixed Fixed::operator/ (const Fixed &fixed) {
	Fixed ret(this->toFloat() / fixed.toFloat());
	return (ret);
}

Fixed Fixed::operator- (const Fixed &fixed) {
	Fixed ret;

	ret.setRawBits(_numberValue - fixed._numberValue);
	return (ret);
}

Fixed Fixed::operator+ (const Fixed &fixed) {
	Fixed ret;

	ret.setRawBits(_numberValue + fixed._numberValue);
	return (ret);
}

bool Fixed::operator== (const Fixed &fixed) {
	return (_numberValue == fixed._numberValue);
}

bool Fixed::operator<= (const Fixed &fixed) {
	return (_numberValue <= fixed._numberValue);
}

bool Fixed::operator< (const Fixed &fixed) {
	return (_numberValue < fixed._numberValue);
}

bool Fixed::operator> (const Fixed &fixed) {
	return (_numberValue > fixed._numberValue);
}

bool Fixed::operator>= (const Fixed &fixed) {
	return (_numberValue >= fixed._numberValue);
}

bool Fixed::operator!= (const Fixed &fixed) {
	return (_numberValue != fixed._numberValue);
}

Fixed & Fixed::max(Fixed &a, Fixed &b) {
	return (a._numberValue > b._numberValue ? a : b);
}

Fixed & Fixed::min(Fixed &a, Fixed &b) {
	return (a._numberValue < b._numberValue ? a : b);
}

const Fixed & Fixed::max(Fixed const &a, Fixed const &b) {
	return (a._numberValue > b._numberValue ? a : b);
}

const Fixed & Fixed::min(Fixed const &a, Fixed const &b) {
	return (a._numberValue < b._numberValue ? a : b);
}
