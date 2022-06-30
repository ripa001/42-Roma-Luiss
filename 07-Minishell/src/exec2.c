/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:28:20 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:28:20 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find(char *str)
{
	if (!ft_strncmp(str, "pwd", ft_strlen(str)) && ft_strlen(str) == 3)
		return (1);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)) && ft_strlen(str) == 2)
		return (1);
	else if (!ft_strncmp(str, "echo", ft_strlen(str)) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "env", ft_strlen(str)) && ft_strlen(str) == 3)
		return (1);
	else if (!ft_strncmp(str, "exit", ft_strlen(str)) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "export", ft_strlen(str)) && ft_strlen(str) == 6)
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)) && ft_strlen(str) == 5)
		return (1);
	return (0);
}

int	ft_exec_error(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	if (fd > 0)
		close (fd);
	return (ret);
}

int	ft_exec_sys2(char *path, char **cmd, t_mini *mini)
{
	int	ret;

	ret = 0;
	g_sigs.pid = fork();
	if (g_sigs.pid == 0)
	{
		if (ft_strchr(path, '/') != NULL)
			execve(path, cmd, mini->env);
		ret = ft_exec_error(path);
		ft_free_tok(mini->start);
		exit(ret);
	}
	else
		waitpid(g_sigs.pid, &ret, 0);
	if (g_sigs.sigint == 1 || g_sigs.sigquit == 1)
		return (g_sigs.exit_status);
	return (ret);
}
