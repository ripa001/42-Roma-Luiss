#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

#include <iostream>

class Fixed {

	public:
		Fixed &operator= (const Fixed &obj);
		Fixed( void );
		Fixed(const Fixed &obj);
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		~Fixed( void );

	private:
		int					_numberValue;
		static const int	_fractBits = 8;

};

#endif