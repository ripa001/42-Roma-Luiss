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

int	ft_exec_from_system(char **cmd, t_mini *mini)
{
	int		ret;
	char	*path;

	ret = 127;
	path = ft_find_path(mini, cmd[0]);
	if (!path && !cmd[0])
		return (1);
	if (!path)
		ret = ft_exec_sys2(cmd[0], cmd, mini);
	else
		ret = ft_exec_sys2(path, cmd, mini);
	free(path);
	return (ret);
}

void	ft_exec_cmd2(char **cmd, t_mini *mini)
{
	if (ft_find(cmd[0]))
	{
		if (!(ft_strncmp("pwd", cmd[0], 3)))
			ft_get_pwd(mini);
		else if (!(ft_strncmp("cd", cmd[0], 2)))
			ft_change_dir(cmd, mini);
		else if (!(ft_strncmp("echo", cmd[0], 4)))
			ft_echo(cmd, mini);
		else if (!(ft_strncmp("env", cmd[0], 3)))
			ft_env(mini);
		else if (!(ft_strncmp("export", cmd[0], 6)))
			ft_export_command(cmd, mini);
		else if (!(ft_strncmp("unset", cmd[0], 5)))
			ft_unset_var(mini, cmd);
	}
	else
		mini->ret = ft_exec_from_system(cmd, mini);
}

void	ft_exec_cmd(t_mini *mini, t_tok *tok)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = ft_convert_cmd_to_matrix(tok);
	if (cmd && (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) \
		&& ft_strlen(cmd[0]) == 4) && ft_pipe_open(tok) == 0)
		ft_exit_command(mini, cmd);
	else if (cmd)
		ft_exec_cmd2(cmd, mini);
	if (cmd)
		ft_free_matrix(cmd);
	ft_close (mini->pipin);
	ft_close (mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

int	ft_exec_helper(t_tok *prev, t_tok *tok, t_mini *mini)
{
	int		pipe;

	pipe = 0;
	if (ft_is_type(prev, TRUNC))
		ft_redirection(mini, tok, TRUNC);
	else if (ft_is_type(prev, INPUT))
		ft_input(mini, tok);
	else if (ft_is_type(prev, APPEND))
		ft_redirection(mini, tok, APPEND);
	else if (ft_is_type(prev, HEREDOC))
		ft_heredoc(tok, mini);
	else if (ft_is_type(prev, PIPE))
		pipe = ft_pipe(mini);
	return (pipe);
}

void	ft_exec(t_mini *mini, t_tok *tok)
{
	t_tok	*prev;
	t_tok	*next;
	int		pipe;

	prev = ft_prev_separator(tok, 0);
	next = ft_next_separator(tok, 0);
	pipe = ft_exec_helper(prev, tok, mini);
	if (next && ft_is_types(next, "ENO") == 0 && pipe != 1)
		ft_exec(mini, next->next);
	if ((ft_is_type(prev, END) || ft_is_type(prev, PIPE) || !prev) \
		&& pipe != 1 && mini->no_exec == 0)
		ft_exec_cmd(mini, tok);
	else if (ft_is_type(prev, AND) && mini->ret == 0)
		ft_exec_cmd(mini, tok);
	else if (ft_is_type(prev, OR) && mini->ret != 0)
		ft_exec_cmd(mini, tok);
}
