/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:57:11 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/29 17:02:30 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **cmd, t_mini *mini)
{
	int		flag;
	char	**echo;

	flag = 0;
	(void)mini;
	(void)echo;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 3))
	{
		flag = 1;
		cmd++;
	}
	while (*++cmd)
	{
		ft_putstr_fd(*cmd, 1);
		if (*++cmd)
			write(1, " ", 1);
		cmd--;
	}
	if (!flag)
		write(STDOUT, "\n", 1);
	mini->ret = 0;
}
