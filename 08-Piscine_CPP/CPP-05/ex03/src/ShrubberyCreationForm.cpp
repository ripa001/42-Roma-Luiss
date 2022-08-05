/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:38:14 by dripanuc          #+#    #+#             */
/*   Updated: 2022/07/31 12:38:14 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): Form("ShrubberyCreationForm", "default", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : Form("ShrubberyCreationForm", target, 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : Form(other) {
	*this = other;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {}
	return *this;
}

void	ShrubberyCreationForm::executeConcrete() const {
	std::fstream	fs;

	fs.open(std::string(this->getTarget() + "_shrubbery").c_str(), std::fstream::out | std::fstream::trunc);

	if (!fs.good())
		std::cerr << "Error while opening Shrubbery target file" << std::endl;

	fs <<
	"              * *\n"
	"           *    *  *\n"
	"      *  *    *     *  *\n"
	"     *     *    *  *    *\n"
	" * *   *    *    *    *   *\n"
	" *     *  *    * * .#  *   *\n"
	" *   *     * #.  .# *   *\n"
	"  *     \"#.  #: #\" * *    *\n"
	" *   * * \"#. ##\"       *\n"
	"   *       \"###\n"
	"             \"##\n"
	"              ##.\n"
	"              .##:\n"
	"              :###\n"
	"              ;###\n"
	"            ,####.\n"
	"/\\/\\/\\/\\/\\/.######.\\/\\/\\/\\/\\\n";

	fs.close();
}
