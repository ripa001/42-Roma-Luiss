/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:20:22 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:20:23 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include "../include/WrongCat.hpp"

int main()
{
	std::cout << "------- Animals constructors -------" << std::endl;

	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "------- Animals Testing -------" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	std::cout << "------- Animals Destructors -------" << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "------- WrongAnimals constructions -------" << std::endl;
	const WrongAnimal*	wrongA = new WrongAnimal();
	const WrongAnimal*	wrongC = new WrongCat();

	std::cout << "------- WrongAnimals testing -------" << std::endl;
	std::cout << wrongA->getType() << std::endl;
	std::cout << wrongC->getType() << std::endl;
	wrongA->makeSound();
	wrongC->makeSound();

	std::cout << "------- WrongAnimals Destructors -------" << std::endl;
	delete wrongA;
	delete wrongC;
	return 0;
}