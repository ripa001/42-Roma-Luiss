#ifndef KAREN_CLASS_HPP
# define KAREN_CLASS_HPP

#include <iostream>

class Karen
{
	public:
		Karen( std::string level );
		~Karen( void );
		void complain( std::string level );

	private:
		std::string 	levelFilter;
		void	debug( void );
		void	info( void );
		void	warning( void );
		void	error( void );
};

#endif