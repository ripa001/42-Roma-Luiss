/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:09 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_CLASS_HPP
# define DOG_CLASS_HPP

#include <iostream>
#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog( void );
		Dog(const Dog& animal);
		Dog&	operator=(Dog const &other);
		void makeSound( void ) const;
		~Dog( void );
};

#endif