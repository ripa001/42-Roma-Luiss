/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:30 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:30 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool	Server::startServer() {
	int reuse = 1;
	
	_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sockfd < 0)
		error("Error: Socket could not be created");
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
		if ((*it).socketfd == socket)
			return it;
		it++;
	}
	return it;
}

int	Server::chunkEncodingCleaning(t_connection &conn) {
	if (conn.buff_size < 0) {
		char buffer[2048] = {0};
		int dataRead = recv(conn.socketfd, buffer, 1, 0);
		if (dataRead <= 0) {
			error("Error: Chunked encoding error", _sockfd);
		}
		conn.buffer.append(buffer);
		if (conn.buffer.find("\r\n") != conn.buffer.npos) {
			conn.buff_size = strtoul(conn.buffer.c_str(), NULL, 16);
			conn.buffer.clear();
		}
	} else if (conn.buff_size > 0) {
		unsigned char buffer[conn.buff_size];
		buffer[0] = 0;
		int totalRead = 0;
		while (totalRead < conn.buff_size) {
			int dataRead = recv(conn.socketfd, buffer, conn.buff_size - totalRead, MSG_DONTWAIT);
			if (dataRead < 0)
				usleep(10000);
			else if (dataRead > 0)
				totalRead += dataRead;
		}
		recv(conn.socketfd, buffer, 2, 0);
		conn.buff_size = -1;
	} else if (conn.buff_size == 0) {
		char chunk[4];
		recv(conn.socketfd, chunk, sizeof(chunk), MSG_DONTWAIT);
		conn.buff_size = -1;
		return 1;
	}
	return 0;
}

void	Server::defaultAnswer(int err, t_connection conn) {
	std::string tmpString;
	std::stringstream body;
	std::ifstream file;

	if (conn.config.error_pages.size() && err != 500)
	{
		body << err;
		for (std::vector<std::string>::iterator it = conn.config.error_pages.begin(); it != conn.config.error_pages.end(); it++) {
			if (body.str() == (*it).substr(0, 3))
			{
				if (*(_config->root.end() - 1) != '/')
					_config->root.push_back('/');
				file.open((_config->root + *it).c_str());
				if (!file)
				{
					file.close();
					defaultAnswer(500, conn);
					return;
				}
				break;
			}
		}
	}
	switch (err)
	{
		case 100: tmpString = "100 Continue"; break ;
		case 200: tmpString = "200 OK"; break ;
		case 201: tmpString = "201 Created"; break ;
		case 202: tmpString = "202 Accepted"; break ;
		case 203: tmpString = "203 Non-Authoritative Information"; break ;
		case 204: tmpString = "204 No content"; break ;
		case 205: tmpString = "205 Reset Content"; break ;
		case 206: tmpString = "206 Partial Content"; break ;
		case 400: tmpString = "400 Bad Request"; break ;
		case 401: tmpString = "401 Unauthorized"; break ;
		case 402: tmpString = "402 Payment Required"; break ;
		case 403: tmpString = "403 Forbidden"; break ;
		case 404: tmpString = "404 Not Found"; break ;
		case 405: tmpString = "405 Method Not Allowed"; break ;
		case 406: tmpString = "406 Not Acceptable"; break ;
		case 411: tmpString = "411 Length Required"; break ;
		case 413: tmpString = "413 Request Entity Too Large"; break ;
		case 500: tmpString = "500 Internal Server Error"; break ;
		case 501: tmpString = "501 Not Implemented"; break ;
		case 510: tmpString = "510 Not Extended"; break ;
		default: break ;
	}
	conn.response.line = "HTTP/1.1 " + tmpString;	
	if (file.is_open())
	{
		body.clear();
		body << file.rdbuf();
		file.close();
		conn.response.body = body.str();
		conn.response.body.erase(0, 3);
		body.str("");
		body << conn.response.body.length();
		findKey(conn.response.headers, "Content-Length")->second = body.str();
		tmpString.clear();
	}
	else if (err != 100)
	{
		conn.response.body = "<html>\n<head><title>" + tmpString + "</title></head>\n<body>\n<center><h1>" + tmpString + "</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n";
		body.str("");
		body << conn.response.body.length();
		findKey(conn.response.headers, "Content-Length")->second = body.str();
		tmpString.clear();
	}

	if (err == 405)
	{
		for (std::vector<std::string>::iterator iter = conn.config.allowed_methods.begin(); iter != conn.config.allowed_methods.end(); iter++) {
			if (findKey(conn.response.headers, "Allow")->second.length())
				findKey(conn.response.headers, "Allow")->second += " " + *iter;
			else
				findKey(conn.response.headers, "Allow")->second += *iter;
		}
	}

	tmpString = conn.response.line + "\r\n";
	std::map<std::string, std::string>::iterator iter = conn.response.headers.begin();
	findKey(conn.response.headers, "Connection")->second = "close";

	while (iter != conn.response.headers.end())
	{
		if ((*iter).second.length())
			tmpString += (*iter).first + ": " + (*iter).second + "\r\n";
		iter++;
	}
	if (err != 100 && conn.request.method != "HEAD")
		tmpString += "\r\n" + conn.response.body + "\r\n";
	else
		tmpString += "\r\n";
	send(conn.socketfd, tmpString.c_str(), tmpString.size(), 0);
}

