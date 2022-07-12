#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain*	brain;
	public:
		Dog( void );
		Dog(const Dog& animal);
		Dog&	operator=(Dog const &other);
		Brain*	getBrain( void ) const;
		void makeSound( void ) const;
		~Dog( void );
};

#endif