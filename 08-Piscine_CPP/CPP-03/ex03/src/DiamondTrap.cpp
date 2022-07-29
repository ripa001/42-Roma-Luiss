/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:21:36 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:38 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/DiamondTrap.hpp"

DiamondTrap::DiamondTrap( void ) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	this->_name = "Default";
	std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) 
	: ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), _name(name) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	std::cout << "DiamondTrap Name constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap& fragTrap) : ClapTrap(fragTrap.getName() + "_clap_name"), FragTrap(fragTrap.getName()), ScavTrap(fragTrap.getName()) {
	*this = fragTrap;
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to for DiamondTrap attack!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	this->_attackDamage++;
	std::cout << "DiamondTrap " << getName() << " attacks " << target
	<< ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(DiamondTrap& equals) {
	this->_name = equals._name;
	this->_hitPoints = equals._hitPoints;
	this->_energyPoints = equals._energyPoints;
	this->_attackDamage = equals._attackDamage;
	return (*this);
}

void	DiamondTrap::highFivesGuys( void ) {
	std::cout	<< "DiamondTrap " << _name << " want you to high five!"
				<< std::endl;
}

DiamondTrap::~DiamondTrap( void ) {
	std::cout << "Destructor DiamondTrap called" << std::endl;
	return ;
}

void	DiamondTrap::whoAmI( void ) {
	std::cout	<< "My name is DiamondTrap " << _name
				<< ". My ClapTrap name is " << ClapTrap::_name << std::endl;
}
