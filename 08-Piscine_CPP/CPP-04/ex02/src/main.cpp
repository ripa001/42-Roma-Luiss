/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:07:17 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 18:06:09 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"
#include "../include/Cat.hpp"
#include "../include/Brain.hpp"
#define N_ANIMALS 4

int	main() {
	{
		std::cout << "------- ANIMALS -------" << std::endl;
		const Animal*	zoo[N_ANIMALS];
		// try
		// {
		// 	const Animal* prova = new Animal();
		// 	(void) prova;
		// }
		// catch(...)
		// {
		// 	std::cerr << "La classe Animal non può essere inizializzata da sola " << '\n';
		// }
		for (int i = 0; i < N_ANIMALS / 2; i++)
			zoo[i] = new Cat();
		for (int i = N_ANIMALS / 2; i < N_ANIMALS; i++)
			zoo[i] = new Dog();
		for (int i = 0; i < N_ANIMALS; i++)
			zoo[i]->makeSound();
		Cat* cat = new Cat();
		cat->getBrain()->setIdea("Ideas on animals brain 1");
		cat->getBrain()->setIdea("Ideas on animals brain 2");
		cat->getBrain()->setIdea("Ideas on animals brain 3");
		cat->getBrain()->setIdea("Ideas on animals brain 4");
		Cat* cat2 = new Cat(*cat);
		cat2->getBrain()->setIdea("Ideas on animals brain 7");
		cat->getBrain()->printIdeas();
		cat2->getBrain()->printIdeas();
		for (int i = 0; i < N_ANIMALS; i++)
			delete zoo[i];
	}
	{
		std::cout << "------- BRAIN -------" << std::endl;

		Brain*	normal = new Brain();

		normal->setIdea("My name is AB");
		normal->setIdea("I like watching movies");
		normal->setIdea("My favourite is Frankenstein Junior");

		normal->printIdeas();

		Brain*	abnormal = new Brain(*normal);

		delete normal;

		abnormal->printIdeas();

		delete abnormal;
	}
}
