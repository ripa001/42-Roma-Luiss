/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:33 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_CLASS_HPP
# define CLAPTRAP_CLASS_HPP

#include <iostream>

class ClapTrap {

	private:
		std::string _name;
		static const int	_maxHitPoints = 10;
		static const int	_maxEnergyPoints = 10;
		static const int	_maxAttackDamage = 0;
		int			_hitPoints;
		int			_energyPoints;
		int			_attackDamage;
	public:
		ClapTrap(std::string name);
		ClapTrap( void );
		ClapTrap(const ClapTrap& clapTrap);
		ClapTrap&	operator=(ClapTrap const &other);
		int			getHitPoint( void );
		int			getEnergyPoint( void );
		int			getAttackDamage( void );
		std::string	getName( void );
		void		addEnergyPoint(int value);
		void		attack(const std::string& target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);
		~ClapTrap( void );
};

#endif