/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:57:09 by ebassi            #+#    #+#             */
/*   Updated: 2022/06/23 00:41:30 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_pwd(t_mini *mini)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (wd)
	{
		ft_putendl_fd(wd, 1);
		free(wd);
		mini->ret = 0;
		return ;
	}
	free(wd);
	mini->ret = 1;
}
