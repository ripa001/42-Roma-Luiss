#ifndef ZOMBIE_CLASS_HPP
# define ZOMBIE_CLASS_HPP

#include <iostream>

class Zombie {

	public:
		Zombie(void);
		~Zombie(void);

		void announce( void );
		std::string getInfo(int n);

	private:
		std::string info[5];
};

#endif