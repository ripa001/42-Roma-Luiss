/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:28 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:28 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (str[pos] == ';')
				error("Error: no location path found");
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
	if (strtol(value.c_str(), NULL, 0) < 0 || strtol(value.c_str(), NULL, 0) > 65535)
		error("Error: port is not between 0 and 65535");
	return true;
}

bool	checkHost(std::string host) {
	size_t j = 0;

	for (size_t i = 0; i < host.length(); i++)
		if (host[i] == '.')
			if (host[i + 1] == '.' || host[i - 1] == '.')
				error("Error: host is not a valid ip it shouldn't have 2 dots in a row");
	for (size_t i = 0; i < host.length(); i++)
		if (!std::isdigit(host[i]) && host[i] != '.')
			error("Error: host is not a valid ip it should be a number or a dot");
	if (std::count(host.begin(), host.end(), '.') != 3)
		error("Error: host is not a valid ip it should have 3 dots");
	for (size_t i = 0; i < host.length(); i++)
		if (host[i] == '.') {
			if (strtol(host.substr(j, i - j).c_str(), NULL, 0) < 0 || strtol(host.substr(j, i - j).c_str(), NULL, 0) > 255)
				error("Error: host is not a valid ip in range 0-255");
			j = i + 1;
		}
	if (strtol(host.substr(j, host.length() - j).c_str(), NULL, 0) < 0 || strtol(host.substr(j, host.length() - j).c_str(), NULL, 0) > 255)
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
	} else {
		port = value.substr(value.find(":") + 1);
		host = value.substr(0, value.find(":"));
	}
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
		config.port = strtol(value.c_str(), NULL, 0);
	else if (!checkPortHost(value))
		error("Error: invalid port or host");
	else {
		config.port = strtol(value.substr(value.find(":") + 1).c_str(), NULL, 0);
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

	while (value.find_first_of(" \n\r\t") != std::string::npos) {
		serverName = value.substr(0, value.find_first_of(" \n\r\t"));
		count++;
		if (checkServerName(serverName) == false)
			error("Error: invalid server name in server block: " );
		config.server_name.push_back(serverName);
		value = value.substr(value.find_first_of(" \n\r\t") + 1);
	}
}

void	parseRoot(std::string value, t_config &config) {
	if (value.find_first_of(" \n\r\t") != std::string::npos)
		error("Error: invalid root");
	config.root = value;
}

void	parseAutoindex(std::string value, t_config &config) {
	if (value == "on")
		config.autoindex = true;
	else if (value == "off")
		config.autoindex = false;
	else
		error("Error: invalid autoindex");	
}

void parseIndex(std::string value, t_config &config) {
	std::string	idx;

	while (value.find_first_of(" \n\r\t") != std::string::npos) {
		idx = myTrim(value.substr(0, value.find_first_of(" \n\r\t")));
		if (idx == "")
			return ;
		config.index.push_back(myTrim(value.substr(0, value.find_first_of(" \n\r\t"))));
		value = myTrim(value.substr(value.find_first_of(" \n\r\t") + 1));
	}
	if (value != "")
		config.index.push_back(value);
}

void parseErrorPage(std::string value, t_config &config) {
	std::string	error_page;

	while (value.find_first_of(" \n\r\t") != std::string::npos) {
		error_page = myTrim(value.substr(0, value.find_first_of(" \n\r\t")));
		if (error_page == "")
			return ;
		config.error_pages.push_back(myTrim(value.substr(0, value.find_first_of(" \n\r\t"))));
		value = myTrim(value.substr(value.find_first_of(" \n\r\t") + 1));
	}
	if (value != "")
		config.error_pages.push_back(value);
}

