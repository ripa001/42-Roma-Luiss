#include "../includes/Server.hpp"

bool	Server::startServer() {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0)
		error("Error: Socket could not be created");
	if (bind(_sockfd, (struct sockaddr *)&_sin, sizeof(_sin)) < 0)
		error("Error: Socket could not be binded");
	if (listen(_sockfd, 200) < 0)
		error("Error: Socket could not be listened");
	return true;
}

std::vector<t_config>	Server::getConfigs() {
	return _configs;
}

t_config*	Server::getConfig() {
	return &_configs[0];
}

t_config*	Server::getConfig(int i) {
	return &_configs[i];
}

Server::Server(t_config config) {
	_config = NULL;
	_configs.push_back(config);
	memset(&_sin, 0, sizeof(_sin));
	memset(&_client, 0, sizeof(_client));
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = inet_addr((*(_configs.begin())).host.c_str());
	_sin.sin_port = htons((*(_configs.begin())).port); 
	if (startServer() == false)
		error("Error: Server could not be started");
}

Server::~Server() {
}
