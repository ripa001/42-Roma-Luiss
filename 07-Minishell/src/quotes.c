/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:18:52 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:18:52 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_quotes(char *line, int in)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i] && i != in)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (quotes == 0 && line[i] == 34)
			quotes = 1;
		else if (quotes == 0 && line[i] == 39)
			quotes = 2;
		else if (quotes == 1 && line[i] == 34)
			quotes = 0;
		else if (quotes == 2 && line[i] == 39)
			quotes = 0;
		i++;
	}
	return (quotes);
}

int	ft_check_quotes(t_mini *mini, char **line)
{
	if (ft_quotes(*line, 2147483647))
	{
		ft_putendl_fd("Syntax error: open quotes", STDERR);
		mini->ret = 2;
		mini->start = NULL;
		free(*line);
		return (1);
	}
	return (0);
}

int	qquotes(char c, int q)
{
	if (c == '"' && !q)
		q = 2;
	else if (c == '"' && q == 2)
		q = 0;
	else if (c == '\'' && !q)
		q = 1;
	else if (c == '\'' && q == 1)
		q = 0;
	return (q);
}

int	quote_in_quotes(char *line)
{
	int	i;
	int	open_m;
	int	open_s;

	i = -1;
	open_s = 0;
	open_m = 0;
	while (line[++i])
	{
		if (line[i] == '"' && !open_s && !open_m)
			open_m = 1;
		else if (line[i] == '"' && open_m)
			open_m = 0;
		else if (line[i] == '\'' && !open_s && !open_m)
			open_s = 1;
		else if (line[i] == '\'' && open_s)
			open_s = 0;
	}
	if (!open_s && !open_m)
		return (0);
	else if (open_s && !open_m)
		return (1);
	else if (!open_s && open_m)
		return (2);
	return (0);
}

char	*check_readline(char *line)
{
	char	*tmp;
	int		flag;

	tmp = 0;
	flag = quote_in_quotes(line);
	while (flag)
	{
		if (flag == 1)
			tmp = readline("quote: ");
		else
			tmp = readline("dquote: ");
		line = ft_strjoin_get(line, "\n");
		line = ft_strjoin_free(line, tmp);
		flag = quote_in_quotes(line);
	}
	return (line);
}
