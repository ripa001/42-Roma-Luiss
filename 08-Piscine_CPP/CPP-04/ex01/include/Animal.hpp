#ifndef ANIMAL_CLASS_HPP
# define ANIMAL_CLASS_HPP

#include <iostream>

class Animal {
	protected:
		std::string type;
	public:
		Animal( void );
		Animal(const Animal& animal);
		std::string		getType( void ) const;
		Animal&			operator=(Animal const &other);
		virtual void	makeSound( void ) const;
		virtual ~Animal( void );
};

#endif