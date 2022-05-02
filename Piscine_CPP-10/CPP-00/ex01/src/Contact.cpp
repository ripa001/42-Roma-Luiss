# include "../include/Contact.hpp"

Contact::Contact(void)
{
	info[0] = std::string("First name");
	info[1] = std::string("Last name");
	info[2] = std::string("Username");
	info[3] = std::string("Phone number");
	info[4] = std::string("Date of birth (dd/mm/yyyy)");
	return ;
}

Contact::~Contact(void)
{
	return ;
}

void Contact::addInfo(void)
{
	int i;
	std::string str;

	i = -1;
	std::cout << "Fill the form!\n";
	while (++i < 5)
	{
		str.clear();
		while (str.size() == 0)
		{
			std::cout << "Insert the " << info[i] << ": " << std::endl;
			std::cin >> str;
			if (str.size() == 0)
				std::cout << "Fill the " << info[i] << " !" << std::endl;
		}
		info[i] = str;
	}
}

std::string Contact::getInfo(int n)
{
	return (info[n]);
}