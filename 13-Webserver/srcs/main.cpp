/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:45:19 by dripanuc          #+#    #+#             */
/*   Updated: 2023/05/18 10:45:19 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Webserver.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <config_file>" << std::endl;
		return 1;
	}
	WebServer webserver(argv[1]);
	// Create a webserver object
	// configs = parseConficurationFile(argv[1]);
	// servers = createServerBasedOnConfiguration(configs);

	// // Start the webserver
	// startListening();

	// // Wait for the webserver to finish
	// waitForWebserverToFinish(servers);

	// // Cleanup
	// cleanup(servers);
	return 0;
}