// TODO check for config
t_config*	Server::findConfigByConnection(t_connection &conn) {
	std::string	serverName = conn.request.headers["Host"];


	if (serverName.find(":") != serverName.npos)
		serverName = serverName.substr(0, serverName.find(":"));

	if (!std::strncmp(serverName.c_str(), "localhost", 9) || serverName.find("localhost") != serverName.npos)
		return (&(*(_configs.begin())));
		
	for (std::vector<t_config>::iterator iter = _configs.begin(); iter != _configs.end(); iter++)
	{
		for (std::vector<std::string>::iterator serverNameIt = iter->server_name.begin(); serverNameIt != iter->server_name.end(); serverNameIt++) {
			if (!serverName.compare(*serverNameIt))
				return (&(*iter));
		}
	}
	return (&(*(_configs.begin())));
}

bool	Server::isRegex(std::string path, t_config *config) {
	std::vector<t_location>::iterator iter = config->locations.begin();

	while (iter != config->locations.end()) {
		if (iter->regex && !std::strncmp(iter->path.c_str(), &(path.c_str())[path.length() - iter->path.length()], iter->path.length()))
			return true;
		iter++;
	}
	return false;
}

t_location*	Server::findLocationByConnection(t_connection &conn) {
	bool regex;
	t_location *ret = NULL;

	_config = findConfigByConnection(conn);
	regex = isRegex(conn.request.path, _config);
	for (std::vector<t_location>::iterator iter = _config->locations.begin(); !regex && iter != _config->locations.end(); iter++)
		if (!iter->regex && !std::strncmp(iter->path.c_str(), conn.request.path.c_str(), iter->path.length()))
			if (!ret || iter->path.length() > ret->path.length())
				ret = &(*iter);
	if (!ret && !regex)
		for (std::vector<t_location>::iterator iter = _config->locations.begin(); iter != _config->locations.end(); iter++)
			if (!iter->regex && !std::strncmp(iter->path.c_str(), conn.request.path.c_str(), conn.request.path.length()))
				if (!ret || iter->path.length() > ret->path.length())
					ret = &(*iter);
	if (regex)
		for (std::vector<t_location>::iterator iter = _config->locations.begin(); iter != _config->locations.end(); iter++)
			if (iter->regex && !std::strncmp(iter->path.c_str(), &(conn.request.path.c_str())[conn.request.path.length() - iter->path.length()], iter->path.length()))
				if (!ret || iter->path.length() > ret->path.length())
					ret = &(*iter);
	if (!ret)
		defaultAnswer(404, conn);
	return (ret);
}

t_config	Server::getConfigByConnection(t_connection &conn) {
	// t_config ret = *(findConfigByConnection(conn));
	t_config ret;
	std::string path = conn.request.path;
	std::string toCompare[9] = {"root", "autoindex", "index", "error_page", "client_max_body_size", "allowed_methods", "try_files", "return", "Cgi_pass"};
	if (path.find("?") != path.npos)
		path = path.substr(0, path.find("?"));
	s_config config = *(conn.location->config);
	if (config.client_max_body_size && std::strlen(conn.request.body.c_str()) > config.client_max_body_size) {
		defaultAnswer(413, conn);
		return (t_config(false));
	}
	for (std::vector<std::string>::iterator iter = config.try_files.begin(); iter != config.try_files.end(); iter++) {
		if (iter->find("$uri") != iter->npos) {
			size_t index = std::distance(config.try_files.begin(), iter);
			config.try_files[index].replace(iter->find("$uri"), iter->find("$uri") + 4, path);
		}
	}
	if (config.root.empty())
		config.root = _config->root;
	if (!config.port)
		config.port = _config->port;
	if (config.index.empty())
		config.index = _config->index;
	if (config.error_pages.empty())
		config.error_pages = _config->error_pages;
	if (!config.client_max_body_size)
		config.client_max_body_size = _config->client_max_body_size;
	if (config.allowed_methods.empty())
		config.allowed_methods = _config->allowed_methods;
	if (config.try_files.empty())
		config.try_files = _config->try_files;
	if (config.return_.empty())
		config.return_ = _config->return_;
	if (config.cgi_script.empty())
		config.cgi_script = _config->cgi_script;
	return (config);
}

// int 		VirtServ::get(t_connection & conn)
// {
// 	std::vector<std::pair<std::string, std::string> >::iterator it;
// 	for (it = _cacheRequests.begin(); it != _cacheRequests.end(); it++) {
// 		if (it->first == conn.headers) {
// 			conn.request.method.clear();
// 			send(conn.socketfd, it->second.c_str(), it->second.size(), 0);
// 			return 1;
// 		}
// 	}
	
// 	tryFiles(conn); conn.request.method.clear(); return 1;
// }

std::string Server::generateCookie(std::string name) {
	std::string ninjaName[28] = { "ka", "zu", "mi", "te", "ku", "lu","ji", 
								"ri", "ki", "zu", "me", "ta", "rin", "to", "mo", "no","no", 
								"ke", "shi", "ari", "chi", "do", "ru", "mei", "na", "fu", "zi" };
	
	std::string	ret;
	for (std::string::iterator it = name.begin(); it != name.end(); it++)
		ret.append(ninjaName[tolower(*it) - 'a']);
	return (ret);
}


