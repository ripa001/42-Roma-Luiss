/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:13 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:14 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  WRONGCAT_CLASS_HPP
# define WRONGCAT_CLASS_HPP

#include <iostream>
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		WrongCat( void );
		WrongCat(const WrongCat& cat);
		WrongCat&	operator=(WrongCat const &other);
		void 	makeSound( void ) const;
		~WrongCat( void );
};

#endif