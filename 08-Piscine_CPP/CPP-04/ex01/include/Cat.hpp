/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:58 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:59 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain*	brain;
	public:
		Cat( void );
		Cat(const Cat& cat);
		Cat&	operator=(Cat const &other);
		Brain*	getBrain( void ) const;
		void 	makeSound( void ) const;
		~Cat( void );
};

#endif