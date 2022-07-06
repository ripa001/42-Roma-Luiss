#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

#include <iostream>
#include <cmath>

class Fixed {

	public:
		Fixed &operator= (const Fixed &obj);
		Fixed(const int val);
		Fixed(const float val);
		Fixed( void );
		Fixed(const Fixed &obj);
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		float toFloat( void ) const;
		int toInt( void ) const;
		~Fixed( void );

	private:
		int					_numberValue;
		static const int	_fractBits = 8;

};
std::ostream& operator<<(std::ostream & os, Fixed const & i);

#endif