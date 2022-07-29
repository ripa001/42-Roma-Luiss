/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:36 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:37 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

ClapTrap::ClapTrap( void ) : _name("Default"), _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage) {
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage) {
	std::cout << "Name constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& clapTrap) : _hitPoints(this->_maxHitPoints), _energyPoints(this->_maxEnergyPoints), _attackDamage(this->_maxAttackDamage) {
	*this = clapTrap;
	std::cout << "Copy constructor called" << std::endl;
}

void	ClapTrap::addEnergyPoint(int value) {
	if (value > this->_maxEnergyPoints)
		this->_energyPoints = _maxEnergyPoints;
	else
		this->_energyPoints = value;
	std::cout << "Energy points filled, now you have " << getEnergyPoint() << " energy points" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to attack!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	this->_attackDamage++;
	std::cout << "ClapTrap " << getName() << " attacks " << target
	<< ", causing " << getAttackDamage() << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (!getEnergyPoint() || !getHitPoint())
	{
		std::cout << "No more point to repair!" << std::endl;
		return ;
	}
	else
		this->_energyPoints--;
	if ((this->_hitPoints + amount) > this->_maxHitPoints)
		this->_hitPoints = this->_maxHitPoints;
	else
		this->_hitPoints += amount;
    std::cout << this->_name << " gained " << amount << " HP points! " << getHitPoint() << " remaining " << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (getHitPoint() <= 0)
	{
		std::cout << "You already died" << std::endl;
		return ;
	}
	if (((int)this->_hitPoints - (int)amount) < 0)
		this->_hitPoints = 0;
	else
		this->_hitPoints -= amount;
    std::cout << this->_name << " lost " << amount << " HP points! " << getHitPoint() << " remaining " << std::endl;
}

int	ClapTrap::getHitPoint( void ) {
	return (this->_hitPoints);
}

int	ClapTrap::getEnergyPoint( void ) {
	return (this->_energyPoints);
}

int	ClapTrap::getAttackDamage( void ) {
	return (this->_attackDamage);
}

std::string	ClapTrap::getName( void ) {
	return (this->_name);
}

ClapTrap&	ClapTrap::operator=(ClapTrap const &other) {
	this->_name = other._name;
	this->_hitPoints = other._hitPoints;
	this->_energyPoints = other._energyPoints;
	this->_attackDamage = other._attackDamage;
	return *this;
}

ClapTrap::~ClapTrap( void ) {
	std::cout << "Destructor called" << std::endl;
	return ;
}
