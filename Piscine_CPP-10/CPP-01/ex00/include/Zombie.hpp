#ifndef ZOMBIE_CLASS_HPP
# define ZOMBIE_CLASS_HPP

#include <iostream>

class Zombie {

	public:
		Zombie(std::string name);
		Zombie(void);
		~Zombie(void);

		void	announce( void );

	private:
		std::string _name;
};


	Zombie*	newZombie( std::string name );
	void	randomChump( std::string name );

#endif