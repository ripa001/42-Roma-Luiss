#include "../includes/utils.hpp"

void	error(std::string const err)
{
	std::cerr << err << std::endl;
	exit(1);
}

std::string	myTrim(std::string str) {
	str = str.substr(str.find_first_not_of(" \n\r\t"));
	str = str.substr(0, str.find_last_not_of(" \n\r\t") + 1);
	return str;
}