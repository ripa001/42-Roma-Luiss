/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:37:19 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:37:19 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tok(t_tok *start)
{
	while (start && start->next)
	{
		if (start->str)
			free(start->str);
		start = start->next;
		free(start->prev);
	}
	if (start)
	{
		if (start->str)
			free(start->str);
		free(start);
	}
}

t_tok	*ft_next_tok(char *line, int *i)
{
	t_tok	*tok;
	int		k;
	char	c;

	k = 0;
	c = 32;
	tok = malloc(sizeof(t_tok));
	tok->str = malloc(sizeof(char) * ft_strlen(line));
	if (!tok || !tok->str)
		return (NULL);
	while (line[*i] && (line[*i] != 32 || c != 32))
	{
		if (c == 32 && (line[*i] == 34 || line[*i] == 39))
			c = line[(*i)++];
		else if (c != 32 && line[*i] == c && (*i)++)
			c = 32;
		else if (line[*i] == '\\' && (*i)++)
			tok->str[k++] = line[(*i)++];
		else
			tok->str[k++] = line[(*i)++];
	}
	tok->str[k] = 0;
	return (tok);
}

void	ft_arg_type2(t_tok *tok, int sep, t_mini *mini)
{
	if (!ft_strncmp(tok->str, "&&", ft_strlen(tok->str)) && sep == 0)
		tok->type = AND;
	else if (!ft_strncmp(tok->str, ";", ft_strlen(tok->str)) && sep == 0)
		tok->type = END;
	else if (!ft_strncmp(tok->str, ")", ft_strlen(tok->str)) && sep == 0)
	{
		tok->type = PARC;
		mini->lvl--;
	}
	else if (!ft_strncmp(tok->str, "(", ft_strlen(tok->str)) && sep == 0)
	{
		tok->type = PARO;
		mini->lvl++;
	}
	else if (tok->prev == NULL || tok->prev->type >= TRUNC)
		tok->type = CMD;
	else
		tok->type = ARG;
}

void	ft_arg_type(t_tok *tok, int sep, t_mini *mini, int i)
{
	if (!ft_strncmp(tok->str, "", ft_strlen(tok->str)))
		tok->type = EMPTY;
	else if (!ft_strncmp(tok->str, ">", ft_strlen(tok->str)) && sep == 0)
		tok->type = TRUNC;
	else if (!ft_strncmp(tok->str, ">>", ft_strlen(tok->str)) && sep == 0)
		tok->type = APPEND;
	else if (!ft_strncmp(tok->str, "<", ft_strlen(tok->str)) && sep == 0)
		tok->type = INPUT;
	else if (!ft_strncmp(tok->str, "<<", ft_strlen(tok->str)) && sep == 0)
		tok->type = HEREDOC;
	else if (!ft_strncmp(tok->str, "|", ft_strlen(tok->str)) && sep == 0)
		tok->type = PIPE;
	else if (!ft_strncmp(tok->str, "||", ft_strlen(tok->str)) && sep == 0)
		tok->type = OR;
	else
		ft_arg_type2(tok, sep, mini);
	if (mini->lvl < 0)
		mini->lvl = -9999;
	if (i == 1)
		tok->lvl = mini->lvl;
}

t_tok	*ft_get_tok(char *line, t_mini *mini)
{
	t_tok	*prev;
	t_tok	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	i = ft_get_tok_help(line, i);
	while (line[i])
	{
		sep = ft_ignore_sep(line, i);
		next = ft_next_tok(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		ft_arg_type(next, sep, mini, 1);
		i = ft_get_tok_help(line, i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
