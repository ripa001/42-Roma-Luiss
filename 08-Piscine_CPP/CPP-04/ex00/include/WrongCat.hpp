#ifndef  WRONGCAT_CLASS_HPP
# define WRONGCAT_CLASS_HPP

#include <iostream>
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		WrongCat( void );
		WrongCat(const WrongCat& cat);
		WrongCat&	operator=(WrongCat const &other);
		void 	makeSound( void ) const;
		~WrongCat( void );
};

#endif