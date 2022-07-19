/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:54 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/18 12:19:52 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MATERIASOURCE_CLASS_HPP
# define MATERIASOURCE_CLASS_HPP

# include "IMateriaSource.hpp"

# define KNOWN_SIZE	4

class MateriaSource: public IMateriaSource {
	private:
		AMateria**	known;
	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		~MateriaSource();

		MateriaSource&	operator=(const MateriaSource& other);

		virtual void		learnMateria(AMateria* m);
		virtual AMateria*	createMateria(const std::string& type);
};

#endif
