#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat( void );
		Cat(const Cat& cat);
		Cat&	operator=(Cat const &other);
		void 	makeSound( void ) const;
		~Cat( void );
};

#endif