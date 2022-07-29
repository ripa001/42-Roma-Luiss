/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:21:47 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:21:50 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/DiamondTrap.hpp"

int	main() {
	std::cout << "------- FragTrap | Max 100HP - 100 energy Points  -------" << std::endl;
	ScavTrap a("Pippo");
	ScavTrap b;
	FragTrap c("Pluto");
	FragTrap d("Gigi");
	DiamondTrap	e("AIoT");
	DiamondTrap	f("Ripa");

	std::cout << "**** Testing ****  " << std::endl;

	a.attack(b.getName());
	b.takeDamage(a.getAttackDamage());

	b.attack(c.getName());
	c.takeDamage(b.getAttackDamage());

	d.attack(a.getName());
	a.takeDamage(d.getAttackDamage());

	a.beRepaired(2);
	b.beRepaired(3);
	c.beRepaired(4);

	a.guardGate();
	a.guardGate();

	d.highFivesGuys();

	f.attack(e.getName());
	e.takeDamage(f.getAttackDamage());

	f.whoAmI();
	std::cout << "**** Destructor ****" << std::endl;
}