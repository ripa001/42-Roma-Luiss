/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:21:16 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:17 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/ScavTrap.hpp"

ScavTrap::ScavTrap( void ) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	this->_name = "Default";
	std::cout << "ScavTrap Default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	this->_name = name;
	std::cout << "ScavTrap Name constructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap& scavTrap) : ClapTrap(scavTrap) {
	*this = scavTrap;
	std::cout << "ScavTrap Copy constructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to for ScavTrap attack!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	this->_attackDamage++;
	std::cout << "ScavTrap " << getName() << " attacks " << target
	<< ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

ScavTrap& ScavTrap::operator=(ScavTrap& equals) {
	this->_name = equals._name;
	this->_hitPoints = equals._hitPoints;
	this->_energyPoints = equals._energyPoints;
	this->_attackDamage = equals._attackDamage;
	return (*this);
}

bool	ScavTrap::getKeeperMode() {
	return (this->_isInKeeperMode);
}

void ScavTrap::guardGate() {
	if (getKeeperMode())
		std::cout << "You already are in keeper mode" << std::endl;
	else
	{
		std::cout << "ScavTrap is now in Gate keeper mode." << std::endl;
		this->_isInKeeperMode = 1;
	}
}

ScavTrap::~ScavTrap( void ) {
	std::cout << "Destructor ScavTrap called" << std::endl;
	return ;
}
