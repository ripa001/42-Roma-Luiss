#ifndef PHONEBOOK_CLASS_HPP
# define PHONEBOOK_CLASS_HPP

# include "Contact.hpp"
# include <algorithm>
# include <cstring>
# include <iomanip>


class PhoneBook {

	public:
		PhoneBook( void );
		~PhoneBook( void );

		void addContact( void );
		void searchContact( void );

	private:
		Contact contact[8];
		int n;
		int oldest;
};

#endif