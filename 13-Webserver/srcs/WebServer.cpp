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
	std::vector<t_config>		v_prime;
	
	if (!confFile.is_open())
		throw std::runtime_error("Error: cannot open config file");

	// Save file in one string
	buffer << confFile.rdbuf();
	text = buffer.str();

	// Divide file into server blocks
	v_prime = parse(text);
	_configs.insert(_configs.end(),v_prime.begin(),v_prime.end());
	for (std::vector<t_config>::iterator it = _configs.begin(); it != _configs.end(); it++) {
		std::cout << "Server Name:  ";

		for (std::vector<std::string>::iterator it2 = it->server_name.begin(); it2 != it->server_name.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
		std::cout << "Port: " << it->port << std::endl;
		std::cout << "Host: " << it->host << std::endl;
		std::cout << "Root: " << it->root << std::endl;
		std::cout << "Autoindex: " << it->autoindex << std::endl;
		std::cout << "Client max body size: " << it->client_max_body_size << std::endl;
		std::cout << "Allowed methods: ";
		for (std::vector<std::string>::iterator it2 = it->allowed_methods.begin(); it2 != it->allowed_methods.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
		std::cout << "Index: ";
		for (std::vector<std::string>::iterator it2 = it->index.begin(); it2 != it->index.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
		std::cout << "Error pages: ";
		for (std::vector<std::string>::iterator it2 = it->error_pages.begin(); it2 != it->error_pages.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
		std::cout << "Files: ";
		for (std::vector<std::string>::iterator it2 = it->files.begin(); it2 != it->files.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
		std::cout << "CGI script: " << it->cgi_script << std::endl;
		std::cout << "Locations: " << std::endl;
		for ( std::vector<t_location>::iterator it2 = it->locations.begin(); it2 != it->locations.end(); it2++) {
			std::cout << "  Regex: " << it2->regex << std::endl;
			std::cout << "  Exact: " << it2->exact_path << std::endl;
			std::cout << "  Content: " << it2->content << std::endl;
			std::cout << "  Path: " << it2->path << std::endl;
			}
		std::cout << " -------------------------------------- " << std::endl;
		}
	for (std::vector<t_config>::iterator it = _configs.begin(); it != _configs.end(); it++) {
		_servers.push_back(Server(*it));
	}
	// divideServers(text, serverBlocks);
}