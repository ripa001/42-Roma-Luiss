#ifndef HUMANA_CLASS_HPP
# define HUMANA_CLASS_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA {

	public:
		HumanA(std::string name, Weapon &weapon);
		HumanA( void );
		~HumanA( void );

		void	attack( void );

	private:
		std::string _name;
		Weapon		&weapon;
};

#endif