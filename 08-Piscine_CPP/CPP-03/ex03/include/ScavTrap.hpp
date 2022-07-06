#ifndef SCAVTRAP_CLASS_HPP
# define SCAVTRAP_CLASS_HPP

#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	protected:
		bool				_isInKeeperMode;
		static const int	_maxHitPoints = 100;
		static const int	_maxEnergyPoints = 50;
		static const int	_maxAttackDamage = 20;
	public:
		ScavTrap(std::string name);
		ScavTrap( void );
		ScavTrap(ScavTrap& scavTrap);
		ScavTrap& operator=(ScavTrap& equals);
		bool getKeeperMode();
		void attack(const std::string& target);
		void guardGate();
		~ScavTrap( void );
};

#endif