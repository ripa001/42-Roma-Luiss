#ifndef POINT_CLASS_HPP
# define POINT_CLASS_HPP

#include "Fixed.hpp"

class Point {

	private:
		Fixed const _x;
		Fixed const _y;
	public:
		Point(const float x, const float y);
		Point( void );
		Point(const Point &obj);
		Fixed const &getX( void ) const;
		Fixed const &getY( void ) const;
		Point& operator=(const Point &point);
		~Point( void );


};
std::ostream& operator<<(std::ostream & os, Point const & i);
bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif