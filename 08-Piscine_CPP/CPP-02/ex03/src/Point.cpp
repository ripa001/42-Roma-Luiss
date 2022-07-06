#include "../include/Point.hpp"

Point::Point( void ) : _x(Fixed(0)), _y(Fixed(0)){}

Point::Point(const float x, const float y) : _x(Fixed(x)), _y(Fixed(y)){}

Point::Point(const Point &point) {
	*this = point;
}

Fixed const &Point::getX( void ) const {
	return _x;
}

Fixed const &Point::getY( void ) const {
	return _y;
}

std::ostream& operator<<(std::ostream & os, Point const & i) {
	return (os << i.getX() << "," << i.getY());
}

Point&	Point::operator=(Point const &other) {
	( void ) other;
	return *this;
}

Point::~Point( void ){}
