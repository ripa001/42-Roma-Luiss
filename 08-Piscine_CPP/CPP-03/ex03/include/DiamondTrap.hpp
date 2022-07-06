#ifndef DIAMONDTRAP_CLASS_HPP
# define DIAMONDTRAP_CLASS_HPP

#include <iostream>
#include "FragTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
	private:
		bool				_isInKeeperMode;
		std::string			_name;
		static const int	_maxHitPoints = FragTrap::_maxHitPoints;
		static const int	_maxEnergyPoints = ScavTrap::_maxEnergyPoints;
		static const int	_maxAttackDamage = FragTrap::_maxAttackDamage;
	public:
		DiamondTrap(std::string name);
		DiamondTrap( void );
		DiamondTrap(DiamondTrap& diamondTrap);
		DiamondTrap& operator=(DiamondTrap& equals);
		void whoAmI( void );
		void attack(const std::string& target);
		void highFivesGuys( void );
		~DiamondTrap( void );
};

#endif
