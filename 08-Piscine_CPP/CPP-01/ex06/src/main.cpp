#include "../include/Harl.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc == 2)
	{
		Harl harl;
		harl.complain(argv[1]);
	}
	else
		std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;




}