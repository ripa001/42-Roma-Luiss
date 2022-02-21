/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:16:59 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/21 18:25:52 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig)
{
	static int	counter;

	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Messaggio ricevuto", 1);
		exit(0);
	}
	else
		counter++;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
	}
}

void	send_string(int pid, char *string)
{
	while (*string)
		send_char(pid, *string++);
}

int	main(int argc, char *argv[])
{
	int				pid;
	int				i;

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	if (argc != 3 || !ft_isnumber(argv[1]))
	{
		ft_putstr_fd("Errore argomenti della funzione", 1);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	send_string(pid, argv[2]);
	i = -1;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
	while (1)
		;
}
