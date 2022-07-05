#include <iostream>
#include "../include/Fixed.hpp"
#include "../include/Point.hpp"

int main( void ) {
	const Point a = Point(10,20);
	const Point b = Point(10.5,203);
	const Point c = Point(135,20);
	const Point x = Point(15, 100);
	std::cout << "Point " << x << "\tTriangle: " << a << " " << b << " " << c << std::endl << "Result: "  
	<< bsp(Point(10,20), Point(10.5,203), Point(135,20),  Point(15, 100)) << std::endl;
}
