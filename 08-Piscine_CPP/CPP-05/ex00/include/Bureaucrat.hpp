/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:22:58 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:22:58 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_CLASS_HPP
# define BUREAUCRAT_CLASS_HPP

#include <iostream>

class Bureaucrat {
	private:
		const std::string	name;
		int					grade;

		Bureaucrat( void );
	public:
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		int					getGrade() const;
		const std::string&	getName() const;
		void				incrementGrade(int change = 1);
		void				decrementGrade(int change = 1);
		Bureaucrat&			operator=(Bureaucrat const &other);
		class GradeTooLowException: public std::exception {
			virtual const char*	what() const throw();
		};

		class GradeTooHighException: public std::exception {
			virtual const char*	what() const throw();
		};

		~Bureaucrat( void );
};
std::ostream& operator<<(std::ostream & os, Bureaucrat const & i);

#endif