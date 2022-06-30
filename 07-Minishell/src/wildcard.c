/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 20:20:51 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_check_last2(char **files, char *str, int i, int j)
{
	char	**new;

	new = malloc(sizeof(char *) * ft_strlen_matrix(files) + 1);
	while (files[i])
	{
		if (ft_strchr(str, '*') != NULL)
		{
			if (ft_strcmp_end(files[i], ft_strrchr(str, '*') + 1))
			{
				new[j] = ft_strdup(files[i]);
				j++;
			}
		}
		else
		{
			if (ft_strcmp_end(files[i], str))
			{
				new[j] = ft_strdup(files[i]);
				j++;
			}
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

char	**ft_check_last(char **files, char *str, int i, int j)
{
	char	**new;

	if (str[ft_strlen(str) - 1] == '*' || !str[0])
		return (files);
	else if (files[0] == 0)
	{
		new = ft_calloc(3, sizeof(char *));
		return (new);
	}
	else
		new = ft_check_last2(files, str, i, j);
	ft_free_matrix(files);
	return (new);
}

char	**ft_findwild_multi2_help(char *str, char **files, char *find, int i)
{
	int		k;
	char	*last;

	k = -1;
	last = NULL;
	while (1)
	{
		if (str[i] == '*' || str[i] == 0)
		{
			find[++k] = 0;
			files = ft_find_multi(files, find, last);
			if (find)
				last = ft_strdup(find);
			k = -1;
		}
		else
			find[++k] = str[i];
		if (str[i] == 0)
			break ;
		i++;
	}
	if (last)
		free(last);
	return (files);
}

char	**ft_findwild_multi2(char *str, char *dir)
{
	char			**files;
	char			*find;
	char			*last;

	files = ft_findwild_multi3(str, dir);
	str = ft_substr(str, ft_strchr(str, '*') - str + 1, ft_strlen(str));
	find = malloc(ft_strlen(str) + 1);
	last = NULL;
	files = ft_findwild_multi2_help(str, files, find, 0);
	free(find);
	files = ft_check_last(files, str, 0, 0);
	free(str);
	return (files);
}
