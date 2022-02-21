/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:20:08 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/21 18:26:21 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *siginf, void *ptr)
{
	static unsigned char	c = 0;
	static int				i = 0;
	int						client_pid;

	(void)ptr;
	c |= (sig == SIGUSR2);
	client_pid = siginf->si_pid;
	if (++i == 8)
	{
		if (!c)
			kill(siginf->si_pid, SIGUSR2);
		ft_putchar_fd(c, 1);
		kill(siginf->si_pid, SIGUSR1);
		c = 0;
		i = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	client;
	char				*pid;
	pid_t				g_pid;

	g_pid = getpid();
	pid = ft_itoa((int)g_pid);
	if (!pid)
	{
		ft_putendl_fd("Errore itoa", 1);
		return (0);
	}
	ft_putstr_fd("In ascolto su pid: ", 1);
	ft_putendl_fd(pid, 1);
	client.sa_sigaction = handler;
	client.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &client, 0);
	sigaction(SIGUSR2, &client, 0);
	while (1)
		;
	return (1);
}