std::string Server::defineFileType(char *filename)
{
	std::string toCompareText[4] = {".html", ".css", ".csv", ".xml"};
	std::string toCompareImage[6] = {".gif", ".jpeg", ".jpg", ".png", ".tiff", ".ico"};
	std::string toCompareApp[3] = {".js", ".zip", ".pdf"};
	std::string fileExtension = std::string(filename);
	size_t i;

	fileExtension = fileExtension.substr(fileExtension.find_last_of("."));

	for (i = 0; i < toCompareText->size(); i++)
	{
		if (!fileExtension.compare(toCompareText[i]))
			break;
	}

	if (i != toCompareText->size())
	{
		switch (i) {
			case 0: return ("text/html");
			case 1: return ("text/css");
			case 2:	return ("text/csv");
			case 3:	return ("text/xml");
			default: break;
		}
	}

	for (i = 0; i < toCompareImage->size(); i++)
	{
		if (!fileExtension.compare(toCompareImage[i]))
			break;
	}

	if (i != toCompareImage->size())
	{
		switch (i) {
			case 0: return ("image/gif");
			case 1: return ("image/jpeg");
			case 2: return ("image/jpeg");
			case 3: return ("image/png");
			case 4: return ("image/tiff");
			case 5: return ("image/x-icon");
			default: break;
		}
	}

	for (i = 0; i < toCompareApp->size(); i++)
	{
		if (!fileExtension.compare(toCompareApp[i]))
			break;
	}

	if (i != toCompareApp->size())
	{
		switch (i) {
			case 0: return ("application/javascript");
			case 1: return ("application/zip");
			case 2: return ("application/pdf");
			default: break;
		}
	}

	return ("text/plain");
}

void	Server::correctPath(std::string &filename, t_connection &conn) {
	std::string	tmp;

	(void)conn;
	for (std::vector<t_location>::iterator iter = _config->locations.begin(); iter != _config->locations.end(); ++iter) {
		if (filename.compare(0, iter->path.length(), iter->path) == 0 && iter->path.length() > tmp.length()) {
			tmp = iter->path;
		}
	}
	if (!tmp.empty()) {
		filename = filename.substr(tmp.length());
		if (!filename.empty() && filename.at(0) == '/' && filename.length() > 1) {
			filename = filename.substr(1);
		} else {
			filename.clear();
		}
	}

	if (!conn.request.arguments.empty()) {
		std::string argKey;
		std::string argValue;

		while (1) {
			std::size_t equalSignPos = conn.request.arguments.find("=");
			std::size_t ampersandPos = conn.request.arguments.find("&");
			if (equalSignPos != std::string::npos && conn.request.arguments[equalSignPos - 1] != '=') {
				argKey = conn.request.arguments.substr(0, equalSignPos);
				conn.request.arguments = conn.request.arguments.substr(equalSignPos + 1);
				argValue = conn.request.arguments.substr(0, ampersandPos - argKey.length() - 1);
				conn.cookie.insert(std::make_pair(argKey, argValue));
				conn.set_cookie = true;
			}
			if (ampersandPos != std::string::npos)
				conn.request.arguments = conn.request.arguments.substr(ampersandPos - argKey.length());
			else
				break ;
		}
	}
}

std::vector<std::string> findCookiesNames(std::string const &tmpBody) // check!!!!
{
	size_t restartHere = 0, valueEnd;
	std::string value;
	std::vector<std::string> inputNamesList;
	while (1)
	{
		restartHere = tmpBody.find("<input type=\"text\"", restartHere);
		if (restartHere != std::string::npos)
		{
			restartHere = tmpBody.find("name=\"", restartHere);
			if (restartHere != std::string::npos)
			{
				restartHere += 6;
				valueEnd = tmpBody.find("\"", restartHere);
				if (valueEnd != std::string::npos)
				{
					value = tmpBody.substr(restartHere, valueEnd);
					inputNamesList.push_back(value);
					restartHere = valueEnd + 1;
				}
			}
		}
		else
			break ;
	}
	return (inputNamesList);
}

