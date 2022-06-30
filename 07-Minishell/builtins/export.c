/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:00 by ebassi            #+#    #+#             */
/*   Updated: 2022/06/30 16:07:47 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_command2(char **cmd, t_mini *mini, int *k, char *env_n)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	if (env_n[ft_strlen(env_n) - 1] == '+' && ++flag)
		env_n[ft_strlen(env_n) - 1] = 0;
	if (ft_get_env(mini->env, env_n) == NULL)
		mini->env = ft_export_command3(cmd, mini, flag, *k);
	else
	{
		while (mini->env[++i])
		{
			if (ft_strncmp(mini->env[i], env_n, ft_strlen(env_n)) == 0 && \
			(mini->env[i][ft_strlen(env_n)] == '=' || \
			ft_strlen(env_n) == ft_strlen(mini->env[i])))
			{
				if (flag == 1)
					mini->env[i] = ft_strjoin_get(mini->env[i], \
					ft_strchr(cmd[*k], '=') + 1);
				else if (ft_strchr(cmd[*k], '='))
					mini->env[i] = ft_replace_env(mini->env[i], env_n, cmd[*k]);
			}
		}
	}
}

void	ft_export_helper(char *str, int *k, t_mini *mini)
{
	ft_putstr_fd("Export: \"", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd("\" not a valid identifier", STDERR);
	if (*k == 1)
		mini->ret = 1;
}

void	ft_export_command_help(t_mini *mini, char **cmd, int *k, int *j)
{
	int		flag;
	char	*env_n;

	if (ft_strchr(cmd[*k], '='))
		env_n = ft_substr(cmd[*k], 0, ft_strchr(cmd[*k], '=') - cmd[*k]);
	else
		env_n = ft_strdup(cmd[*k]);
	*j = -1;
	flag = 0;
	while (env_n[++(*j)] && flag == 0)
	{
		if (!ft_isalnum(env_n[*j]))
			flag = 1;
		if (*j == (int)ft_strlen(env_n) - 1 && \
			env_n[ft_strlen(env_n) - 1] == '+')
			flag = 0;
	}
	if (!flag)
	{
		ft_export_command2(cmd, mini, k, env_n);
		mini->ret = 0;
	}
	else
		ft_export_helper(cmd[*k], k, mini);
	free(env_n);
}

void	ft_export_command(char **cmd, t_mini *mini)
{
	int		k;
	int		j;

	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0 && !cmd[1])
	{
		ft_export_alone(mini->env);
		return ;
	}
	k = 0;
	j = 0;
	while (cmd[++k])
	{
		if (!ft_isalpha(cmd[k][0]))
		{
			ft_export_helper(cmd[k], &k, mini);
			continue ;
		}
		ft_export_command_help(mini, cmd, &k, &j);
	}
}
