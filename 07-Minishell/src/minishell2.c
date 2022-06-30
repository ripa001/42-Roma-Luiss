/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell copy 3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 17:47:16 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_global(int signal)
{
	if ((signal == SIGINT || signal == SIGQUIT) && g_sigs.read == 1)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGINT && g_sigs.read == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*ft_new_alloc(char *line)
{
	char	*new;
	int		c;
	int		i;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (ft_is_sep(line, i))
			c++;
		i++;
	}
	new = malloc(sizeof(char) * ((2 * c) + i + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_add_spaces2(char *line, int i, int k)
{
	char	*new;

	new = ft_new_alloc(line);
	if (!new)
		return (NULL);
	while (line[i])
	{
		if (ft_quotes(line, i) == 0 && ft_is_sep(line, i))
		{
			new[k++] = 32;
			new[k++] = line[i++];
			if (ft_quotes(line, i) == 0 && (line[i] == '<' || line[i] == '>' \
				|| line[i] == '|' || line[i] == '&'))
				new[k++] = line[i++];
			new[k++] = 32;
		}
		else
			new[k++] = line[i++];
	}
	new[k] = 0;
	return (new);
}

char	*ft_add_spaces(char *line, t_mini *mini)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	line = ft_expand(line, mini);
	new = ft_add_spaces2(line, i, k);
	free(line);
	return (new);
}

void	ft_init_signals( void )
{
	g_sigs.sigint = 0;
	g_sigs.sigquit = 0;
	g_sigs.pid = 0;
	g_sigs.exit_status = 0;
}
