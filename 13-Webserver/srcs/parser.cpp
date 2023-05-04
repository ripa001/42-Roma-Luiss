#include "../includes/utils.hpp"

size_t findServerLocation(const std::string& str, size_t skipChars = 0, size_t returEnd = 0, int location = 0) {
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
			while (!std::isspace(str[pos]))
				++pos;
			while (std::isspace(str[pos]))
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
	if (findServerLocation(text) == std::string::npos)
		error("Error: no server block found or server block not at the beginning of the file");
	// loop until there are no more server blocks check and clean
	while ((found = findServerLocation(text)) != std::string::npos) {
		serverBlockTmp = text.substr(found, findServerLocation(text, found + 1));
		// check if there are comments
		std::cout << "serverBlockTmp: " << findServerLocation(text, found + 1) << found << std::endl;
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


void	fillKeyValueArgs(std::string &text, t_config &config) {
	key = text.substr(0, text.find_first_of(" \n\r\t"));
	value = text.substr(text.find_first_of(" \n\r\t") + 1);
	// parse arguments
	std::cout << "key: " << key << std::endl;
	std::cout << "value: " << value << std::endl;
	std::string	toCompare[9] = { "listen", "server_name", "root", "autoindex", "index", "error_page", "client_max_body_size", "allowed_methods", "location" };
	
}

void	parseServerBlocks(std::vector<std::string> serverBlocks) {
	std::vector<std::string>::iterator	it;
	t_config							config;
	std::string							content;
	std::string							tmp;

	std::cout << "serverBlocks.size(): " << serverBlocks.size() << std::endl;
	for (it = serverBlocks.begin(); it != serverBlocks.end(); it++) {
		content = (*it).substr(findServerLocation(*it,0,1), (*it).find_last_of("}"));
		if (content.find(";") == std::string::npos)
			error("Error: no instruction in server block");
		while (content.find(";") != std::string::npos) {
			tmp = content.substr(0, content.find(";"));
			if (tmp.find_first_of(" \n\r\t") == std::string::npos)
				error("Error: invalid instruction, there should ne spaces between the instruction and the parameters");
			if (findServerLocation(tmp, 0, 0, 1) != std::string::npos) {
				tmp = myTrim(content.substr(0, content.find("}") + 1));
				// parseLocationBlock(tmp, config);
				std::cout << "location: " << tmp << std::endl;
				content = content.substr(content.find("}") + 1);
				continue;
			}
			tmp = fillKeyValueArgs(myTrim(tmp), config));
			
			(void)config;
			// if (key.find("location")
			content = content.substr(content.find(";") + 1);
			
		}
		
		// while (content.find("location") != std::string::npos) {
		// 	// parseLocationBlock(content);

		// }
		
		
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

