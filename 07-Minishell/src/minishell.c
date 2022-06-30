/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 17:49:28 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_path(t_mini *mini, char *cmd)
{
	char	*path;
	char	*env_p;
	char	**spath;
	int		i;

	path = NULL;
	env_p = ft_get_env(mini->env, "PATH");
	if (env_p == NULL)
		return (NULL);
	spath = ft_split(env_p, ':');
	if (!spath[0])
	{
		ft_free_matrix(spath);
		return (NULL);
	}
	i = -1;
	while (spath[++i] && path == NULL)
		path = ft_check_dir(spath[i], cmd);
	ft_free_matrix(spath);
	free(env_p);
	return (path);
}

char	*ft_check_dir(char *dir, char *cmd)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	folder = opendir(dir);
	if (!folder)
		return (NULL);
	entry = readdir(folder);
	while (entry && path == NULL)
	{
		if (!ft_strncmp(cmd, entry->d_name, ft_strlen(cmd)) \
			&& !ft_strncmp(entry->d_name, cmd, ft_strlen(entry->d_name)))
				path = ft_join_path(dir, entry->d_name);
		entry = readdir(folder);
	}
	closedir(folder);
	return (path);
}

void	ft_main2(t_mini *mini)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->exit = 0;
	mini->ret = 0;
	mini->no_exec = 0;
}

void	ft_mini_helper(t_mini *mini)
{
	mini->charge = 1;
	mini->parent = 1;
	mini->last = 1;
}

char	*ft_join_path(char *str, char *str2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(str, "/");
	path = ft_strjoin(tmp, str2);
	free(tmp);
	return (path);
}
