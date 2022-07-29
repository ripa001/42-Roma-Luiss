/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:19:56 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:19:57 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_CLASS_HPP
# define BRAIN_CLASS_HPP

#include <iostream>

class Brain {
	private:
		std::string	ideas[100];
		int index;
	public:
		Brain( void );
		Brain(const Brain& other);
		Brain&	operator=(const Brain& other);
		void	printIdeas(void) const;
		void	setIdea(const std::string& idea);
		~Brain( void );
};

#endif