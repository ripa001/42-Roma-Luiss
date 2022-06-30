/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:57:56 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:57:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

void	ft_close_fds(t_mini *mini)
{
	if (mini->fdin > 0)
		close (mini->fdin);
	if (mini->fdout > 0)
		close (mini->fdout);
	if (mini->pipin > 0)
		close (mini->pipin);
	if (mini->pipout > 0)
		close (mini->pipout);
}

void	ft_reset_stds(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	ft_redirection(t_mini *mini, t_tok *tok, int type)
{
	if (mini->fdout > 0)
		close(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(tok->str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		mini->fdout = open(tok->str, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (mini->fdout == -1)
	{
		ft_putstr_fd(tok->str, STDERR);
		ft_putendl_fd("No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	ft_input(t_mini *mini, t_tok *tok)
{
	if (mini->fdin > 0)
		close(mini->fdin);
	mini->fdin = open(tok->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd(tok->str, STDERR);
		ft_putendl_fd("No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}
