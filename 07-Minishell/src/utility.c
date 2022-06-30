/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:15:45 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:15:45 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	ft_is_type(t_tok *tok, int type)
{
	if (tok && tok->type == type)
		return (1);
	return (0);
}

void	ft_print_start(t_tok *start)
{
	while (start)
	{
		ft_putstr_fd(start->str, STDERR);
		write(1, " - T: ", 3);
		ft_putnbr_fd(start->type, STDERR);
		write(1, " - L: ", 3);
		ft_putnbr_fd(start->lvl, STDERR);
		write(1, "\n", 1);
		start = start->next;
	}
}

int	ft_is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;&()", line[i]))
		return (0);
	else if (ft_strchr("<>|;&()", line[i]) && ft_quotes(line, i) == 0)
		return (1);
	return (0);
}