void	Server::answer(std::string fullPath, struct dirent *dirent, t_connection conn) {
	std::stringstream stream;
	std::string tmpString;
	std::string tmpBody;
	std::ostringstream responseStream;
	std::string responseString;

	if (*fullPath.rbegin() != '/')
		fullPath.append("/");
	std::ifstream resource((fullPath + std::string(dirent->d_name)).c_str());
	if (!resource || !resource.is_open())
	{
		// std::cout << "cannot read file" << std::endl;
		return;
	}
	conn.response.line = "HTTP/1.1 200 OK";
	stream << resource.rdbuf();
	tmpBody = stream.str();
	stream.str("");
	std::string tmpBody2;
	// COOKIES PART HERE
	if (!std::strncmp(dirent->d_name, "registered.html", std::strlen(dirent->d_name))
		&& findKey(conn.request.headers, "Cookie")->second.find("name=") != findKey(conn.request.headers, "Cookie")->second.npos
		&& conn.set_cookie == false)
	{
		std::string value;

		value = findKey(conn.request.headers, "Cookie")->second;
		tmpBody2 = tmpBody.substr(0, tmpBody.find("greetings") + 11);
		while (value.find(";") != value.npos)
		{
			tmpBody2.append(value.substr(value.find("=") + 1, value.find(";") - value.find("=") - 1));
			// std::cout << "tmpBody2: " << value.substr(value.find("=") + 1, value.find(";") - value.find("=") - 1) << std::endl;
			if (value.find(";") != value.npos) {
				tmpBody2.append(" ");
				value = value.substr(value.find(";") + 1);
			}
		}
		tmpBody2.append(value.substr(value.find("=") + 1));
		tmpBody2.append(tmpBody.substr(tmpBody.find("greetings") + 11));
		tmpBody = tmpBody2;
	}
	else if (!std::strncmp(dirent->d_name, "registered.html", std::strlen(dirent->d_name))
		&& conn.set_cookie == true)
	{
		tmpBody2 = tmpBody.substr(0, tmpBody.find("greetings") + 11);
		tmpBody2.append("Cookie is set. Refresh");
		tmpBody2.append(tmpBody.substr(tmpBody.find("greetings") + 11));
		tmpBody = tmpBody2;
	}
	else if (!std::strncmp(dirent->d_name, "registered.html", std::strlen(dirent->d_name)))
	{
		tmpBody2 = tmpBody.substr(0, tmpBody.find("greetings") + 11);
		tmpBody2.append("sign in at <a href=\"register.html\">register.html</a>");
		tmpBody2.append(tmpBody.substr(tmpBody.find("greetings") + 11));
		tmpBody = tmpBody2;
	}
	std::map<std::string, std::string>::iterator iter2 = conn.response.headers.find("Content-Length");
	if (tmpBody.length())
	{
		stream << tmpBody.length();
		stream >> tmpString;
		(*iter2).second = tmpString;
	}
	else
		(*iter2).second = "0";
	findKey(conn.response.headers, "Content-Type")->second = defineFileType(dirent->d_name);
	conn.response.headers.find("Connection")->second = "close";
	if (conn.set_cookie)
	{
		std::string tmp;
		std::map<std::string, std::string>::iterator mapIter = conn.cookie.begin();
		//  qui bisogna parsare tutti i coockies e metterli in una stringa
		while (mapIter != conn.cookie.end())
		{
			tmp = tmp.append((*mapIter).first + "=" + (*mapIter).second);
			// std::cout << "tmp: " << tmp << std::endl;
			if (++mapIter != conn.cookie.end())
				tmp.append(";");
		}
		findKey(conn.response.headers, "Set-Cookie")->second = tmp;
	}
	conn.response.body = tmpBody;
	responseStream << conn.response.line << "\r" << std::endl;
	std::map<std::string, std::string>::iterator iter = conn.response.headers.begin();
	std::string tmpVal;
	std::string tmpStr;
	while (iter != conn.response.headers.end())
    {
        if ((*iter).first == "Set-Cookie" && !(*iter).second.empty())
        {
            tmpVal = (*iter).second;
            while (tmpVal.find(";") != tmpVal.npos)
            {
                tmpStr += (*iter).first + ": " + tmpVal.substr(0, tmpVal.find(";")) + "\t\n";
				tmpVal = tmpVal.substr(tmpVal.find(";") + 1);
            }
            tmpStr += (*iter).first + ": " + tmpVal + "\r\n";
        }
        else if ((*iter).second.length())
            tmpStr += (*iter).first + ": " + (*iter).second + "\r\n";
        
        iter++;
    }
	responseStream << tmpStr;
	if (conn.request.method != "HEAD")
		responseStream << "\r\n" << conn.response.body;
	else
		responseStream << "\r\n";
	responseString = responseStream.str();
	if (responseString.size() > IOV_MAX)
	{
		while (responseString.size() > IOV_MAX) {
			send(conn.socketfd, responseString.c_str(), IOV_MAX, MSG_NOSIGNAL);
			responseString = responseString.substr(IOV_MAX);
		}
		send(conn.socketfd, responseString.c_str(), responseString.size(), MSG_NOSIGNAL);
	} else 
		send(conn.socketfd, responseString.c_str(), responseString.size(), MSG_NOSIGNAL);
	resource.close();
}

std::string Server::findFiles(std::string &filename, t_connection &conn, std::string &fullPath) {
	if (filename.compare(0, conn.location->path.length(), conn.location->path) == 0) {
		filename = filename.substr(std::strlen(conn.location->path.c_str()));
		if (*filename.begin() == '/' && filename.length() > 1)
			filename = filename.substr(1);
		else if (*filename.begin() == '/')
			filename = "";
		else if (filename.size() == 0)
			filename = "/";
		if (filename.find('/') != std::string::npos) {
			if (*fullPath.rbegin() != '/')
				fullPath = std::string(fullPath) + "/" + filename.substr(0, filename.find_last_of("/"));
			else
				fullPath = std::string(fullPath) + filename.substr(0, filename.find_last_of("/"));
			filename = filename.substr(filename.find_last_of("/"));
			if (!filename.empty() && filename[0] == '/' && filename.length() > 1)
				filename = filename.substr(1);
			else if (!filename.empty() && filename[0] == '/')
				filename.clear();
		}
	}
	
	return (fullPath);
}

