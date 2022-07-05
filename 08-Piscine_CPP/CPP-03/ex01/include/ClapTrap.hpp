#ifndef CLAPTRAP_CLASS_HPP
# define CLAPTRAP_CLASS_HPP

#include <iostream>

class ClapTrap {

	private:
		std::string _name;
		static const int	_maxHitPoints = 100;
		static const int	_maxEnergyPoints = 50;
		static const int	_maxAttackDamage = 20;
		int			_hitPoints;
		int			_energyPoints;
		int			_attackDamage;
	public:
		ClapTrap(std::string name);
		ClapTrap(void);
		ClapTrap(const ClapTrap& clapTrap);
		ClapTrap&	operator=(ClapTrap const &other);
		int			getHitPoint(void);
		int			getEnergyPoint(void);
		int			getAttackDamage(void);
		std::string	getName(void);
		void		addEnergyPoint(int value);
		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);
		~ClapTrap(void);
};

#endif