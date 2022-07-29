/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:05 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:06 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_CLASS_HPP
# define ANIMAL_CLASS_HPP

#include <iostream>

class Animal {
	protected:
		std::string type;
	public:
		Animal( void );
		Animal(const Animal& animal);
		std::string		getType( void ) const;
		Animal&			operator=(Animal const &other);
		virtual void	makeSound( void ) const;
		virtual ~Animal( void );
};

#endif