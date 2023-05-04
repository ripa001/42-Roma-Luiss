#include "../includes/Webserver.hpp"

WebServer::WebServer(std::string const &configPath) {
	_configs.reserve(30);
	_servers.reserve(30);
	this->createConfigs(configPath);
}

WebServer::~WebServer() {
}

void	WebServer::createConfigs(std::string const &configPath) {
	std::ifstream				confFile(configPath);
	std::string					text;
	std::stringstream			buffer;
	
	if (!confFile.is_open())
		throw std::runtime_error("Error: cannot open config file");

	// Save file in one string
	buffer << confFile.rdbuf();
	text = buffer.str();

	// Divide file into server blocks
	parse(text);
	// divideServers(text, serverBlocks);
}