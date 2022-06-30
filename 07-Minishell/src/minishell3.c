/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 18:49:34 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_tok_help(char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

char	*expand_envars_help(char *cmd, int *x, t_mini *mini, int j)
{
	char	*current_env;

	if (cmd[*x] == '?' && (*x)++)
		current_env = ft_itoa(mini->ret);
	else if (cmd[*x] == '$' && (*x)++)
		current_env = ft_itoa(getpid());
	else if (!cmd[*x] || cmd[*x] == ' ')
		current_env = ft_strdup("$");
	else
		current_env = ft_current_env(mini, cmd, x, j);
	return (current_env);
}
