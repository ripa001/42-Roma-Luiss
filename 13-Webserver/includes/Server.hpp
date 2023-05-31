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

class Server
{
	private:
		typedef std::vector<std::pair<std::string, std::string> >::iterator	iterator;
		Server();

		std::vector<t_config>								_configs;
		t_config*											_config;
		std::vector<std::pair<std::string, std::string> >	_storeReq; 
		struct sockaddr_in									_sin;
		struct sockaddr_in									_client;
		socklen_t											_size;
		int													_sockfd;
		std::vector<t_connection>							_connections;
		std::map<std::string, std::string>					_cookies;

		void												defaultAnswerError(int err, t_connection conn);
		t_location*											findLocationByConnection(t_connection &conn);
		t_config*											findConfigByConnection(t_connection &conn);
		bool												isRegex(std::string path, t_config *config);
		int													execGet(t_connection &conn);
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

		Server(t_config config);
		~Server();
};