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
		static Fixed &max(Fixed &a, Fixed &b);
		static Fixed &min(Fixed &a, Fixed &b);
		static const Fixed &max(Fixed const &a, Fixed const &b);
		static const Fixed &min(Fixed const &a, Fixed const &b);
		bool operator!= (const Fixed &fixed);
		bool operator>= (const Fixed &fixed);
		bool operator> (const Fixed &fixed);
		bool operator< (const Fixed &fixed);
		bool operator<= (const Fixed &fixed);
		bool operator== (const Fixed &fixed);
		Fixed operator+ (const Fixed &fixed);
		Fixed operator- (const Fixed &fixed);
		Fixed operator/ (const Fixed &fixed);
		Fixed operator* (const Fixed &fixed);
		Fixed operator-- (int);
		Fixed operator++ (int);
		Fixed &operator++ ();
		Fixed &operator-- ();

		~Fixed( void );

	private:
		int					_numberValue;
		static const int	_fractBits = 8;

};
std::ostream& operator<<(std::ostream & os, Fixed const & i);

#endif