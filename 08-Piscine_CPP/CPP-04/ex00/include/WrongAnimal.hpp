#ifndef WRONGANIMAL_CLASS_HPP
# define WRONGANIMAL_CLASS_HPP

#include <iostream>

class WrongAnimal {
	protected:
		std::string type;
	public:
		WrongAnimal( void );
		WrongAnimal(const WrongAnimal& wrongAnimal);
		std::string		getType( void ) const;
		WrongAnimal&			operator=(WrongAnimal const &other);
		void	makeSound( void ) const;
		~WrongAnimal( void );
};

#endif