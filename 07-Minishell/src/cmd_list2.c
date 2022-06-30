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

t_tok	*ft_prev_separator(t_tok *tok, int i)
{
	if (tok && i)
		tok = tok->prev;
	while (tok && tok->type < TRUNC)
		tok = tok->prev;
	return (tok);
}

t_tok	*ft_next_separator(t_tok *tok, int i)
{
	if (tok && i)
		tok = tok->next;
	while (tok && tok->type < TRUNC)
		tok = tok->next;
	return (tok);
}

int	ft_is_valid_arg(t_tok *tok)
{
	t_tok	*prev;

	if (!tok || ft_is_type(tok, ARG) || ft_is_type(tok, CMD))
	{
		prev = ft_prev_separator(tok, 0);
		if (!prev || ft_is_type(prev, PIPE) || ft_is_type(prev, END) \
			|| ft_is_type(prev, AND) || ft_is_type(prev, OR))
			return (1);
		return (0);
	}
	return (0);
}

void	ft_arrange_args2(t_tok *tok, t_mini *mini, t_tok *prev)
{
	while (ft_is_valid_arg(prev) == 0)
		prev = prev->prev;
	tok->prev->next = tok->next;
	if (tok->next)
		tok->next->prev = tok->prev;
	tok->prev = prev;
	if (!prev)
		tok->next = mini->start;
	if (!prev)
		prev = tok;
	prev->next->prev = tok;
	if (!mini->start->prev)
		prev->next = tok;
	if (mini->start->prev)
		mini->start = mini->start->prev;
}

void	ft_arrange_args(t_mini *mini)
{
	t_tok	*tok;
	t_tok	*prev;

	tok = mini->start;
	while (tok)
	{
		prev = ft_prev_separator(tok, 0);
		if (ft_is_type(tok, ARG) && ft_is_types(prev, "TAIH"))
			ft_arrange_args2(tok, mini, prev);
		tok = tok->next;
	}
}
