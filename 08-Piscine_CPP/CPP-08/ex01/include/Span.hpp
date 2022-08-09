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

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
// #include <random>
#include <vector>
#include <algorithm>
#include <exception>

class Span
{
	private:
		std::vector<int>	_numbers;
		unsigned int		_n;
	public:
		Span( void );
		Span(unsigned int n);
		Span(const Span &copy);
		~Span();

		Span &operator=(const Span &equals);
		
		void			addNumber(int n);
		void			addNumber(std::vector<int>::const_iterator it1, std::vector<int>::const_iterator it2);

		unsigned long	shortestSpan();
		unsigned long	longestSpan() const;

		class InvalidSizeException: public std::exception {
			virtual const char*	what() const throw();
		};

		class NoElementsException: public std::exception {
			virtual const char*	what() const throw();
		};

		class NoElementsLeftException: public std::exception {
			virtual const char*	what() const throw();
		};
};

#endif