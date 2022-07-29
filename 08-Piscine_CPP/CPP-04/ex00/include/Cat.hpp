/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:08 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_CLASS_HPP
# define CAT_CLASS_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat( void );
		Cat(const Cat& cat);
		Cat&	operator=(Cat const &other);
		void 	makeSound( void ) const;
		~Cat( void );
};

#endif