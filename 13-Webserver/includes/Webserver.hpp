#pragma once

#include "utils.hpp"
#include "Server.hpp"

class WebServer
{
	private:
		/* data */
		std::vector<Server> _servers;
		std::vector<t_config> _configs;


	public:
		WebServer(std::string const &configPath);
		WebServer(/* args */);
		~WebServer();
		void	createConfigs(std::string const &configPath);
};
