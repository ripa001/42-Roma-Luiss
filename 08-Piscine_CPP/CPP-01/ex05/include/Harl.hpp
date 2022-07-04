#ifndef HARL_CLASS_HPP
# define HARL_CLASS_HPP

#include <iostream>
#include <string>

class Harl
{
	public:
		Harl( void );
		~Harl( void );
		void complain( std::string level );

	private:
		void	debug( void );
		void	info( void );
		void	warning( void );
		void	error( void );
};

#endif