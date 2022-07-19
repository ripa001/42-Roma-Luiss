/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:52 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/19 19:44:45 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_CLASS_HPP
# define ICE_CLASS_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
	public:
		Ice*	clone() const;
		void	use(ICharacter& target);

		Ice();
		Ice(Ice &copy);
		~Ice();

		Ice&	operator=(Ice const &other);
};

#endif