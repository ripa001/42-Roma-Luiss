/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:27:55 by lrocca            #+#    #+#             */
/*   Updated: 2021/11/30 12:01:35 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MateriaSource.hpp"

MateriaSource::MateriaSource(): known(new AMateria*[4]) {
	for (size_t i = 0; i < 4; i++)
		known[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& other)
	: known(new AMateria*[4]) {
	for (size_t i = 0; i < 4; i++)
		if (other.known[i])
			known[i] = other.known[i];
		else
			known[i] = NULL;
}

MateriaSource::~MateriaSource() {
	for (size_t i = 0; i < 4; i++)
		if (known[i])
			delete known[i];
	delete [] known;
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& other) {
	if (this != &other) {
		for (size_t i = 0; i < 4; i++)
			if (known[i])
				delete known[i];
		for (size_t i = 0; i < 4; i++)
			if (other.known[i])
				known[i] = other.known[i];
			else
				known[i] = NULL;
	}
	return *this;
}

void	MateriaSource::learnMateria(AMateria* m) {
	size_t	i = 0;

	for (; i < 4 && known[i]; i++)
		;

	if (i == 4)
		return ;

	known[i] = m;
}

AMateria*	MateriaSource::createMateria(const std::string& type) {
	for (size_t i = 0; i < 4; i++)
		if (known[i]->getType() == type)
			return known[i]->clone();

	return NULL;
}
