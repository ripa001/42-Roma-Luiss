#include "../include/PhoneBook.hpp"

PhoneBook::PhoneBook( void ) {
	n = 0;
	oldest = 0;
	return ;
}

PhoneBook::~PhoneBook( void ) {
	return ;
}

void PhoneBook::addContact( void ) {
	Contact tmp;

	tmp.addInfo();
	if (n == 8)
	{
		if (oldest == 8)
			oldest = 0;
		contact[oldest++] = tmp;
	}
	else
		contact[n++] = tmp; 
	return ;
}

void PhoneBook::searchContact( void ) {
	int i = -1;
	int j = -1;	
	int	index;
	Contact tmp;


	if (n == 0)
		std::cout << "There aren't contacts in your Phonebook. Add a new Contact!";
	else
	{
		std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
		while (++i < n)
		{
			j = -1;
			std::cout << "|" << std::setw(10) << i + 1 << "|";
			while (++j < 3)
			{
				if (contact[i].getInfo(j).size() < 10)
					std::cout << std::setw(10) << contact[i].getInfo(j) << "|";
				else
					std::cout << contact[i].getInfo(j).substr(0, 9) << ".|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		while (1)
		{
			std::cout << "Enter a valid contact index (1 to " << n << ") or 0 to go back" << std::endl;
			std::cin >> index;
			if (index > n || index < 0 || std::cin.fail())
			{
				std::cout << "Invalid index! Please enter a valid one!" << std::endl;
				std::cin.clear();
				break ;
			}
			else
			{
				if (index != 0)
				{
					i = -1;
					std::cout << "Information for index: " << index << std::endl;
					while (++i < 5)
						std::cout << "\t" << tmp.getInfo(i) << ": " << contact[index - 1].getInfo(i) << std::endl;
				}
				else
				{
					std::cin.clear();
					break ;
				}
			}
		}
	}
}