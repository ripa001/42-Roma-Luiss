/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:39 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:39 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"

Brain::Brain( void ) : index(0) {
	std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& brain) {
	*this = brain;
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain&	Brain::operator=(Brain const &other) {
	this->index = other.index;
	for (int i = 0; i < 100; i++)
			this->ideas[i] = other.ideas[i];
	return *this;
}

void	Brain::setIdea(const std::string& idea) {
	ideas[index++] = idea;
	index = index % 100;
}

void	Brain::printIdeas(void) const {
	for (int i = 0; i < 100 && !ideas[i].empty(); i++)
		std::cout << i << ": " << ideas[i] << std::endl;
}

Brain::~Brain( void ) {
	std::cout << "Brain destructor called" << std::endl;
	return ;
}
