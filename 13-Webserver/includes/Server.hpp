#pragma once

#include "utils.hpp"

class Server
{
private:
		typedef std::vector<std::pair<std::string, std::string> >::iterator	iterator;
		Server();

		std::vector<t_config>								_configs;
		t_config*											_config;
		std::vector<std::pair<std::string, std::string> >	_storeReq; 
		struct sockaddr_in									_sin;
		struct sockaddr_in									_client;
		socklen_t											_size;
		int													_sockfd;
		std::vector<t_connection>								_connections;
		std::map<std::string, std::string>					_cookies;


public:
	t_config*												getConfig();
	t_config*												getConfig(int i);
	std::vector<t_config>									getConfigs();
	int														getSocket();
	bool													startServer();
	int														newConnection(int socket);
	

	Server(t_config config);
	~Server();
};