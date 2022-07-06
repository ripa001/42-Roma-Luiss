# include "../include/Weapon.hpp"

Weapon::Weapon( void ) : type("") {
	return ;
}

Weapon::Weapon(std::string tempType) : type(tempType) {
	return ;
}

Weapon::~Weapon( void ) {
	return ;
}

void Weapon::setType(std::string tempType) {
	type = tempType;
}

const std::string &Weapon::getType( void ) {
	const std::string &TYPE = type;
	return (TYPE);
}