void Server::answerAutoIndex(std::string fullPath, DIR *dir, t_connection conn) {
	std::vector<struct dirent*> dirents;
	std::ostringstream output;
	std::ostringstream body;
	std::ostringstream size;
	std::string name;
	struct stat attr;
	struct dirent* entry;

	if ((*fullPath.end() - 1) != '/')
		fullPath.push_back('/');
	while ((entry = readdir(dir)))
	{
		// name = std::string(entry->d_name);
		if (entry->d_type == DT_DIR)
			// dirents.push_front(entry);
			dirents.insert(dirents.begin(), entry);
		// if (name != "." && name != "..")
		dirents.push_back(entry);
	}

	conn.response.line = "HTTP/1.1 200 OK";
	conn.response.body = "<html>\n<head><title>Index of " + conn.request.line.substr(0, conn.request.line.find_first_of(" ")) + "</title></head>\n<body>\n<h1>Index of " + conn.request.line.substr(0, conn.request.line.find_first_of(" ")) + "</h1><hr><pre>";
	while (!dirents.empty()) {
		std::string name = dirents.front()->d_name;
		if (name != "." && name != "..")
		{
			stat((fullPath + name).c_str(), &attr);
			size << static_cast<size_t>(attr.st_size);
			body << "<a href=\"" << name << "\">" << name << "</a>";

			if (dirents.front()->d_type == DT_DIR)
				body << "/";

			body.width(52 - name.length());
			body << ' ';
			body.width(21);
			body << (dirents.front()->d_type == DT_DIR ? "-" : size.str());
			body << '\n';
		}
		dirents.erase(dirents.begin());
	}
	body << "</pre><hr></body>\n</html>";
	conn.response.body += body.str();
	output << "HTTP/1.1 200 OK\r\n";
	output << "Content-Length: " << body.str().length() << "\r\n";
	output << "Connection: close\r\nDate: " << getDateTime() << "\r\n";
	output << "Content-Type: text/html\r\n";
	output << "\r\n" << conn.response.body;

	std::string response = output.str();
	_cacheRequests.push_back(std::make_pair(conn.headers, response));
	send(conn.socketfd, response.c_str(), response.length(), 0);
}

void Server::dirAnswer(std::string fullPath, struct dirent* dirent, t_connection conn) {
	if (*fullPath.rbegin() != '/')
		fullPath.append("/");
	std::string path = dirent ? fullPath + dirent->d_name + "/" : fullPath;
	DIR* dir = opendir(path.c_str());
	if (!dir)
	{
		defaultAnswer(404, conn);
		return;
	}
	if (!conn.config.autoindex || !conn.config.index.empty())
	{
		while(struct dirent* entry = readdir(dir))
		{
			if (std::find(conn.config.index.begin(), conn.config.index.end(), entry->d_name) != conn.config.index.end())
			{
				answer(path, entry, conn);
				closedir(dir);
				return ;
			}
		}
		defaultAnswer(404, conn);
	} else
		answerAutoIndex(path, dir, conn);
	closedir(dir);

}


int Server::tryFiles(t_connection &conn) {
	std::vector<std::string>::iterator it = conn.config.try_files.begin();
	std::string fullPath = conn.config.root;
	std::string rootPath = fullPath;
	struct dirent* dirent = 0;
	DIR* directory;

	if (conn.config.allowed_methods.size() && std::find(conn.config.allowed_methods.begin(), conn.config.allowed_methods.end(), conn.request.method) == conn.config.allowed_methods.end()) {
		defaultAnswer(405, conn);
		return (1);
	}
	for (;it != conn.config.try_files.end(); it++) {
		fullPath = findFiles(*it, conn, fullPath);
		correctPath(*it, conn);
		if (!(directory = opendir(fullPath.c_str()))) {
			if (errno == EACCES)
				defaultAnswer(403, conn);
			else if (errno == ENOENT || errno == ENOTDIR)
				defaultAnswer(404, conn);
			return (1);
		}
		if ((*it).length()) {
			while ((dirent = readdir(directory)))
			{
				if (dirent->d_name == *it)
				{
					if (!((*it).compare("directory")))
					{
						dirAnswer(fullPath, NULL, conn);
						break;
					}
					if (dirent->d_type == DT_DIR)
					{
						dirAnswer(fullPath, dirent, conn);
						break;
					}
					answer(fullPath, dirent, conn);
					break;
				}
			}
			if (!dirent)
				defaultAnswer(404, conn);
			closedir(directory);
			return (1);
		} else if (conn.config.autoindex) {
			answerAutoIndex(rootPath, directory, conn);
			closedir(directory);
			return (1);
		} 
		else if (!conn.config.autoindex) {
			closedir(directory);
			dirAnswer(rootPath, NULL, conn);
			return (1);
		} 
		closedir(directory);
	}
	return (0);
}

int Server::encoding(t_connection& conn)
{
	int dataRead = 0;
	int totalRead = 0;
	if (conn.buff_size == -1 ) {
		unsigned char buffer = 0;
		dataRead = recv(conn.socketfd, &buffer, sizeof(unsigned char), 0);
		if (dataRead <= 0)
			error("Error reading from socket", _sockfd);
		conn.buffer.push_back(buffer);
		if (conn.buffer.find("\r\n") != conn.buffer.npos) {
			conn.buff_size = strtoul(conn.buffer.c_str(), NULL, 16);
			conn.buffer.clear();
		}
		return (0);
	} else if (!conn.buff_size) {
		char chunk[4];
		recv(conn.socketfd, chunk, sizeof(chunk), MSG_DONTWAIT);
		conn.buff_size = -1;
		return (1);
	} else {
		std::vector<unsigned char> buffer(conn.buff_size);
		while (totalRead < conn.buff_size) {
			dataRead = recv(conn.socketfd, buffer.data() + totalRead, conn.buff_size - totalRead, MSG_DONTWAIT);
			if (dataRead < 0) {
				usleep(1000);
			} else if (dataRead > 0) {
				totalRead += dataRead;
			}
		}
		conn.body.insert(conn.body.end(), buffer.begin(), buffer.end());
		dataRead = recv(conn.socketfd, buffer.data(), 2, 0);
		conn.buff_size = -1;
		return (0);
	}
}

