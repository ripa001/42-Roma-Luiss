#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog( void );
		Dog(const Dog& animal);
		Dog&	operator=(Dog const &other);
		void makeSound( void ) const;
		~Dog( void );
};

#endif