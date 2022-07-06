#ifndef WEAPON_CLASS_HPP
# define WEAPON_CLASS_HPP

#include <iostream>

class Weapon {

	public:
		Weapon(std::string name);
		Weapon( void );
		~Weapon( void );

		const std::string	&getType( void );
		void				setType(std::string name);

	private:
		std::string type;
};

	Weapon*	WeaponHorde( int N, std::string name );
	Weapon*	newWeapon( std::string name );
	void	randomChump( std::string name );

#endif