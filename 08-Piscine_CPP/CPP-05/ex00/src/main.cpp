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

#include "../include/Bureaucrat.hpp"

void	sectionTitle(const std::string& title) {
	std::cout	<< std::endl
				<< "*** " << title << " ***"
				<< std::endl << std::endl;
}

int	main() {
	sectionTitle("constructor");

	try {
		Bureaucrat	deamn("deamn", 1);
		std::cout << deamn;
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	try {
		Bureaucrat	pluto("pluto", -42);
		std::cout << pluto;
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}


	try {
		Bureaucrat	mone("mone", 4242);
		std::cout << mone;
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	sectionTitle("increment");

	try {
		Bureaucrat	deamn("deamn", 12);
		std::cout << deamn;
		deamn.incrementGrade(10);
		std::cout << deamn;
		deamn.incrementGrade();
		std::cout << deamn;
		deamn.incrementGrade(); // too high!
		std::cout << deamn;
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	sectionTitle("decrement");

	try {
		Bureaucrat	deamn("deamn", 139);
		std::cout << deamn;
		deamn.decrementGrade(10);
		std::cout << deamn;
		deamn.decrementGrade();
		std::cout << deamn;
		deamn.decrementGrade(); // too low!
		std::cout << deamn;
	}
	catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
