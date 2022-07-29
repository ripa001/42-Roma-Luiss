/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:21:01 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:02 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_CLASS_HPP
# define SCAVTRAP_CLASS_HPP

#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	private:
		bool				_isInKeeperMode;
		static const int	_maxHitPoints = 100;
		static const int	_maxEnergyPoints = 50;
		static const int	_maxAttackDamage = 20;
	public:
		ScavTrap(std::string name);
		ScavTrap( void );
		ScavTrap(ScavTrap& scavTrap);
		ScavTrap& operator=(ScavTrap& equals);
		bool getKeeperMode();
		void attack(const std::string& target);
		void guardGate();
		~ScavTrap( void );
};

#endif