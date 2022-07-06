#include "../include/Zombie.hpp"

int	main( void ) {
	Zombie *zombies;

	zombies = zombieHorde(20, "zombie1");
	
	for (int i = 0; i < 20; i++)
		zombies[i].announce();

	delete [] zombies;

	return (0);
}