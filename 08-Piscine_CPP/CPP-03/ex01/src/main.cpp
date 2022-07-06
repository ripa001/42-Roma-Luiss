#include <iostream>
#include "../include/ScavTrap.hpp"

int main( void ) {
	
	std::cout << "------- ScavTrap | Max 100HP - 50 energy Points  -------" << std::endl << std::endl;
	ClapTrap a("Pippo");
	ClapTrap b;
	ScavTrap c("Pluto");
	ScavTrap d("Gino");

	std::cout << "**** Testing ****  " << std::endl;

	a.attack(b.getName());
	b.takeDamage(a.getAttackDamage());

	b.attack(c.getName());
	c.takeDamage(b.getAttackDamage());

	d.attack(a.getName());
	a.takeDamage(d.getAttackDamage());

	a.beRepaired(2);
	b.beRepaired(3);
	c.beRepaired(4);

	d.guardGate();
	d.guardGate();
	std::cout << "**** Destructor ****" << std::endl;
}