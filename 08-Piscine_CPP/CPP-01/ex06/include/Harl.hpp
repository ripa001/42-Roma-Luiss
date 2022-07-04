#ifndef HARL_CLASS_HPP
# define HARL_CLASS_HPP

#include <iostream>

class Harl
{
	public:
		Harl( void );
		~Harl( void );
		void	complain( std::string level );
		void	execute( int l );


	private:
		std::string 	levelFilter;
		void	debug( void );
		void	info( void );
		void	warning( void );
		void	error( void );
};

#endif