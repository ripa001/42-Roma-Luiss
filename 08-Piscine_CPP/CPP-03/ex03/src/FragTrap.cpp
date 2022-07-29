/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:21:42 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:46 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

FragTrap::FragTrap( void ) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	this->_name = "Default";
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) {
	this->_isInKeeperMode = false;
	this->_hitPoints = this->_maxHitPoints;
	this->_energyPoints = this->_maxEnergyPoints;
	this->_attackDamage = this->_maxAttackDamage;
	this->_name = name;
	std::cout << "FragTrap Name constructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap& fragTrap) : ClapTrap(fragTrap) {
	*this = fragTrap;
	std::cout << "FragTrap Copy constructor called" << std::endl;
}

void FragTrap::attack(const std::string& target) {
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to for FragTrap attack!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	this->_attackDamage++;
	std::cout << "FragTrap " << getName() << " attacks " << target
	<< ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

FragTrap& FragTrap::operator=(FragTrap& equals) {
	this->_name = equals._name;
	this->_hitPoints = equals._hitPoints;
	this->_energyPoints = equals._energyPoints;
	this->_attackDamage = equals._attackDamage;
	return (*this);
}

void	FragTrap::highFivesGuys( void ) {
	std::cout	<< "FragTrap " << _name << " want you to high five!"
				<< std::endl;
}

FragTrap::~FragTrap( void ) {
	std::cout << "Destructor FragTrap called" << std::endl;
	return ;
}
