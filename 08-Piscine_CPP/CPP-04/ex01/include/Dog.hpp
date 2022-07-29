/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:00 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:01 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain*	brain;
	public:
		Dog( void );
		Dog(const Dog& animal);
		Dog&	operator=(Dog const &other);
		Brain*	getBrain( void ) const;
		void makeSound( void ) const;
		~Dog( void );
};

#endif