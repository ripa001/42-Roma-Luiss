/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:28:13 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/29 20:04:54 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_expand(char *line, t_mini *mini)
{
	char	*ret;
	char	*ret2;

	ret = expand_envars(line, mini);
	ret2 = ft_expand_wild(ret);
	return (ret2);
}

int	ft_convert_cmd_to_matrix_help(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok && tok->type < TRUNC)
	{
		tok = tok->next;
		i++;
	}
	return (i);
}

char	**ft_convert_cmd_to_matrix(t_tok *start)
{
	t_tok	*tok;
	char	**ret;
	int		i;

	if (!start)
		return (NULL);
	tok = start->next;
	i = ft_convert_cmd_to_matrix_help(tok);
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	tok = start->next;
	ret[0] = ft_strdup(start->str);
	i = 1;
	while (tok && tok->type < TRUNC)
	{
		ret[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	ret[i] = 0;
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	ft_main2(&mini);
	ft_reset_fds(&mini);
	signal(SIGQUIT, ft_signal_handler_global);
	signal(SIGINT, ft_signal_handler_global);
	mini.env = ft_init_env(env, 1);
	if (ac == 2)
		ft_subshell(&mini, av[1]);
	else if (ac == 1)
	{
		while (mini.exit == 0)
		{
			ft_init_signals();
			ft_get_cmd(&mini);
			if (mini.start != NULL && ft_check_cmd(&mini, mini.start))
				ft_mini(&mini);
			ft_free_tok(mini.start);
		}
	}
	ft_free_matrix(mini.env);
	return (mini.ret);
}
