#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain*	brain;
	public:
		Cat( void );
		Cat(const Cat& cat);
		Cat&	operator=(Cat const &other);
		Brain*	getBrain( void ) const;
		void 	makeSound( void ) const;
		~Cat( void );
};

#endif