/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:29:35 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 12:29:35 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Character.hpp"

Character::Character( void ) : ICharacter(), _name(""), _n_invetory(0), inventory(new AMateria*[4]) {
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
	std::cout << "Character constructor called" << std::endl;
}

Character::Character(Character& copy) {
	for (size_t i = 0; i < 4; i++)
		if (copy.inventory[i])
			inventory[i] = copy.inventory[i]->clone();
}

Character::Character(std::string const& name) : ICharacter(), _name(name), _n_invetory(0), inventory(new AMateria*[4]) {
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
	std::cout << "Character constructor called" << std::endl;
}


Character&	Character::operator=(Character const &other) {
	if (this != &other) {
		for (size_t i = 0; i < 4; i++)
			if (inventory[i])
				delete inventory[i];
		for (size_t i = 0; i < 4; i++)
			if (other.inventory[i])
				inventory[i] = other.inventory[i]->clone();
			else
				inventory[i] = NULL;
	}
	return *this;
}

std::string const & Character::getName() const {
	return (_name);
}

void	Character::equip(AMateria* m) {
	int flag;

	flag = 0;
	for (int i = 0; i < 4 && !flag; i++) {
		if (!this->inventory[i]) {
			flag = 1;
			this->inventory[i] = m;
			std::cout << "Equipped a " << m->getType() << ", inventory: " << ++_n_invetory << " / 4"
				<< std::endl;
		}
	}
	if (!flag)
		std::cout << "Couldn't equip a " << m->getType() << ", no more space"
			<< std::endl;
}

void	Character::unequip(int idx) {
	if (idx < 0 || idx > 3)
		std::cout << "Couldn't unequip index " << idx << ", this index is wrong"
			<< std::endl;
	if (!this->inventory[idx])
		std::cout << "Couldn't unequip index " << idx << " this index is already empty"
			<< std::endl;
	if (this->inventory[idx]) {
		std::cout << "Unequipped a " << this->inventory[idx]->getType()  << ", inventory: " << --_n_invetory << " / 4"
				<< std::endl;
		this->inventory[idx] = NULL;
	}
}

void	Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx > 3)
		std::cout << "Couldn't use index " << idx << ", this index is wrong"
			<< std::endl;
	if (!this->inventory[idx])
		std::cout << "Couldn't use index " << idx << " this index is empty"
			<< std::endl;
	if (this->inventory[idx]) {
		this->inventory[idx]->use(target);
	}
}

Character::~Character( void ) {
	for (int i = 0; i < 4; i++)
		if (inventory[i])
			delete inventory[i];
	delete [] inventory;
	std::cout << "Character destructor called" << std::endl;
	return ;
}
