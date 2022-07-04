#include <iostream>

int	main(void)
{
	std::string my_string = "HI THIS IS BRAIN";
	std::string *my_string_ptr = &my_string;
	std::string &my_string_ref = my_string;

	std::cout << "==============  Address  =============" << std::endl;
	std::cout << "by using str      : " << &my_string << std::endl;
	std::cout << "by using stringPTR: " << my_string_ptr << std::endl;
	std::cout << "by using stringREF: " << &my_string_ref << std::endl << std::endl;

	std::cout << "==============  String  ==============" << std::endl;
	std::cout << "by using str      : " << my_string << std::endl;
	std::cout << "by using stringPTR: " << *my_string_ptr << std::endl;
	std::cout << "by using stringREF: " << my_string_ref << std::endl;
	return (0);
}