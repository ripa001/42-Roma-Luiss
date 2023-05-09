# pragma once

# include <iostream>
# include <sstream>
# include <vector>
# include <map>
# include <fstream>
# include <cstring>
# include <cstdlib>
# include <cstdio>
#include <algorithm>

typedef	struct	s_location
{
	bool						regex;		// ~
	bool						exact_path;	// =
	std::vector<std::string>	allowed_methods;
	std::string					path;	// path
	std::string					content;// block
	s_location&	operator=(s_location const & rhs)
	{
		this->regex = rhs.regex;
		this->exact_path = rhs.exact_path;
		this->allowed_methods = rhs.allowed_methods;
		this->path = rhs.path;
		this->content = rhs.content;
		return (*this);
	}
}				t_location;


typedef struct	s_config
{
	unsigned short				port;					// listen
	std::string					host;
	std::vector<std::string>	server_name;			// server_name
	std::string					root;					// root
	bool						autoindex;				// autoindex
	std::vector<std::string>	index;					// index
	std::vector<std::string>	error_pages;				// error_page
	unsigned long				client_max_body_size;	// client_max_body_size
	std::vector<std::string>	allowed_methods;
	std::vector<t_location>		locations;			// location
	std::vector<std::string>	files;					// files to try
	std::string					cgi_script;
	bool						valid;

	s_config() : port(0)
	{
		root = "";
		host = "0.0.0.0";
		client_max_body_size = 1048576;
		valid = true;
		cgi_script = "";
	}
	s_config(s_config const & src)
	{
		port = src.port;
		server_name = src.server_name;
		autoindex = src.autoindex;
		index = src.index;
		error_pages = src.error_pages;
		allowed_methods = src.allowed_methods;
		files = src.files;
		root = src.root;
		host = src.host;
		client_max_body_size = src.client_max_body_size;
		valid = src.valid;
		cgi_script = src.cgi_script;
		locations = src.locations;
	}
	s_config&	operator=(s_config const & rhs)
	{
		port = rhs.port;
		server_name = rhs.server_name;
		autoindex = rhs.autoindex;
		index = rhs.index;
		error_pages = rhs.error_pages;
		allowed_methods = rhs.allowed_methods;
		files = rhs.files;
		root = rhs.root;
		host = rhs.host;
		client_max_body_size = rhs.client_max_body_size;
		valid = rhs.valid;
		cgi_script = rhs.cgi_script;
		locations = rhs.locations;
		return (*this);
	}
	s_config(bool val) : valid(val) {}
}				t_config;

void		error(std::string const err);
std::string	myTrim(std::string str);

// Parsing
std::vector<t_config>	parse(std::string text);
void 					divideServers(std::string text, std::vector<std::string> serverBlocks);
