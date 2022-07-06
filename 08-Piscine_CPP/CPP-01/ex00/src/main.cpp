#include "../include/Zombie.hpp"

int	main( void ) {
	Zombie *zombie1;
	Zombie *zombie2;

	zombie1 = newZombie("zombie1");
	zombie2 = newZombie("zombie2");

	randomChump("zombie3");

	zombie2->announce();
	zombie1->announce();

	delete zombie1;
	delete zombie2;

	return (0);
}