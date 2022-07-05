
#include "../include/ScavTrap.hpp"

ScavTrap::ScavTrap( void ) : _name("Default"), _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage)
{
	std::cout << "Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : _name(name), _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage)
{
	std::cout << "Name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ClapTrap& clapTrap) : _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage)
{
	*this = clapTrap;
	std::cout << "Copy constructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to attack!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	this->_attackDamage++;
	std::cout << "ScavTrap " << getName() << " attacks " << target
	<< ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

ClapTrap&	ClapTrap::operator=(ClapTrap const &other)
{
	this->_name = other._name;
	this->_hitPoints = other._hitPoints;
	this->_energyPoints = other._energyPoints;
	this->_attackDamage = other._attackDamage;
	return *this;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap is now in Gate keeper mode." << std::endl;
}

ClapTrap::~ClapTrap( void )
{
	std::cout << "Destructor called" << std::endl;
	return ;
}
