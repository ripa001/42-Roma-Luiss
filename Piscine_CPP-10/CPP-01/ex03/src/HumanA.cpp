# include "../include/HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), weapon(weapon)
{
	return ;
}

HumanA::~HumanA(void)
{
	std::cout << "Sto distruggendo HumanA: " << _name << std::endl;
	return ;
}

void HumanA::attack(void)
{
	std::cout << _name << " attacks with their " << this->weapon.getType() << std::endl;
}

