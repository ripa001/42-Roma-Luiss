/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:22:27 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:22:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env_flag(int flag, char *current_env2)
{
	char	*current_env;

	if (!flag)
	{
		current_env = ft_strtrim(current_env2, "*");
		free(current_env2);
	}
	else
	{
		current_env = ft_strdup(current_env2);
		free(current_env2);
	}
	return (current_env);
}

char	*ft_tilde(char *cmd, int x, t_mini *mini, int quotes)
{
	char	*new_data;

	if (cmd[x] == '~' && !quotes)
	{
		new_data = ft_substr(cmd, 0, x);
		new_data = ft_strjoin_free(new_data, ft_get_env(mini->env, "HOME"));
		new_data = ft_strjoin_get(new_data, &cmd[x + 1]);
		free(cmd);
		return (new_data);
	}
	return (cmd);
}

char	*ft_env_digit(char *cmd, int *x, int j)
{
	char	*current_env;

	while (ft_isalnum(cmd[*x]))
		(*x)++;
	current_env = ft_substr(cmd, j + 2, *x - j - 1);
	return (current_env);
}
