/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:49 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:52 by dripanuc         ###   ########.fr       */
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
		cat->getBrain()->printIdeas();
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
