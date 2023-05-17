#include "../includes/Server.hpp"

bool	Server::startServer() {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0)
		error("Error: Socket could not be created");
	    // Set the SO_REUSEADDR option
    int reuse = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
		error("Error: Socket could not be setsockopt");
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

int Server::getSocket() {
	return _sockfd;
}

std::vector<t_connection>::iterator	Server::findSocket(int socket) {
	std::vector<t_connection>::iterator it = _connections.begin();
	while (it != _connections.end()) {
		if ((*it).socket == socket)
			return it;
		it++;
	}
	return it;
}

int	Server::handleClient(int socket) {
	std::vector<t_connection>::iterator it = findSocket(socket);
	if (it == _connections.end())
		return (0);

	struct linger 	l;
	l.l_onoff = 1;
	l.l_linger = 0;
	(void)l;

	unsigned char buffer;
	if (it->request.method == "") {
		recv(socket, &buffer, sizeof(unsigned char), 0);
		it->buffer.push_back(buffer);
		if (it->buffer.find("\r\n\r\n") == (size_t)-1) return 0;
		std::cout << "Buffer: " << it->buffer;
		parseRequest(it->buffer, it->request);
		// if (!this->readRequest(*it, it->buffer))
		// {
		// 	defaultAnswerError(400, *it);
		// 	_connections.erase(it);
		// 	return (1);
		// }
	}
	return (0);

}

int	Server::newConnection(int socket) {
	socklen_t				addrlen;
	struct sockaddr_storage	sockaddr;
	int						connection;

	addrlen = sizeof(sockaddr);
	connection = accept(socket, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (connection < 0)
		error("Error: Connection could not be accepted");
	_connections.push_back(t_connection(connection));
	return connection;
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
