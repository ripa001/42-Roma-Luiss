/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:43:57 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:43:57 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Form.hpp"
#include "../include/Bureaucrat.hpp"

void	sectionTitle(const std::string& title) {
	std::cout	<< std::endl
				<< "*** " << title << " ***"
				<< std::endl << std::endl;
}

void	printError(std::exception& e) {
	std::cout << "Error: " << e.what() << std::endl;
}

int	main() {
	Bureaucrat	bur("bur", 42);
	std::cout << bur;

	sectionTitle("constructor");
	try {
		Form	myForm("myForm", 1000, 1);
	}
	catch (std::exception& e) {
		printError(e);
	}
	try {
		Form	myForm("myForm", 42, 0);
	}
	catch (std::exception& e) {
		printError(e);
	}

	try {
		Form	myForm2("myForm2", 42, 42);
		Form	myForm3("myForm3", 1, 1);

		std::cout << std::endl << myForm2 << myForm3;

		sectionTitle("sign twice");
		bur.signForm(myForm2);
		std::cout << myForm2;
		bur.signForm(myForm2);

		sectionTitle("grade too low");
		bur.signForm(myForm3);
	}
	catch (std::exception& e) {
		printError(e);
	}
}
