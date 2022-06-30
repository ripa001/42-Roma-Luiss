/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:14:27 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:14:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tok	*ft_convert_par2(t_tok *start, int *lvl)
{
	t_tok	*head;

	*lvl = start->lvl;
	free(start->str);
	start->str = ft_strdup("./minishell");
	start->type = CMD;
	head = start->next;
	head->str = ft_strjoin_free(ft_strdup("\""), head->str);
	head->type = ARG;
	head->str = ft_strjoin_free(head->str, ft_strdup(" "));
	return (head);
}

t_tok	*ft_convert_par3(t_tok *start, t_tok *head)
{
	t_tok	*prev;
	t_tok	*next;

	if (start->next == NULL)
	{
		head->next = NULL;
		free(start->str);
		free(start);
		start = NULL;
	}
	else
	{
		prev = head;
		next = start->next;
		prev->next = next;
		next->prev = prev;
		free(start->str);
		free(start);
		start = prev;
	}
	return (start);
}

void	ft_convert_par(t_tok *start)
{
	int		lvl;
	t_tok	*head;
	t_tok	*next;

	while (start)
	{
		if (ft_is_type(start, PARO))
		{
			head = ft_convert_par2(start, &lvl);
			start = head->next;
			while (start->lvl >= lvl)
			{
				head->str = ft_strjoin_free(head->str, start->str);
				if (start->next->lvl >= lvl)
					head->str = ft_strjoin_get(head->str, " ");
				next = start->next;
				free(start);
				start = next;
			}
			head->str = ft_strjoin_free(head->str, ft_strdup("\""));
			start = ft_convert_par3(start, head);
		}
		if (start)
			start = start->next;
	}
}
