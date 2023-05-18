/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:15 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:15 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"
#include "Server.hpp"

class WebServer
{
	private:
		/* data */
		std::vector<Server> _servers;
		std::vector<t_config> _configs;
		struct pollfd		*_pfds;



	public:
		WebServer(std::string const &configPath);
		WebServer(/* args */);
		~WebServer();
		void	createConfigs(std::string const &configPath);
		void	start();
		void	startLooping(int fd_count, int fd_size);
};
