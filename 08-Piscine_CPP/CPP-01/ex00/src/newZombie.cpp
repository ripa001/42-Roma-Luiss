#include "../include/Zombie.hpp"

Zombie*	newZombie( std::string name )
{
	Zombie *my_zombie = new Zombie(name);
	return (my_zombie);
}
