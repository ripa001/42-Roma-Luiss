/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:16:00 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/28 17:16:00 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_init_env(char **env, int k)
{
	char	**tmp;
	int		i;
	int		lvl;
	char	*sh;

	sh = ft_get_env(env, "SHLVL");
	if (k == 1)
		lvl = ft_atoi(sh) + 1;
	else
		lvl = ft_atoi(sh);
	i = ft_strlen_matrix(env);
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0 && env[i][5] == '=')
			tmp[i] = ft_strjoin_free(ft_strdup("SHLVL="), ft_itoa(lvl));
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = 0;
	free(sh);
	return (tmp);
}

char	*ft_get_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0 \
			&& (env[i][ft_strlen(str)] == '=' || \
			ft_strlen(str) == ft_strlen(env[i])))
			return (ft_substr(env[i], ft_strlen(str) + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}
