/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:53:17 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/09 11:53:17 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <list>

template<typename T>
class MutantStack: public std::stack<T>
{
	private:
	public:
		MutantStack<T>( void ) {}
		~MutantStack<T>( void ) {}

		MutantStack<T>( const MutantStack<T> &src )
		{
			*this = src;
		}

		MutantStack<T>	&operator=( const MutantStack<T> &rhs )
		{
			this->c = rhs.c;
			return(*this);
		}

		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator	begin( void )
		{
			return this->c.begin();
		}
		
		iterator	end( void ) {
			return this->c.end();
		}
};

#endif