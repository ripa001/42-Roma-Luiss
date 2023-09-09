/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmeoli <gmeoli@student.42.fr>          +#+  +:+       +#+            */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:45:09 by gmeoli          #+#    #+#               */
/*   Updated: 2023/05/20 10:45:09 by gmeoli         ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */
#pragma once

#include "utils.hpp"

class Cgi {
	public:
		Cgi();
		Cgi(t_connection &connectionInfo, unsigned short port);
		~Cgi();
		std::string	executeCgi(t_config &config, const char *path);
		char **getEnv(void) const;
	private:
		std::vector<std::pair<std::string, std::string> > _env;
		std::string _body;
};
