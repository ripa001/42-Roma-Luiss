#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "* LOAD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	while (--argc)
	{
		argv++;
		for (int i = 0; i < (int)strlen(*argv); i++)
			(*argv)[i] = std::toupper((*argv)[i]);
		std::cout << *argv << " ";
	}
	std::cout << std::endl;
}