# include "../include/Zombie.hpp"

Zombie::Zombie( void ) : _name("") {
	return ;
}

Zombie::Zombie(std::string name) : _name(name) {
	return ;
}

Zombie::~Zombie( void ) {
	std::cout << "Sto distruggendo Zombie: " << _name << std::endl;
	return ;
}

void Zombie::setName(std::string name) {
	_name = name;
}

void Zombie::announce( void ) {
	std::cout << _name << ": BraiiiiiiinnnzzzZ...\n";
}