void	parseClientMaxBodySize(std::string value, t_config &config) {
	size_t	idx = value.find_first_not_of("0123456789");
	unsigned long	size;

	size = strtoul(value.c_str(), NULL, 0);
	if (idx != std::string::npos) {
		if (value.find_last_of("KMB") == value.length() - 1) {
			if (value[value.length() - 1] == 'K')
				size *= 1024;
			else if (value[value.length() - 1] == 'M')
				size *= 1024 * 1024;
			else if (value[value.length() - 1] == 'B')
				;
			else
				error("Error: not a correct size - K (kilobit), M (megabit), B (bit)");
		}
		else
			error("Error: invalid client body max size syntax");
		config.client_max_body_size = size;
	}
}

void	parseAllowedMethods(std::string text, t_config &config) {
	std::string	methods[5] = { "GET", "POST", "DELETE", "PUT", "HEAD" };
	std::string	method;
	int count = 0;

	while (text.find_first_of(" \n\r\t") != std::string::npos) {
		method = text.substr(0, text.find_first_of(" \n\r\t"));
		count++;
		if (std::find(methods, methods + 5, method) == methods + 5)
			error("Error: invalid method in server block: ");
		
		if (std::find(config.allowed_methods.begin(), config.allowed_methods.end(), method) != config.allowed_methods.end())
			continue;
		config.allowed_methods.push_back(method);
		text = myTrim(text.substr(text.find_first_of(" \n\r\t") + 1));
	}
	if (text != "") {
		count++;
		if (std::find(methods, methods + 5, text) == methods + 5)
			error("Error: invalid method in server block: ");
		if (std::find(config.allowed_methods.begin(), config.allowed_methods.end(), text) != config.allowed_methods.end())
			return ;
		config.allowed_methods.push_back(text);
	}
}

void	parseLocationBlock(std::string text, t_config &config) {
	t_location	location;

	location.regex = false;
	location.exact_path = false;
	text = myTrim(text.substr(8));
	if (text.at(0) == '~')
		location.regex = true;
	else if (text.at(0) == '=')
		location.exact_path = true;
	text = myTrim(text.substr(text.find_first_not_of(" \n\r\t~=")));
	location.path = text.substr(0, text.find_first_of(" \n\r\t{"));
	if (location.path == "")
		error("Error: location block must have a path");
	text = myTrim(text.substr(text.find_first_of(" \n\r\t{")));
	if (text.at(0) != '{')
		error("Error: location block must start with {");
	location.content = myTrim(text.substr(1, text.find_last_of("}") - 1));
	config.locations.push_back(location);
}

void	fillKeyValueArgs(std::string text, t_config &config) {
	std::string	key;
	std::string	value;

	key = text.substr(0, text.find_first_of(" \n\r\t"));
	value = text.substr(text.find_first_of(" \n\r\t") + 1);
	value = myTrim(value);

	if (key == "listen")
		parseListen(value, config);
	else if (key == "server_name")
		parseServerName(value, config);
	else if (key == "root")
		parseRoot(value, config);
	else if (key == "autoindex")
		parseAutoindex(value, config);
	else if (key == "index")
		parseIndex(value, config);
	else if (key == "error_page")
		parseErrorPage(value, config);
	else if (key == "client_max_body_size")
		parseClientMaxBodySize(value, config);
	else if (key == "allowed_methods")
		parseAllowedMethods(value, config);
	else
		error("Error: invalid instruction: " + key);


	(void)config;

}

void resetConfig(t_config &config) {
	config.port = 0;
	config.host = "0.0.0.0";
	config.server_name.clear();
	config.root = "";
	config.valid = true;
	config.autoindex = false;
	config.index.clear();
	config.error_pages.clear();
	config.client_max_body_size = 1048576;
	config.allowed_methods.clear();
	config.locations.clear();
	config.cgi_script = "";
	 
}

