/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:56 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 17:55:21 by dripanuc         ###   ########.fr       */
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
		virtual Brain*	getBrain( void ) const;
		// virtual	std::string		getType( void ) const;
		virtual void makeSound( void ) const;
		~Dog( void );
};

#endif