bool		Server::contentType(t_connection & conn)
{
	std::string _boundary = findKey(conn.request.headers, "Content-Type")->second;
	std::string filename;
	unsigned char read[4096] = {0};
	int dataRead = 0;

	_boundary = _boundary.substr(_boundary.find_first_of("=") + 1, _boundary.find_last_of("\n") - 1);
	_boundary.append("--");
	_boundary.insert(0, "--");
	dataRead = recv(conn.socketfd, read, sizeof read, MSG_DONTWAIT);
	for (int i = 0; i < dataRead; i++)
		conn.body.push_back(read[i]);
	if (conn.body.find(_boundary) == conn.body.npos)
		return 0;
	filename = conn.body.substr(conn.body.find("filename"), std::string::npos);
	filename = filename.substr(filename.find_first_of("\"") + 1, filename.find_first_of("\n"));
	filename = _config->root + "/put_test/" + filename.substr(0, filename.find_first_of("\""));
	FILE *ofs = fopen(filename.c_str(), "wb+");
	conn.body = conn.body.substr(conn.body.find("\r\n\r\n") + 4, conn.body.npos);
	conn.body = conn.body.substr(0, conn.body.find(_boundary) - 2);
	for (size_t i = 0; i < conn.body.length(); i++)
			fwrite(&conn.body.at(i), 1, sizeof(char), ofs);
	fclose(ofs);
	conn.body.clear();
	return 1;
}

// int			VirtServ::execDelete(t_connection & conn)
// {
// 	if (conn.config.allowedMethods.size() && std::find(conn.config.allowedMethods.begin(), conn.config.allowedMethods.end(), "DELETE") == conn.config.allowedMethods.end() && findKey(conn.request.headers, "Transfer-Encoding")->second == "chunked")
// 	{
// 		if (chunkEncodingCleaning(conn) == 1) {
// 			defaultAnswerError(405, conn);
// 			return 1;
// 		}
// 		return 0;
// 	}
// 	else if (conn.config.allowedMethods.size() && std::find(conn.config.allowedMethods.begin(), conn.config.allowedMethods.end(), "DELETE") == conn.config.allowedMethods.end())
// 	{
// 		defaultAnswerError(405, conn);
// 		return 1;
// 	}
// 	else if (findKey(conn.request.headers, "Transfer-Encoding")->second == "chunked") {
// 		if (chunkEncoding(conn) == 1) {
// 			if (conn.body.size() > conn.config.client_max_body_size) {
// 				defaultAnswerError(413, conn);
// 				return 1;
// 			}
// 			std::string filename = conn.config.root;
// 			if (*(filename.end() - 1) != '/')
// 				filename.append("/");
// 			if (conn.config.root != _config->root)
// 			{
// 				std::string	path = conn.request.line.substr(conn.request.line.find_first_of(" \t"));
// 				path = path.substr(path.find_first_not_of(" \t"));
// 				path = path.substr(0, path.find_first_of(" ") - 1);
// 				path = path.substr(conn.location->location.length());
// 				if (path.at(0) == '/')
// 					path = path.substr(1);
// 				filename.append(path);
// 			}
// 			else
// 				filename.append(conn.request.line.substr(1, conn.request.line.find_first_of(" ") - 1));
// 			if (filename.at(0) == '/')
// 				filename = filename.substr(1);
// 			if (access(filename.c_str(), F_OK))
// 				defaultAnswerError(404, conn);
// 			else
// 			{
// 				remove(filename.c_str());
// 				defaultAnswerError(204, conn);
// 			}
// 			conn.body.clear();
// 			return 1;
// 		}
// 	}
// 	else
// 	{
// 		std::string filename = conn.config.root;
// 		if (*(filename.end() - 1) != '/')
// 			filename.append("/");
// 		if (conn.config.root != _config->root)
// 		{
// 			std::string	path = conn.request.line.substr(conn.request.line.find_first_of(" \t"));
// 			path = path.substr(path.find_first_not_of(" \t"));
// 			path = path.substr(0, path.find_first_of(" ") - 1);
// 			path = path.substr(conn.location->location.length());
// 			if (path.at(0) == '/')
// 				path = path.substr(1);
// 			filename.append(path);
// 		}
// 		else
// 			filename.append(conn.request.line.substr(1, conn.request.line.find_first_of(" ") - 1));
// 		if (conn.request.path.at(0) == '/')
// 			conn.request.path = conn.request.path.substr(1);
// 		if (access(filename.c_str(), F_OK))
// 			defaultAnswerError(404, conn);
// 		else
// 		{
// 			remove(filename.c_str());
// 			defaultAnswerError(204, conn);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }
std::string Server::generateFilename(const t_connection &conn) {
	std::string filename = conn.config.root;
	if (*(filename.end() - 1) != '/') filename.append("/");
	if (conn.config.root != _config->root) {
		
		std::string path = conn.request.line.substr(conn.request.line.find_first_of(" \t"));
		path = path.substr(path.find_first_not_of(" \t"));
		path = path.substr(0, path.find_first_of(" ") - 1);
		path = path.substr(conn.location->path.length());
		if (path.at(0) == '/')
			path = path.substr(1);
		filename.append(path);
	} else
		filename.append(conn.request.line.substr(1, conn.request.line.find_first_of(" ") - 1));
	return filename;
}

bool Server::removeFile(std::string &filename) {
	if (filename.at(0) == '/')
		filename = filename.substr(1);

	if (access(filename.c_str(), F_OK)) {
		return false;
	}

	if (remove(filename.c_str())) {
		return false;
	}
	return true;
}

