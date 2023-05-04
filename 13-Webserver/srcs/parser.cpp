#include "../includes/utils.hpp"

size_t findServerAndLocation(const std::string& str, size_t skipChars = 0, size_t returEnd = 0, int location = 0) {
    size_t pos = skipChars;
	std::string	to_find = "server";

    while (true) {
		if (location == 1)
			to_find = "location";
        pos = str.find(to_find, pos);
        if (pos == std::string::npos)
            return -1;
        size_t start = pos;
        pos += to_find.length(); 
        while (std::isspace(str[pos]))
            ++pos;
		if (location == 1){
			if (str[pos] == '{')
				error("Error: no location path found");
			while (str[pos] != '{')
				++pos;
		}			
        if (str[pos] == '{') {
			if (returEnd == 1)
				return ++pos;
            return start;
        }
    }
}

void	divideServers(std::string text, std::vector<std::string> *serverBlocks) {
	size_t found;
	std::string serverBlockTmp;

	text = text.substr(text.find_first_not_of(" \n\r\t"));
	if (findServerAndLocation(text) == std::string::npos)
		error("Error: no server block found or server block not at the beginning of the file");
	// loop until there are no more server blocks check and clean
	while ((found = findServerAndLocation(text)) != std::string::npos) {
		serverBlockTmp = text.substr(found, findServerAndLocation(text, found + 1));
		// check if there are comments
		std::cout << "serverBlockTmp: " << findServerAndLocation(text, found + 1) << found << std::endl;
		while (serverBlockTmp.find("#") != std::string::npos)
		{
			if (serverBlockTmp.find("#") == 0)
				serverBlockTmp = serverBlockTmp.substr(serverBlockTmp.find("\n"));
			else
				serverBlockTmp = serverBlockTmp.substr(0, serverBlockTmp.find("#")) + serverBlockTmp.substr(serverBlockTmp.find("\n"));
		}
		if (std::count(serverBlockTmp.begin(), serverBlockTmp.end(), '{') != std::count(serverBlockTmp.begin(), serverBlockTmp.end(), '}'))
			error("Error: missing bracket in server block");
		serverBlockTmp = serverBlockTmp.erase(serverBlockTmp.find_last_not_of(" \n\r\t")+1);
		if (serverBlockTmp[serverBlockTmp.length() - 1] != '}')
			error("Error: instructions outside of server block");
		(*serverBlocks).push_back(serverBlockTmp);
		if (text.find("server {", found + 1) == std::string::npos)
			break;
		text = text.substr(text.find("server {", found + 1));
	}
}

bool	checkPort(std::string value) {
	if (value == "")
		error("Error: no port found");
	// check if port is a number
	for (size_t i = 0; i < value.length(); i++)
		if (!std::isdigit(value[i]))
			error("Error: port is not a number");
	// check if port is between 0 and 65535
	if (std::stoi(value) < 0 || std::stoi(value) > 65535)
		error("Error: port is not between 0 and 65535");
	return true;
}

bool	checkHost(std::string host) {
		// check if host is a valid ip

	for (size_t i = 0; i < host.length(); i++)
		if (host[i] == '.')
			if (host[i + 1] == '.' || host[i - 1] == '.')
				error("Error: host is not a valid ip it shouldn't have 2 dots in a row");
	for (size_t i = 0; i < host.length(); i++)
		if (!std::isdigit(host[i]) && host[i] != '.')
			error("Error: host is not a valid ip it should be a number or a dot");
	if (std::count(host.begin(), host.end(), '.') != 3)
		error("Error: host is not a valid ip it should have 3 dots");

	size_t j = 0;
	for (size_t i = 0; i < host.length(); i++)
		if (host[i] == '.') {
			if (std::stoi(host.substr(j, i - j)) < 0 || std::stoi(host.substr(j, i - j)) > 255)
				error("Error: host is not a valid ip in range 0-255");
			j = i + 1;
		}
	if (std::stoi(host.substr(j, host.length() - j)) < 0 || std::stoi(host.substr(j, host.length() - j)) > 255)
		error("Error: host is not a valid ip in range 0-255");
	
	return true;
}

bool	checkPortHost(std::string value) {
	std::string	port;
	std::string	host = "";

	if (value.find(":") == std::string::npos) {
		port = value;
		if (checkPort(port))
			return true;
	}
	else {
		port = value.substr(value.find(":") + 1);
		host = value.substr(0, value.find(":"));
	}
	std::cout << "port: " << port << std::endl;
	std::cout << "host: " << host << std::endl;

	// check if host is a valid ip
	if (checkHost(host) && checkPort(port))
		return true;
	return false;
}

