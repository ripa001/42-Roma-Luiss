/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:57:13 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/29 22:04:06 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_dir2(char **cmd)
{
	ft_putstr_fd("cd: no such file or directory: ", STDERR);
	ft_putendl_fd(cmd[1], STDERR);
}

void	ft_update_env(char **env)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = -1;
	pwd = ft_get_env(env, "PWD");
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			tmp = env[i];
			tmp2 = getcwd(NULL, 0);
			env[i] = ft_strjoin("PWD=", tmp2);
			free(tmp);
			free(tmp2);
		}
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			tmp = env[i];
			env[i] = ft_strjoin("OLDPWD=", pwd);
			free(tmp);
		}
	}
	free(pwd);
}

char	*change_dir3(char **cmd, char **env, char *home_path)
{
	char	*str;
	char	*pwd;

	str = 0;
	if (!cmd[1])
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (cmd[1][0] == '~')
		str = ft_strjoin_free(ft_strdup(home_path), \
		ft_substr(str, 1, ft_strlen(str)));
	else if (cmd[1][0] == '-')
		str = ft_get_env(env, "OLDPWD");
	else if (cmd[1][0] == '/')
		str = ft_strdup(cmd[1]);
	else
	{
		str = ft_strjoin_get(ft_strdup("/"), cmd[1]);
		str = ft_strjoin_free(ft_strdup(pwd), str);
	}
	free(pwd);
	return (str);
}

void	ft_change_dir2(t_mini *mini)
{
	char	*str;

	str = ft_get_env(mini->env, "HOME");
	chdir(str);
	ft_update_env(mini->env);
	free(str);
}

void	ft_change_dir(char **cmd, t_mini *mini)
{	
	char	*str;
	char	*str2;

	if (!cmd[1])
	{
		ft_change_dir2(mini);
		mini->ret = 0;
	}
	else
	{
		str2 = ft_get_env(mini->env, "HOME");
		str = change_dir3(cmd, mini->env, str2);
		if (!str)
			chdir(str2);
		else if (chdir(str))
		{
			mini->ret = 1;
			change_dir2(cmd);
		}
		else
			ft_update_env(mini->env);
		free (str2);
		free(str);
	}
}
