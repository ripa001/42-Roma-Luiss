/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:08:27 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 18:08:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_types2(t_tok *tok, char *types)
{
	if (ft_strchr(types, 'N') && ft_is_type(tok, AND))
		return (1);
	else if (ft_strchr(types, 'O') && ft_is_type(tok, OR))
		return (1);
	else if (ft_strchr(types, 'P') && ft_is_type(tok, PIPE))
		return (1);
	else if (ft_strchr(types, 'Z') && ft_is_type(tok, PARO))
		return (1);
	else if (ft_strchr(types, 'X') && ft_is_type(tok, PARC))
		return (1);
	else if (ft_strchr(types, 'E') && ft_is_type(tok, END))
		return (1);
	else
		return (0);
}

int	ft_is_types(t_tok *tok, char *types)
{
	int	i;

	if (ft_strchr(types, 32) && ft_is_type(tok, EMPTY))
		return (1);
	else if (ft_strchr(types, 'C') && ft_is_type(tok, CMD))
		return (1);
	else if (ft_strchr(types, 'R') && ft_is_type(tok, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && ft_is_type(tok, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && ft_is_type(tok, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && ft_is_type(tok, INPUT))
		return (1);
	else if (ft_strchr(types, 'H') && ft_is_type(tok, HEREDOC))
		return (1);
	else
		i = ft_is_types2(tok, types);
	return (i);
}

int	ft_check_cmd(t_mini *mini, t_tok *tok)
{
	while (tok)
	{
		if ((ft_is_types(tok, "THAI") && (!tok->next \
			|| ft_is_types(tok->next, "THAINOPEZX"))) || \
			(ft_is_types(tok, "PENO") && (!tok->next || !tok->prev \
			|| ft_is_types(tok->next, "THAINOPE") \
			|| ft_is_types(tok->prev, "THAINOPE"))) \
			|| mini->lvl != 0 || (ft_is_types(tok, "Z") && \
			ft_is_types(tok->next, "X")) \
			|| (ft_is_types(tok, "X") && ft_is_types(tok->next, "Z")))
		{
			ft_putendl_fd("Syntax error", STDERR);
			mini->ret = 258;
			return (0);
		}
		tok = tok->next;
	}
	return (1);
}