void	parseListen(std::string value, t_config &config) {
	std::string	port;
	std::string	host;

	if (value.find(":") == std::string::npos && !checkPortHost(value))
		error("Error: invalid port");
	else if (value.find(":") == std::string::npos)
		config.port = std::stoi(value);
	else if (!checkPortHost(value))
		error("Error: invalid port or host");
	else
	{
		config.port = std::stoi(value.substr(value.find(":") + 1));
		config.host = value.substr(0, value.find(":"));
	}
}

bool	checkServerName(std::string value) {
	if (value.find("www.") == 0)
		value = value.substr(4);

	if (value.find(".") == std::string::npos)
		return false;
	
	for (size_t i = 0; i < value.length(); i++)
		if (!std::isalnum(value[i]) && value[i] != '.' && value[i] != '-')
			return false;

	if (value[0] == '.' || value[value.length() - 1] == '.')
		return false;

	for (size_t i = 0; i < value.length(); i++)
		if (value[i] == '.')
			if (value[i + 1] == '.' || value[i - 1] == '.')
				return false;
	return true;
}

void	parseServerName(std::string value, t_config &config) {
	std::string	serverName;
	int count = 0;

	while (value.find_first_of(" \n\r\t") != std::string::npos)
	{
		serverName = value.substr(0, value.find_first_of(" \n\r\t"));
		count++;
		if (checkServerName(serverName) == false)
			error("Error: invalid server name in server block: " + std::to_string(count));
		config.server_name.push_back(serverName);
		value = value.substr(value.find_first_of(" \n\r\t") + 1);
	}
}

void	parseRoot(std::string value, t_config &config) {
	if (value.find_first_of(" \n\r\t") != std::string::npos)
		error("Error: invalid root");
	config.root = value;
}

void	fillKeyValueArgs(std::string text, t_config &config) {
	std::string	key;
	std::string	value;

	key = text.substr(0, text.find_first_of(" \n\r\t"));
	value = text.substr(text.find_first_of(" \n\r\t") + 1);
	value = myTrim(value);
	// parse arguments
	std::cout << "key: " << key << std::endl;
	std::cout << "value: " << value << std::endl;

	if (key == "listen")
		parseListen(value, config);
	else if (key == "server_name")
		parseServerName(value, config);
	else if (key == "root")
		parseRoot(value, config);
	else if (key == "autoindex")
		;
		// parseAutoindex(value, config);
	else if (key == "index")
		;
		// parseIndex(value, config);
	else if (key == "error_page")
		;
		// parseErrorPage(value, config);
	else if (key == "client_max_body_size")
		;
		// parseClientMaxBodySize(value, config);
	else if (key == "allowed_methods")
		;
		// parseAllowedMethods(value, config);
	else
		error("Error: invalid instruction: " + key);


	(void)config;

}

void	parseServerBlocks(std::vector<std::string> serverBlocks) {
	std::vector<std::string>::iterator	it;
	t_config							config;
	std::string							content;
	std::string							tmp;

	std::cout << "serverBlocks.size(): " << serverBlocks.size() << std::endl;
	for (it = serverBlocks.begin(); it != serverBlocks.end(); it++) {
		content = (*it).substr(findServerAndLocation(*it,0,1), (*it).find_last_of("}"));
		if (content.find(";") == std::string::npos)
			error("Error: no instruction in server block");
		while (content.find(";") != std::string::npos) {
			tmp = content.substr(0, content.find(";"));
			if (tmp.find_first_of(" \n\r\t") == std::string::npos)
				error("Error: invalid instruction, there should ne spaces between the instruction and the parameters");
			if (findServerAndLocation(tmp, 0, 0, 1) != std::string::npos) {
				tmp = myTrim(content.substr(0, content.find("}") + 1));
				// parseLocationBlock(tmp, config);
				std::cout << "location: " << tmp << std::endl;
				content = content.substr(content.find("}") + 1);
				continue;
			}
			fillKeyValueArgs(myTrim(tmp), config);
			
			(void)config;
			// if (key.find("location")
			content = content.substr(content.find(";") + 1);
			
		}
		
	}
	
	// for (size_t i = 0; i < serverBlocks.size(); i++)
	// {
	// 	std::cout << serverBlocks[i]  << std::endl << "---" << std::endl;
	// }
}

void	parse(std::string text) {
	std::vector<std::string>	serverBlocks;

	divideServers(text, &serverBlocks);
	parseServerBlocks(serverBlocks);
}