std::vector<t_config>	parseServerBlocks(std::vector<std::string> serverBlocks) {
	std::vector<std::string>::iterator	it;
	t_config							config;
	std::string							content;
	std::string							tmp;
	std::vector<t_config>				tmpVec;

	for (it = serverBlocks.begin(); it != serverBlocks.end(); it++) {
		resetConfig(config);
		content = (*it).substr(findServerAndLocation(*it,0,1), (*it).find_last_of("}"));
		if (content.find(";") == std::string::npos)
			error("Error: no instruction in server block");
		while (content.find(";") != std::string::npos) {
			tmp = content.substr(0, content.find(";"));
			if (tmp.find_first_of(" \n\r\t") == std::string::npos)
				error("Error: invalid instruction, there should be spaces between the instruction and the parameters");
			if (findServerAndLocation(tmp, 0, 0, 1) != std::string::npos) {
				tmp = myTrim(content.substr(0, content.find("}") + 1));
				parseLocationBlock(tmp, config);
				content = content.substr(content.find("}") + 1);
				continue;
			}
			fillKeyValueArgs(myTrim(tmp), config);
			content = content.substr(content.find(";") + 1);
		}
		tmpVec.push_back(config);
	}
	return tmpVec;
}

std::vector<t_config>	parse(std::string text) {
	std::vector<std::string>	serverBlocks;

	divideServers(text, &serverBlocks);
	return(parseServerBlocks(serverBlocks));
}

bool	parseRequest(std::string buffer, t_request &request) {
	std::string	key;
	std::string	methods[5] = { "GET", "POST", "DELETE", "PUT", "HEAD" };

	buffer = myTrim(buffer);
	request.method = buffer.substr(0, buffer.find_first_of(" "));
	std::cout << "request.method: " << request.method << std::endl;
	buffer = myTrim(buffer.substr(buffer.find_first_of(" ") + 1));
	request.path = buffer.substr(0, buffer.find_first_of(" "));
	std::cout << "request.path: " << request.path << std::endl;
	if (std::find(methods, methods + 5, request.method) == methods + 5)
		return (0);
	buffer = myTrim(buffer.substr(buffer.find_first_of("\n") + 1));
	while (buffer.find_first_of("\n") != std::string::npos) {
		key = buffer.substr(0, buffer.find_first_of(":"));
		if (request.headers.find(key) == request.headers.end())
			return (0);
		request.headers[key] = buffer.substr(buffer.find_first_of(":") + 2, buffer.find_first_of("\n") - buffer.find_first_of(":") - 2);
		std::cout << buffer.substr(0, buffer.find_first_of(":")) << ": " << request.headers[key] << std::endl;
		buffer = myTrim(buffer.substr(buffer.find_first_of("\n") + 1));
	}
	key = buffer.substr(0, buffer.find_first_of(":"));
	if (request.headers.find(key) == request.headers.end())
		return (0);
	request.headers[key] = buffer.substr(buffer.find_first_of(":") + 2, buffer.find_first_of("\n") - buffer.find_first_of(":") - 2);
	std::cout << buffer.substr(0, buffer.find_first_of(":")) << ": " << request.headers[key] << std::endl;
	return (1);
}


void	parseAllowedMethods(std::string text, t_config &config) {
	std::string	methods[5] = { "GET", "POST", "DELETE", "PUT", "HEAD" };
	std::string	method;
	int count = 0;

	while (text.find_first_of(" \n\r\t") != std::string::npos) {
		method = text.substr(0, text.find_first_of(" \n\r\t"));
		count++;
		if (std::find(methods, methods + 5, method) == methods + 5)
			error("Error: invalid method in server block: ");
		
		if (std::find(config.allowed_methods.begin(), config.allowed_methods.end(), method) != config.allowed_methods.end())
			continue;
		config.allowed_methods.push_back(method);
		text = myTrim(text.substr(text.find_first_of(" \n\r\t") + 1));
	}
	if (text != "") {
		count++;
		if (std::find(methods, methods + 5, text) == methods + 5)
			error("Error: invalid method in server block: ");
		if (std::find(config.allowed_methods.begin(), config.allowed_methods.end(), text) != config.allowed_methods.end())
			return ;
		config.allowed_methods.push_back(text);
	}
}

void	parseLocationContent(t_location *location) {
	// TODO parse loc
	(void)location;
	std::cout << "location content: " << location->content << std::endl;
	// lo

}

