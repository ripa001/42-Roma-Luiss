#include "../include/Karen.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		Karen karen(argv[1]);
		std::cout << "[ DEBUG ]" << std::endl;
		karen.complain("DEBUG");
		std::cout << "[ INFO ]" << std::endl;
		karen.complain("INFO");
		std::cout << "[ WARNING ]" << std::endl;
		karen.complain("WARNING");
		std::cout << "[ ERROR ]" << std::endl;
		karen.complain("ERROR");
	}
	

	
}