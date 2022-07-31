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

# include "Bureaucrat.hpp"
# include <iomanip>
# include <stdexcept>
# include <string>
// #include <iostream>
#include <cstdlib>
// #include <string>

class Bureaucrat;

class Form {
	private:
		const std::string	name;
		const std::string   target;
		bool				isSigned;
		const int			gradeToSign;
		const int			gradeToExecute;
		virtual void		executeConcrete() const;

	public:
		Form( void );
		Form(const std::string& name, const std::string& target, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		const std::string&	getName() const;
		const std::string&	getTarget() const;
		bool				getIsSigned() const;
		void				beSigned(const Bureaucrat& bureaucrat);
		void				execute(const Bureaucrat& executor) const;
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

		class ExecuteUnsignedException: public std::exception {
			virtual const char*	what() const throw();
		};

		virtual ~Form( void );
	};
std::ostream& operator<<(std::ostream & os, Form const & i);

#endif