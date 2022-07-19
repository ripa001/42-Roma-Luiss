/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:52 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/19 19:57:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_CLASS_HPP
# define CURE_CLASS_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure*	clone() const;
		void	use(ICharacter& target);

		Cure();
		Cure(Cure &copy);
		~Cure();

		Cure&	operator=(Cure const &other);
};

#endif