int Server::del(t_connection &conn) {
	bool hasAllowedMethods = !conn.config.allowed_methods.empty();
	bool isChunkedTransfer = findKey(conn.request.headers, "Transfer-Encoding")->second == "chunked";

	if (hasAllowedMethods && std::find(conn.config.allowed_methods.begin(), conn.config.allowed_methods.end(), "DELETE") == conn.config.allowed_methods.end() && isChunkedTransfer) {
		if (chunkEncodingCleaning(conn) == 1) {
			defaultAnswer(405, conn);
			return 1;
		}
		return 0;
	} else if (hasAllowedMethods && std::find(conn.config.allowed_methods.begin(), conn.config.allowed_methods.end(), "DELETE") == conn.config.allowed_methods.end()) {
		defaultAnswer(405, conn);
		return 1;
	} else if (isChunkedTransfer) {
		if (encoding(conn) == 1) {
			if (conn.body.size() > conn.config.client_max_body_size) {
				defaultAnswer(413, conn);
				return 1;
			}
			std::string filename = generateFilename(conn);
			if (removeFile(filename))
				defaultAnswer(204, conn);
			else
				defaultAnswer(404, conn);
			conn.body.clear();
			return 1;
		}
	} else {
		std::string filename = generateFilename(conn);
		if (removeFile(filename)) {
			defaultAnswer(204, conn);
		} else {
			defaultAnswer(404, conn);
		}
		return 1;
	}
	return 0;
}

int Server::launchCgi(t_connection &connection)
{
	std::string output;
	if (findKey(connection.request.headers, "Transfer-Encoding")->second == "chunked")
	{
		if (this->encoding(connection) == 1)
		{
			std::string code;
			std::string contentType;
			Cgi Cgi(connection, connection.config.port);
			output = Cgi.executeCgi(connection.config, connection.path.c_str());
			if (output.find("Status: ") != output.npos)
			{
				code = output.substr(output.find("Status: ") + 8, output.npos);
				code = code.substr(0, code.find_first_of("\n"));
			}
			if (output.find("Content-Type: ") != output.npos)
			{
				contentType = output.substr(output.find("Content-Type ") + 17, output.npos);
				contentType = contentType.substr(0, contentType.find_first_of(";"));
			}
			output = output.substr(output.find("\r\n\r\n") + 4, output.npos);
			std::stringstream outputSize;
			outputSize << output.size();
			std::string _answer = "HTTP/1.1 200 OK\r\nServer: webserv\r\n" + contentType;
			_answer += "Date: " + getDateTime();
			_answer += "\r\nContent-Length: "; _answer.append(outputSize.str());
			_answer += "\r\nConnection: close\r\n\r\n";
			_answer += output;
			size_t size = _answer.size();
			// std::cout << "answer: " << _answer << std::endl;
			unsigned char *answer = (unsigned char *)malloc(sizeof(unsigned char) * size);
			memcpy(answer, _answer.c_str(), size);
			unsigned char *tmp = answer;
			while (1)
			{
				if (size <= 0x8000) {
					send(connection.socketfd, answer, size, 0);
					free(tmp);
					while (recv(connection.socketfd, NULL, 0, 0) < 0)
						usleep(50);
					return 1;
				}
				send(connection.socketfd, answer, 0x8000, 0);
				answer += 0x8000;
				size -= 0x8000;
			}
		}
	}
	// std::cout << "launchCgi" << std::endl;
	return (0);
}

int Server::post(t_connection &conn) {
	if (conn.config.cgi_script != "")
	{
		std::string filename;
		filename = conn.request.line.substr(0, conn.request.line.find_first_of(" "));
		// std::cout << "trying launch cgi" << std::endl;
		if (launchCgi(conn) == 1)
			return (1);
		return (0);
	}

	if (conn.config.allowed_methods.size() && std::find(conn.config.allowed_methods.begin(), conn.config.allowed_methods.end(), "POST") == conn.config.allowed_methods.end()) {
		if (chunkEncodingCleaning(conn) == 1) {
			defaultAnswer(405, conn);
			return (1);
		}
		return (0);
	}
	// for (std::map<std::string, std::string>::iterator iter = conn.request.headers.begin(); iter != conn.request.headers.end(); iter++)
	// 	// // std::cout << iter->first << ": " << iter->second << std::endl;
	if (findKey(conn.request.headers, "Transfer-Encoding")->second == "chunked") {
		if (encoding(conn) == 1) {
			if (conn.body.size() > conn.config.client_max_body_size) {
				defaultAnswer(413, conn);
				return 1;
			}
			std::string filename = conn.config.root;
			if (*(filename.end() - 1) != '/')
				filename.append("/");
			if (conn.config.root != _config->root)
			{
				std::string	path = conn.request.line.substr(conn.request.line.find_first_of(" \t"));
				path = path.substr(path.find_first_not_of(" \t"));
				path = path.substr(0, path.find_first_of(" ") - 1);
				path = path.substr(conn.location->path.length());
				if (path.at(0) == '/')
					path = path.substr(1);
				filename.append(path);
			}
			else
				filename.append(conn.request.line.substr(1, conn.request.line.find_first_of(" ") - 1));
			
			FILE* ofs = fopen(filename.c_str(), "wb+");
			if (!ofs) {
				// std::cout << "file not found" << std::endl;
				defaultAnswer(405, conn);
				return 1;
			}
			// // std::cout << "file found" << conn.body << std::endl;
			for (size_t i = 0; i < conn.body.size(); i++)
				fwrite(&conn.body.at(i), 1, sizeof(char), ofs);
			fclose(ofs);
			conn.body.clear();
			defaultAnswer(201,conn);
			return 1;
		}
	} else if (findKey(conn.request.headers, "Content-Type")->second != "") {
		// // std::cout << "content-type" << std::endl;
		// recv(conn.fd, read, sizeof read, MSG_DONTWAIT);

		if (contentType(conn) == 1) {
			defaultAnswer(201,conn);
			return 1;
		}
	}
	return 0;

}


