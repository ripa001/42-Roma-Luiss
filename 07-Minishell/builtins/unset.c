/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:08 by ebassi            #+#    #+#             */
/*   Updated: 2022/06/28 17:03:13 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_unset_var2(char **env, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = ft_strlen_matrix(env);
	tmp = (char **)malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0 \
			&& env[i][ft_strlen(str)] == '=')
			;
		else
		{
			tmp[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = 0;
	ft_free_matrix(env);
	return (tmp);
}

void	ft_unset_var(t_mini *mini, char **cmd)
{
	int		k;
	char	*e;

	k = 0;
	while (cmd[++k])
	{
		e = ft_get_env(mini->env, cmd[k]);
		if (e != NULL)
		{
			mini->env = ft_unset_var2(mini->env, cmd[k]);
		}
		free(e);
	}
	mini->ret = 0;
}
