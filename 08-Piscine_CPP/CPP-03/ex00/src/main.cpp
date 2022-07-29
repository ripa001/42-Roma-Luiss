/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:38 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:40 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/ClapTrap.hpp"

int main( void ) {
	std::cout << "------- ClapTrap | Max 10HP - 10 energy Points  -------" << std::endl << std::endl;
	ClapTrap a("Foo");
	ClapTrap b;

	std::cout << std::endl;
	b.beRepaired(3);
	b.takeDamage(2);
	b.beRepaired(3);
	for (int i = 0; i < 11; i++)
		b.attack("Elisabeth");
	b.addEnergyPoint(10);
	for (int i = 0; i < 3; i++)
		b.attack("Elisabeth");
	b.beRepaired(3);
	a.attack("Luca");
	a.takeDamage(100);
	a.takeDamage(10);
	a.beRepaired(5);
	a.attack("Pippo");
	std::cout << std::endl;
}