#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

#include <iostream>

class Fixed {

	public:
		Fixed(int i) ;
		Fixed(void) : fixed_point(0) ;
		Fixed(const Fixed &obj);
		Fixed &operator= (const Fixed &obj);
		~Fixed(void);

	private:
		int					_numberValue;
		static const int	_fractBits = 8;

};

#endif