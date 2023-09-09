#include "../includes/Cgi.hpp"

Cgi::Cgi()
{
	std::cout << "Cgi built" << std::endl;
}

char **Cgi::getEnv() const {
	char	**env = new char*[this->_env.size() + 1];
	int	j = 0;
	for (std::vector<std::pair<std::string, std::string> >::const_iterator i = this->_env.begin(); i != this->_env.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return env;
}


std::string Cgi::executeCgi(t_config &config, const char *path)
{
	pid_t   pid;
    int     std_cpy[2] = { dup(0), dup(1) };
    char    **env = this->getEnv();
    std::string _retBody = "";
	std::string script = config.cgi_script;
    // // UNCOMMENT TO PRINT ENV
    // int i = 0;
    // while (env[i])
    //     printf("%s\n", env[i++]);
        
    // use tmpFile() instead of pipe() to handle big amount of data
    FILE*   in = tmpfile();
	FILE*   out = tmpfile();
    int     fd_in = fileno(in);
    int     fd_out = fileno(out);

    write(fd_in, _body.c_str(), _body.size());
    lseek(fd_in, 0, SEEK_SET);

    pid = fork();
	if (pid == -1)
	{
		std::cout << "Error: fork failed" << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (!pid)
	{
		char *const args[3] = {strdup(script.c_str()), strdup(path), NULL};
        dup2(fd_in, 0);
		dup2(fd_out, 1);
        execve(script.c_str(), args, env);
		std::cout << "Error: execve failed" << std::endl;
		write(2, "Status: 500\r\n\r\n", 15);
		exit (0);
	}
	else
	{
		waitpid(-1, NULL, 0);
		lseek(fd_out, 0, SEEK_SET);
		char	buffer[1024];
		size_t  dataRead = 0;
		while ((dataRead = read(fd_out, buffer, sizeof buffer)) > 0) {
			for (size_t i = 0; i < dataRead; i++)
				_retBody.push_back(buffer[i]);
			memset(buffer, 0, sizeof buffer);
        }
	}
	fclose(in);
	fclose(out);
	close(fd_in);
	close(fd_out);

    dup2(std_cpy[0], 0);
    dup2(std_cpy[1], 1);

    for (size_t i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	return (_retBody);
}

Cgi::Cgi(t_connection &connection, unsigned short port)
{
	this->_body = connection.body;
	std::stringstream stringStream;
	stringStream << port;
	this->_env.push_back(std::make_pair("AUTH_TYPE", ""));
    this->_env.push_back(std::make_pair("CONTENT_LENGTH", ""));
    this->_env.push_back(std::make_pair("CONTENT_TYPE", "application/x-www-form-urlencoded"));
    this->_env.push_back(std::make_pair("GATEWAY_INTERFACE", "CGI/1.1"));
    this->_env.push_back(std::make_pair("PATH_INFO", connection.path.c_str()));
    this->_env.push_back(std::make_pair("PATH_TRANSLATED", connection.path.c_str()));
    this->_env.push_back(std::make_pair("QUERY_STRING", ""));
    this->_env.push_back(std::make_pair("REMOTE_ADDR", findKey(connection.request.headers, "Host")->second));
    this->_env.push_back(std::make_pair("REMOTE_HOST", ""));
    this->_env.push_back(std::make_pair("REMOTE_IDENT", ""));
    this->_env.push_back(std::make_pair("REMOTE_USER", ""));
    this->_env.push_back(std::make_pair("REQUEST_METHOD", connection.request.method));
    this->_env.push_back(std::make_pair("REQUEST_URI", connection.path.c_str()));
    this->_env.push_back(std::make_pair("SCRIPT_NAME", connection.config.cgi_script.substr(connection.config.cgi_script.find_last_of("/") + 1)));
    this->_env.push_back(std::make_pair("SERVER_NAME", "http://" + findKey(connection.request.headers, "Host")->second));
    this->_env.push_back(std::make_pair("SERVER_PORT", stringStream.str()));
    this->_env.push_back(std::make_pair("SERVER_PROTOCOL", "HTTP/1.1"));
    this->_env.push_back(std::make_pair("SERVER_SOFTWARE", "Webserv/1.0"));
    this->_env.push_back(std::make_pair("REDIRECT_STATUS", "200"));
	if (connection.headers.find("X-Secret") != connection.headers.npos)
		this->_env.push_back(std::make_pair("HTTP_X_SECRET_HEADER_FOR_TEST", connection.headers.substr(connection.headers.find("X-Secret") + 26, connection.headers.find_first_of("\r\n"))));
}

Cgi::~Cgi()
{
	std::cout << "Cgi destructed" << std::endl;
}
