#include "../include/Harl.hpp"

Harl::Harl() {
}

Harl::~Harl( void ) {
}

void	Harl::debug( void ) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pic"
		"kle-special-ketchup burger. I just love it!" << std::endl;
}

void	Harl::info( void ) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon cost more money. You don’"
		"t put enough! If you did I would not have to ask for it!" << std::endl;
}

void	Harl::warning( void ) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. I’ve bee"
		"n coming here for years and you just started working here last month." << std::endl;
}

void	Harl::error( void ) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable, I want to speak to the manager now." << std::endl;
}


void	Harl::execute( int l ) {
	 void	(Harl::*complain[])( void ) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};
	for (int i = 0; i < 5; i++)
	{
		void (Harl::*tmpComplain)( void ) = complain[i];
		if (i >= l)
			(this->*tmpComplain)();
	}
}

void	Harl::complain( std::string level ) {
	int i = 0;

	std::transform(level.begin(), level.end(), level.begin(), ::toupper);
	i = level.compare("DEBUG") ? i : 1;
	i = level.compare("INFO") ? i : 2;
	i = level.compare("WARNING") ? i : 3;
	i = level.compare("ERROR") ? i : 4;
	switch (i)
	{
	case 1:
		Harl::debug();
	case 2:
		Harl::info();
	case 3:
		Harl::warning();
	case 4:
		Harl::error();
		break ;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
		break ;
	}
}