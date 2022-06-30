/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:45:32 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:45:32 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '<')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '&')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ')')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '(')
		return (1);
	return (0);
}

char	*ft_line(t_mini *mini)
{
	char	*prompt;
	char	*line;

	prompt = ft_set_prompt(mini->env);
	g_sigs.read = 1;
	line = readline(prompt);
	g_sigs.read = 0;
	if (line == NULL)
		exit (mini->ret);
	line = check_readline(line);
	free(prompt);
	return (line);
}

void	ft_get_cmd(t_mini *mini)
{
	char	*line;
	t_tok	*tok;

	mini->lvl = 0;
	line = ft_line(mini);
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
	else
		mini->start = NULL;
	free(line);
}
