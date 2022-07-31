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

#include "Form.hpp"
#include <iostream>

class Form;

class Bureaucrat {
	private:
		const std::string	name;
		int					grade;

	public:
		Bureaucrat( void );
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		int					getGrade() const;
		const std::string&	getName() const;
		void				incrementGrade(int change = 1);
		void				decrementGrade(int change = 1);
		void				signForm(Form& form) const;
		void				executeForm(const Form& form) const;
		Bureaucrat&			operator=(Bureaucrat &equals);
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