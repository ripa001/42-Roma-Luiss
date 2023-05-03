#include "../includes/utils.hpp"

void divideServers(std::string text, std::vector<std::string> serverBlocks) {
	size_t found;
	std::string serverBlockTmp;

	// loop until there are no more server blocks check and clean
	if ((found = text.find("server {")) != 0)
		error("Error: no server block found or server block not at the beginning of the file");
	while ((found = text.find("server {")) != std::string::npos) {
		serverBlockTmp = text.substr(found, text.find("server {", found + 1));
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


		serverBlocks.push_back(serverBlockTmp);
		if (text.find("server {", found + 1) == std::string::npos)
			break;
		text = text.substr(text.find("server {", found + 1));

	}
	for (size_t i = 0; i < serverBlocks.size(); i++)
	{
		std::cout << serverBlocks[i] << std::endl;
	}

	

	

}

