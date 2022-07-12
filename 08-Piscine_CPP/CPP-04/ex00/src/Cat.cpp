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
