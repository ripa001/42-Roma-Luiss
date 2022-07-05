#ifndef SCAVTRAP_CLASS_HPP
# define SCAVTRAP_CLASS_HPP

#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

	private:

	public:
		ScavTrap(std::string name);
		ScavTrap(void);
		ScavTrap(const ClapTrap& clapTrap);
		void guardGate();
		~ScavTrap(void);
};

#endif