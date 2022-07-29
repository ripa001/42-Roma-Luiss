/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:59 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:00 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_CLASS_HPP
# define FRAGTRAP_CLASS_HPP

#include <iostream>
#include "ScavTrap.hpp"

class FragTrap : public ClapTrap
{
	private:
		bool				_isInKeeperMode;
		static const int	_maxHitPoints = 100;
		static const int	_maxEnergyPoints = 100;
		static const int	_maxAttackDamage = 30;
	public:
		FragTrap(std::string name);
		FragTrap( void );
		FragTrap(FragTrap& FragTrap);
		FragTrap& operator=(FragTrap& equals);
		void attack(const std::string& target);
		void highFivesGuys( void );
		~FragTrap( void );
};

#endif
