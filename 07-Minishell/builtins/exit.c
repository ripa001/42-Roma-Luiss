/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:19 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/24 19:45:04 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_command( t_mini *mini, char **cmd)
{
	(void)mini;
	(void)cmd;
	ft_putendl_fd("exit", 1);
	mini->exit = 1;
}
