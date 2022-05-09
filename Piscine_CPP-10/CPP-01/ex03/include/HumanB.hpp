#ifndef HUMANB_CLASS_HPP
# define HUMANB_CLASS_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB {

	public:
		HumanB(std::string name);
		HumanB( void );
		~HumanB(void);

		void	attack( void );
		void 	setWeapon(Weapon &weapon);

	private:
		Weapon		*weapon;
		std::string _name;
};

#endif