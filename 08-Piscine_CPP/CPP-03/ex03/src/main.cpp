#include "../include/DiamondTrap.hpp"

int	main() {
	// DiamondTrap	DT1("Pippo"), DT2("Pluto"), DT3("Gigi"), def;

	// DT1 = DT2;

	// DT1.attack("Pluto");
	// DT2.takeDamage(100);
	// DT3.beRepaired(42);

	// DT3 = DiamondTrap("Gigi");
	// DT3.guardGate();
	// DT1.highFivesGuys();

	// DT2.whoAmI();

	std::cout << "------- FragTrap | Max 100HP - 100 energy Points  -------" << std::endl;
	ScavTrap a("Pippo");
	ScavTrap b;
	FragTrap c("Pluto");
	FragTrap d("Gigi");
	DiamondTrap	e("AIoT");
	DiamondTrap	f("Ripa");

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

	a.guardGate();
	a.guardGate();

	d.highFivesGuys();

	f.attack(e.getName());
	e.takeDamage(f.getAttackDamage());

	f.whoAmI();
	std::cout << "**** Destructor ****" << std::endl;
}