/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:50:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:50:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc2(t_tok *tok, int fd[2])
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (ft_strncmp(line, tok->str, ft_strlen(tok->str)) == 0 \
			&& ft_strlen(line) - 1 == ft_strlen(tok->str))
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

void	ft_heredoc(t_tok *tok, t_mini *mini)
{
	int		fd[2];
	int		reader;

	(void)mini;
	pipe(fd);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		ft_heredoc2(tok, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		wait(NULL);
	}
}

int	ft_pipe_open(t_tok *tok)
{
	while (tok && ft_is_type(tok, END) == 0)
	{
		if (ft_is_type(tok, PIPE))
			return (1);
		tok = tok->next;
	}
	return (0);
}

int	ft_pipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->pid = -1;
		mini->parent = 0;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}	
}