int			Server::head(t_connection & conn)
{
	std::vector<std::pair<std::string, std::string> >::iterator it;
	for (it = _cacheRequests.begin(); it != _cacheRequests.end(); it++) {
		if (it->first == conn.headers) {
			conn.request.method.clear();
			send(conn.socketfd, it->second.c_str(), it->second.size(), 0);
			return 1;
		}
	}
	tryFiles(conn);
	conn.request.method.clear();
	return 1;
}

int			Server::put(t_connection & conn) {
	// if (conn.config.allowedMethods.size() && std::find(conn.config.allowedMethods.begin(), conn.config.allowedMethods.end(), "PUT") == conn.config.allowedMethods.end())
	if (conn.config.allowed_methods.size() && std::find(conn.config.allowed_methods.begin(), conn.config.allowed_methods.end(), "PUT") == conn.config.allowed_methods.end()) {
		if (chunkEncodingCleaning(conn) == 1) {
			defaultAnswer(405, conn);
			return 1;
		}
		return 0;
	}
	else if (findKey(conn.request.headers, "Content-Type")->second != "") {
		if (contentType(conn) == 1) {
			defaultAnswer(201,conn);
			return 1;
		}
	}
	else if (findKey(conn.request.headers, "Transfer-Encoding")->second == "chunked") {
		if (encoding(conn) == 1) {
			std::string filename = conn.config.root;
			if (*(filename.end() - 1) != '/')
				filename.append("/");
			if (conn.config.root != _config->root)
			{
				std::string	path = conn.request.line.substr(conn.request.line.find_first_of(" \t"));
				path = path.substr(path.find_first_not_of(" \t"));
				path = path.substr(0, path.find_first_of(" ") - 1);
				path = path.substr(conn.location->path.length());
				if (path.at(0) == '/')
					path = path.substr(1);
				filename.append(path);
			}
			else
				filename.append(conn.request.line.substr(1, conn.request.line.find_first_of(" ") - 1));
			FILE* ofs = fopen(filename.c_str(), "wb+");
			for (size_t i = 0; i < conn.body.size(); i++)
				fwrite(&conn.body.at(i), 1, sizeof(char), ofs);
			fclose(ofs);
			conn.body.clear();
			defaultAnswer(201,conn);
			return 1;
		}
	}
	return 0;
}

int Server::get(t_connection &conn) {
	std::vector<std::pair<std::string, std::string> >::iterator it;
	for (it = _cacheRequests.begin(); it != _cacheRequests.end(); it++) {

		if (it->first == conn.headers) {
			conn.request.method.clear();
			send(conn.socketfd, it->second.c_str(), it->second.size(), 0);
			return (1);
		}
	}
	tryFiles(conn); conn.request.method.clear(); return 1;
	return (1);
}

int	Server::handleClient(int socketfd) {
	std::vector<t_connection>::iterator it = findSocket(socketfd);
	if (it == _connections.end())
		return (0);
	struct linger	l;
	l.l_onoff = 1;
	l.l_linger = 0;
	(void)l;
	unsigned char buffer;

	if (it->request.method == "") {

		recv(socketfd, &buffer, sizeof(unsigned char), 0);
		it->buffer.push_back(buffer);
		if (it->buffer.find("\r\n\r\n") == (size_t)-1)
			return 0;
		if (parseRequest(it->buffer, it->request, *it) == 0) {
			defaultAnswer(400, *it);
			_connections.erase(it);
			return (1);
		}
		it->location = findLocationByConnection(*it);
		if (it->location->path == "") {
			defaultAnswer(404, *it);
			return (1);
		}
		it->config = getConfigByConnection(*it);
		if (it->config.valid == false) {
			_connections.erase(it);
			return (1);
		}
		it->headers = it->buffer;
		it->buffer.clear();
	}
	if (it->request.method == "GET" && get(*it) == 1) {
		usleep(200);
		setsockopt(it->socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
		close(it->socketfd);
		_connections.erase(it);
		return 1;
	} else if (it->request.method == "POST" && post(*it) == 1){
		usleep(200);
		setsockopt(it->socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
		close(it->socketfd);
		_connections.erase(it);
		return 1;
	} else if (it->request.method == "HEAD" && head(*it) == 1){
		usleep(200);
		setsockopt(it->socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
		close(it->socketfd);
		_connections.erase(it);
		return 1;
	} else if (it->request.method == "PUT" && put(*it) == 1){
		usleep(200);
		setsockopt(it->socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
		close(it->socketfd);
		_connections.erase(it);
		return 1;
	} else if (it->request.method == "DELETE" && del(*it) == 1){
		usleep(200);
		setsockopt(it->socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l));
		close(it->socketfd);
		_connections.erase(it);
		return 1;
	}
	
	return (0);
}

int	Server::newConnection(int socketfd) {
	socklen_t				addrlen;
	struct sockaddr_storage	remoteaddr;
	int						connection;

	addrlen = sizeof remoteaddr;
	connection = accept(socketfd, (struct sockaddr *)&remoteaddr, &addrlen);
	if (connection < 0)
	{
		perror("Error: Connection could not be accepted");
		return -1;
	}
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

Server::~Server() {}
