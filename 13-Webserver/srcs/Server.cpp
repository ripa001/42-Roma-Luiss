#include "../includes/Server.hpp"

Server::Server(t_config config) {
	_config = NULL;
	_configs.push_back(config);
	memset(&_sin, 0, sizeof(_sin));
	memset(&_client, 0, sizeof(_client));
	_sin.sin_family = AF_INET;
	_sin.sin_addr.s_addr = inet_addr((*(_configs.begin())).host.c_str());
	_sin.sin_port = htons((*(_configs.begin())).port);
}

Server::~Server() {
}
