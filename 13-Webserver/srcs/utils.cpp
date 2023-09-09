/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:34 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::string getDateTime() {
	time_t now = time(0);
	struct tm *tstruct;
	std::string buf;

	now = time(NULL);
	tstruct = gmtime(&now);
	buf = asctime(tstruct);
	buf = buf.substr(0, buf.size() - 1);
	buf += " GMT";

	return buf;
}

void	error(std::string const err)
{
	std::cerr << err << std::endl;
	exit(1);
}

void error(std::string const err, int socket)
{
	std::cerr << err << std::endl;
	close(socket);
	exit(1);
}

std::string	myTrim(std::string str) {
	// std::cout << "trimming " << str << std::endl;
	str = str.substr(str.find_first_not_of(" \n\r\t"));
	// std::cout << "first trim: " << str << std::endl;
	str = str.substr(0, str.find_last_not_of(" \n\r\t") + 1);
	// std::cout << "final trim: " << str << std::endl;
	return str;
}

std::map<std::string, std::string>::iterator	findKey(std::map<std::string, std::string> &map, std::string key)
{
	for (std::map<std::string, std::string>::iterator iter = map.begin(); iter != map.end(); iter++)
	{
		if ((*iter).first == key)
			return iter;
	}
	return map.end();
}
