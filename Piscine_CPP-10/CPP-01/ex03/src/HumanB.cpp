# include "../include/HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name)
{
	return ;
}

HumanB::HumanB( void )  : _name("Undefined")
{
	return ;
}

HumanB::~HumanB(void)
{
	std::cout << "Sto distruggendo HumanB: " << _name << std::endl;
	return ;
}

void HumanB::attack(void)
{
	std::cout << _name << " attacks with their " << this->weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
}
