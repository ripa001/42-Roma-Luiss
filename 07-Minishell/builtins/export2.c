/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:01:00 by ebassi            #+#    #+#             */
/*   Updated: 2022/06/30 16:21:23 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_copy_env(char **env)
{
	char	**tmp;
	int		i;

	i = ft_strlen_matrix(env);
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = 0;
	tmp[i + 1] = 0;
	return (tmp);
}

char	*ft_replace_env(char *env, char *name, char *value)
{
	char	*new;
	char	*tmp;

	tmp = ft_strchr(value, '=');
	free(env);
	new = ft_strjoin(name, "=");
	if (tmp == NULL)
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(tmp + 1);
	env = ft_strjoin_free(new, tmp);
	return (env);
}

void	ft_print_export(char **env2)
{
	int	i;

	i = 0;
	while (env2[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		if (ft_strchr(env2[i], '='))
			write(STDOUT, env2[i], ft_strchr(env2[i], '=') - env2[i]);
		else
			write(STDOUT, env2[i], ft_strlen(env2[i]));
		ft_putchar_fd('=', STDOUT);
		ft_putchar_fd(34, STDOUT);
		if (ft_strchr(env2[i], '='))
			ft_putstr_fd(ft_strchr(env2[i], '=') + 1, STDOUT);
		ft_putendl_fd("\"", STDOUT);
		i++;
	}
}

void	ft_export_alone(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**env2;

	i = 0;
	env2 = ft_init_env(env, 0);
	while (env2[i])
	{
		j = i +1;
		while (env2[j])
		{
			if (ft_strncmp(env2[i], env2[j], ft_strlen(env2[i])) > 0)
			{
				tmp = env2[i];
				env2[i] = env2[j];
				env2[j] = tmp;
			}
			j++;
		}
		i++;
	}
	ft_print_export(env2);
	ft_free_matrix(env2);
}

char	**ft_export_command3(char **cmd, t_mini *mini, int flag, int k)
{
	char	**tmp;
	char	*temp;
	int		i;

	i = ft_strlen_matrix(mini->env);
	tmp = ft_copy_env(mini->env);
	ft_free_matrix(mini->env);
	if (!flag)
		tmp[i] = ft_strdup(cmd[k]);
	else
	{
		temp = ft_substr(cmd[k], 0, ft_strchr_int(cmd[k], '+'));
		tmp[i] = ft_substr(cmd[k], ft_strchr_int(cmd[k], '+') + 1, ft_strlen(cmd[k]));
		tmp[i] = ft_strjoin_free(temp, tmp[i]);
	}
	return (tmp);
}
