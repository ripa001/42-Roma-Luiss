#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

#include <iostream>

class Contact {

	public:
		Contact( void );
		~Contact( void );

		void addInfo( void );
		std::string getInfo(int n);

	private:
		std::string info[5];
};

#endif