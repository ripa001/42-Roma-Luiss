#include "../include/Dog.hpp"

Dog::Dog( void ) : Animal() {
	std::cout << "Dog constructor called" << std::endl;
	type = "Dog";
}

Dog::Dog(const Dog& dog) : Animal() {
	*this = dog;
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog&	Dog::operator=(Dog const &other) {
	this->type = other.type;
	return *this;
}

void	Dog::makeSound( void ) const {
	std::cout << "Woaf woaf!" << std::endl;
}

Dog::~Dog( void ) {
	std::cout << "Dog destructor called" << std::endl;
	return ;
}
