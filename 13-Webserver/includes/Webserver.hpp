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
