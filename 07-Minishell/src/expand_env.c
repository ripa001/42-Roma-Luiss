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

char	*ft_new_data(char *cmd, int j, int *x, char *current_env)
{
	char	*new_data;

	new_data = ft_substr(cmd, 0, j);
	new_data = ft_strjoin_free(new_data, current_env);
	if (&cmd[*x])
	{
		while (cmd[*x] != ' ' && cmd[*x])
			(*x)++;
		new_data = ft_strjoin_get(new_data, &cmd[*x]);
	}
	free(cmd);
	return (new_data);
}

int	ft_current_env2_help(char *new_data, int k)
{
	while (new_data[k] == '*')
		k++;
	return (k);
}

char	*ft_current_env2(char *cmd, int k, int *x, char *current_env)
{
	char	*current_env2;
	char	*new_data;
	int		flag;

	flag = 0;
	if (current_env)
	{
		k = 0;
		new_data = ft_substr(cmd, *x, ft_strchr_int(&cmd[*x], ' '));
		current_env2 = ft_strjoin_get(current_env, new_data);
		k = ft_current_env2_help(new_data, k);
		while (new_data[k])
		{
			if (new_data[k++] == '*')
				flag = 1;
		}
		current_env = ft_env_flag(flag, current_env2);
		free(new_data);
	}
	else
	{
		free(current_env);
		current_env = ft_substr(cmd, *x, ft_strchr_int(cmd, ' '));
	}
	return (current_env);
}

char	*ft_current_env(t_mini *mini, char *cmd, int *x, int j)
{
	char	*current_env;
	char	*current_env2;
	int		k;

	k = -1;
	if (ft_isdigit(cmd[*x]))
		current_env = ft_env_digit(cmd, x, j);
	else
	{
		while (ft_isalnum(cmd[*x]))
			(*x)++;
		current_env2 = ft_substr(cmd, j + 1, *x - j - 1);
		if (!current_env2 || !current_env2[0])
			current_env = ft_strdup("");
		else
		{
			current_env = ft_get_env(mini->env, current_env2);
			current_env = ft_current_env2(cmd, k, x, current_env);
		}
		free(current_env2);
	}
	return (current_env);
}

char	*expand_envars(char *cmd, t_mini *mini)
{
	int		x;
	int		j;
	int		quotes;
	char	*current_env;

	x = -1;
	quotes = 0;
	while (cmd[++x])
	{
		quotes = qquotes(cmd[x], quotes);
		if (cmd[x] == '$' && quotes != 1)
		{
			j = x++;
			current_env = expand_envars_help(cmd, &x, mini, j);
			cmd = ft_new_data(cmd, j, &x, current_env);
		}
		cmd = ft_tilde(cmd, x, mini, quotes);
	}
	return (cmd);
}
