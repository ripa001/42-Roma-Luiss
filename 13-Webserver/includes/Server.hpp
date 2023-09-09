/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:09 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:09 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"
#include "Cgi.hpp"

#define IOV_MAX 1024

class Server
{
	private:

		typedef std::vector<std::pair<std::string, std::string> >::iterator	iterator;
		Server();

		std::vector<t_config>								_configs;
		t_config*											_config;
		std::vector<std::pair<std::string, std::string> >	_cacheRequests; 
		struct sockaddr_in									_sin;
		struct sockaddr_in									_client;
		socklen_t											_size;
		int													_sockfd;
		std::vector<t_connection>							_connections;			
		std::map<std::string, std::string>					_cookies;

		void												defaultAnswer(int err, t_connection conn);
		t_location*											findLocationByConnection(t_connection &conn);
		t_config*											findConfigByConnection(t_connection &conn);
		bool												isRegex(std::string path, t_config *config);
		std::string											generateFilename(const t_connection &conn);
		bool												removeFile(std::string &filename);
		int													get(t_connection &conn);
		int													post(t_connection &conn);
		int													head(t_connection & conn);
		int													put(t_connection & conn);
		int 												del(t_connection &conn);
		int 												tryFiles(t_connection &conn);
		std::string											findFiles(std::string &filename, t_connection &conn, std::string &fullPath);
		void												answer(std::string fullPath, struct dirent *dirent, t_connection conn);
		void												correctPath(std::string &filename, t_connection &conn);
		void												answerAutoIndex(std::string full_path, DIR *dir, t_connection conn);
		void												dirAnswer(std::string fullPath, struct dirent* dirent, t_connection conn);
		int													encoding(t_connection& conn);
		bool												contentType(t_connection & conn);
		std::string											generateCookie(std::string name);
		int													chunkEncodingCleaning(t_connection &conn);


	public:
		bool												startServer();
		int													getSocket();
		int													newConnection(int socket);
		int													handleClient(int socket);
		t_config*											getConfig();
		t_config*											getConfig(int i);
		t_config											getConfigByConnection(t_connection &conn);
		std::vector<t_config>								getConfigs();
		std::vector<t_connection>::iterator					findSocket(std::vector<t_connection> connections, int socket);
		std::vector<t_connection>::iterator					findSocket(int socket);
		std::string											defineFileType(char *filename);
		int													launchCgi(t_connection &connection);
		Server(t_config config);
		~Server();
};
