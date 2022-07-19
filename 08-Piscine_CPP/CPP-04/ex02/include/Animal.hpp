/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:03 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 17:54:43 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_CLASS_HPP
# define ANIMAL_CLASS_HPP

#include <iostream>

class Animal {
	protected:
		std::string type;
	public:
		Animal&			operator=(Animal const &other);
		virtual std::string		getType( void ) const;
		virtual void	makeSound( void ) const;
		virtual ~Animal( void );
};

#endif