#include "../include/Zombie.hpp"

int main(void)
{
	PhoneBook phoneBook;
	std::string s;
	while(1)
	{
		std::cout << "Type a command:\n\t1 - ADD\n\t2 - SEARCH\n\t3 - EXIT\n";
		std::cin >> s;
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
		if (s == "1" || s == "ADD")
			phoneBook.addContact();
		else if (s == "2" || s == "SEARCH")
			phoneBook.searchContact();
		else if (s == "3" || s == "EXIT")
			return (0);
		else
			std::cout << "Please insert a valid command\n";
	}
	return (0);
}