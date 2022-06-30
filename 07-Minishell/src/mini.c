/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:17:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tok	*ft_next_run(t_tok *tok, int i)
{
	if (tok && i)
		tok = tok->next;
	while (tok && tok->type != CMD)
	{
		tok = tok->next;
		if (tok && tok->type == CMD && tok->prev == NULL)
			;
		else if (tok && tok->type == CMD && tok->prev->type < AND)
			tok = tok->next;
	}
	return (tok);
}

void	ft_mini(t_mini *mini)
{
	t_tok	*tok;
	int		status;

	ft_convert_par(mini->start);
	tok = ft_next_run(mini->start, 0);
	if (ft_is_types(mini->start, "THAI"))
		tok = mini->start->next;
	while (mini->exit == 0 && tok)
	{
		ft_mini_helper(mini);
		ft_exec(mini, tok);
		ft_reset_stds(mini);
		ft_close_fds(mini);
		ft_reset_fds(mini);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
			mini->ret = status;
		if (mini->parent == 0)
		{
			ft_free_tok(mini->start);
			exit(mini->ret);
		}
		tok = ft_next_run(tok, 1);
	}
}

void	ft_subshell(t_mini *mini, char *av)
{
	ft_sub(mini, av);
	if (mini->start != NULL && ft_check_cmd(mini, mini->start))
		ft_mini(mini);
	ft_free_tok(mini->start);
}

void	ft_sub(t_mini *mini, char *str)
{
	t_tok	*tok;
	char	*line;

	mini->lvl = 0;
	signal(SIGINT, ft_signal_handler_global);
	signal(SIGQUIT, ft_signal_handler_global);
	line = ft_strtrim(str, "\"");
	if (g_sigs.sigint == 1)
		mini->ret = g_sigs.exit_status;
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		line = ft_add_spaces(line, mini);
		mini->start = ft_get_tok(line, mini);
		ft_arrange_args(mini);
		tok = mini->start;
		while (tok)
		{
			if (ft_is_type(tok, ARG))
				ft_arg_type(tok, 0, mini, 0);
			tok = tok->next;
		}
	}
	free(line);
}

char	*ft_set_prompt(char **env)
{
	char	*tmp;
	char	*user;

	user = ft_get_env(env, "USER");
	tmp = ft_strdup(user);
	if (!tmp)
		tmp = ft_strdup("guest");
	tmp = ft_strjoin_free(tmp, ft_strdup("@minishell$ "));
	free(user);
	return (tmp);
}
