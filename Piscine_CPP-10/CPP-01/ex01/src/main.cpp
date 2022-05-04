#include "../include/Zombie.hpp"

int	main(void)
{
	Zombie *zombies;

	zombies = zombieHorde(200, "zombie1");
	
	for (int i = 0; i < 200; i++)
		zombies[i].announce();

	delete [] zombies;

	return (0);
}