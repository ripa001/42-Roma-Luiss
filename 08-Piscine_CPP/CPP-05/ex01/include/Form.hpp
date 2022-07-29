/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:54:21 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/29 12:54:21 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_CLASS_HPP
# define FORM_CLASS_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
	private:
		const std::string	name;
		bool				isSigned;
		const int			gradeToSign;
		const int			gradeToExecute;

		Form( void );
	public:
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		const std::string&	getName() const;
		bool				getIsSigned() const;
		void				beSigned(const Bureaucrat& bureaucrat);
		Form&				operator=(Form const &other);
		class GradeTooLowException: public std::exception {
			virtual const char*	what() const throw();
		};

		class GradeTooHighException: public std::exception {
			virtual const char*	what() const throw();
		};
		
		class AlreadySignedException: public std::exception {
			virtual const char*	what() const throw();
		};

		~Form( void );
};
std::ostream& operator<<(std::ostream & os, Form const & i);

#endif