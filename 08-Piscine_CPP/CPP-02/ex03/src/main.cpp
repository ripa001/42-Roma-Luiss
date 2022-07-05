#include <iostream>
#include "../include/Fixed.hpp"
#include "../include/Point.hpp"

int main( void ) {
	std::cout << "Point(15, 100) in Triangle 10.5 - 203, 10 - 20, 135 - 20" << std::endl << "Result: "
	<< bsp(Point(10,20), Point(10.5,203), Point(135,20),  Point(15, 100)) << std::endl;
	std::cout << "Point(5, 100) in Triangle 10.5 - 203, 10 - 20, 135 - 20" << std::endl << "Result: "
	<< bsp(Point(10,20), Point(10.5,203), Point(135,20),  Point(5, 100)) << std::endl;
	std::cout << "Point(15, 1) in Triangle 10.5 - 203, 10 - 20, 135 - 20" << std::endl << "Result: "
	<< bsp(Point(10,20), Point(10.5,203), Point(135,20),  Point(15, 1)) << std::endl;
}
