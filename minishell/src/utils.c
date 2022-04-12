/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:44:40 by ebassi            #+#    #+#             */
/*   Updated: 2022/04/13 00:16:02 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT || sig == SIGTSTP)
		write(STDOUT, "\n", 1);
}

char	*set_prompt()
{
	char	*str;
	char	*tmp;

	str = 0;
	tmp = 0;
	str = ft_strdup(GREEN);
	tmp = ft_strdup("minishell$ ");
	str = ft_strjoin(str, tmp);
	free(tmp);
	tmp = ft_strdup(RESET);
	str = ft_strjoin(str, tmp);
	return (str);
	// write(1, GREEN, ft_strlen(GREEN));
	// write(1, "minishell$ ", ft_strlen("minishell$ "));
	// write(1, GREEN, ft_strlen(GREEN));
}

void	get_next_lst(t_tok *input_ln)
{
	t_tok	*next_lst;

	next_lst = malloc(sizeof(t_tok));
	next_lst->id = input_ln->id + 1;
	input_ln->next = next_lst;
}


void	init(t_tok *x)
{
	x->type = 0;
	x->data = NULL;
	x->exit = 0;
	x->next = NULL;
}

void print_list(t_tok *x)
{
	while (x)
	{
		printf("TYPE:%d DATA:%s ID: %d\n", x->type, x->data, x->id);
		x = x->next;
	}
}