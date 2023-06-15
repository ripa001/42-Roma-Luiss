/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:13 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:13 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

struct s_config;

typedef	struct	s_location
{
	bool						regex;		// ~
	bool						exact_path;	// =
	std::vector<std::string>	allowed_methods;
	std::string					path;	// path
	std::string					content;// block
	s_config					*config;
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
	std::vector<std::string>	try_files;			// files to try
	std::vector<std::string>	return_;
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
		try_files = src.try_files;
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
		autoindex = rhs.autoindex;
		index = rhs.index;
		error_pages = rhs.error_pages;
		server_name = rhs.server_name;
		allowed_methods = rhs.allowed_methods;
		try_files = rhs.try_files;
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

typedef struct	s_request
{
	std::string											line;
	std::string											method;
	std::string											path;
	std::string											arguments;
	std::map<std::string, std::string>					headers;
	std::string											body;

	s_request() {
		headers.insert(std::make_pair("Host", ""));
		headers.insert(std::make_pair("User-Agent", ""));
		headers.insert(std::make_pair("Accept", ""));
		headers.insert(std::make_pair("Accept-Language", ""));
		headers.insert(std::make_pair("Accept-Encoding", ""));
		headers.insert(std::make_pair("Connection", ""));
		headers.insert(std::make_pair("Upgrade-Insecure-Requests", ""));
		headers.insert(std::make_pair("Sec-Fetch-Dest", ""));
		headers.insert(std::make_pair("Sec-Fetch-Mode", ""));
		headers.insert(std::make_pair("Sec-Fetch-Site", ""));
		headers.insert(std::make_pair("Sec-Fetch-User", ""));
		headers.insert(std::make_pair("Content-Length", ""));
		headers.insert(std::make_pair("Content-Type", ""));
		headers.insert(std::make_pair("Expect", ""));
		headers.insert(std::make_pair("Transfer-Encoding", ""));
		headers.insert(std::make_pair("Cookie", ""));
	};

	~s_request() {
		headers.clear();
	};

}		t_request;

typedef struct	s_response
{
	std::string											line;
	std::map<std::string, std::string>					headers;
	std::string											body;

	s_response()
	{
		headers.insert(std::make_pair("Server", "webserv"));
		headers.insert(std::make_pair("Date", ""));
		headers.insert(std::make_pair("Content-Type", ""));
		headers.insert(std::make_pair("Content-Length", ""));
		headers.insert(std::make_pair("Last-Modified", ""));
		headers.insert(std::make_pair("ETag", ""));
		headers.insert(std::make_pair("Accept-Ranges", ""));
		headers.insert(std::make_pair("Protocol", ""));
		headers.insert(std::make_pair("Status-Code", ""));
		headers.insert(std::make_pair("Reason-Phrase", ""));
		headers.insert(std::make_pair("Location", ""));
		headers.insert(std::make_pair("Connection", ""));
		headers.insert(std::make_pair("Allow", ""));
		headers.insert(std::make_pair("Set-Cookie", ""));
	}
}				t_response;

typedef struct	s_connection
{
	int						socket;
	t_request				request;
	t_response				response;
	std::string				buffer;
	t_config				config;
	t_location*				location;
	std::string				headers;



	s_connection() {};
	s_connection(int i) : socket(i) {};
}				t_connection;

// typedef struct	s_connInfo
// {
// 	int									fd;
// 	std::string							buffer;
// 	std::string							headers;
// 	std::string							path;
// 	t_config							config;
// 	int									chunk_size;
// 	// t_request							request;
// 	// t_response							response;
// 	std::string							body;
// 	t_location*							location;
// 	bool								set_cookie;
// 	std::pair<std::string, std::string>	cookie;
	
// 	s_connInfo() : chunk_size(-1), set_cookie(false) {};
// 	s_connInfo(int i) : fd(i), chunk_size(-1), set_cookie(false) {};
// }			t_connInfo;

void		error(std::string const err);
std::string	myTrim(std::string str);

// Parsing
std::vector<t_config>	parse(std::string text);
bool					parseRequest(std::string buffer, t_request &request);
t_config		parseLocationContentConfig(std::string content, t_config &config);
// void					parseLocationContentConfig(t_connection &conn);
void 					divideServers(std::string text, std::vector<std::string> serverBlocks);
