#include "../include/Karen.hpp"

Karen::Karen( std::string level ) : levelFilter(level)
{
}

Karen::~Karen( void )
{
}

void	Karen::debug( void )
{
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pic"
		"kle-special-ketchup burger. I just love it!" << std::endl;
}
void	Karen::info( void )
{
	std::cout << "I cannot believe adding extra bacon cost more money. You don’"
		"t put enough! If you did I would not have to ask for it!" << std::endl;
}
void	Karen::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve bee"
		"n coming here for years and you just started working here last month."
		<< std::endl;
}
void	Karen::error( void )
{
	std::cout << "This is unacceptable, I want to speak to the manager now."
		<< std::endl;
}

void	Karen::complain( std::string level )
{
	int		flag = 0;
	void	(Karen::*complain[])( void ) = {
		&Karen::debug,
		&Karen::info,
		&Karen::warning,
		&Karen::error
	};
	std::string complainLevels[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
	std::transform(levelFilter.begin(), levelFilter.end(), levelFilter.begin(), ::toupper);
	for (int i = 0; i < 4; i++)
	{	
		if (levelFilter == complainLevels[i])
			flag = 1;
		void (Karen::*tmpComplain)( void ) = complain[i];
		if (level == complainLevels[i] && flag)
			(this->*tmpComplain)();
	}
	if (!flag)
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
}