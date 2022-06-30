/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:17:10 by dripanuc          #+#    #+#             */
/*   Updated: 2022/06/29 19:50:10 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_rev_split(char **matrix)
{
	int		i;
	char	*ret;
	int		j;

	ret = ft_strdup("");
	i = 0;
	j = ft_strlen_matrix(matrix) - 1;
	while (matrix[i])
	{
		ret = ft_strjoin_get(ret, matrix[i]);
		if (i != j)
			ret = ft_strjoin_free(ret, ft_strdup(" "));
		i++;
	}
	return (ret);
}

void	ft_print_tok(t_tok *start)
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

char	*ft_findwild_multi(char *str, char *dir)
{
	char			**files;
	int				j;
	char			*ret;

	files = ft_findwild_multi2(str, dir);
	if (files[0] == 0)
	{
		files[0] = ft_strdup(str);
		files[1] = 0;
	}
	j = ft_strlen_matrix(files);
	files[j] = 0;
	ret = ft_rev_split(files);
	free(str);
	ft_free_matrix(files);
	return (ret);
}

int	ft_strcmp_end(char *name, char *end)
{
	int	name_len;
	int	ext_len;

	name_len = ft_strlen(name);
	ext_len = ft_strlen(end);
	if (name_len <= ext_len)
		return (0);
	name += name_len - ext_len;
	while (*name)
	{
		if (*name != *end)
			return (0);
		name++;
		end++;
	}
	return (1);
}

char	**ft_find_multi(char **files, char *find, char *last)
{
	char	**new;
	int		i;
	int		k;

	if (find[0] == 0 || files[1] == 0)
		return (files);
	i = 0;
	k = 0;
	if (!last)
		last = "";
	new = malloc(sizeof(char *) * ft_strlen_matrix(files) + 1);
	new[0] = 0;
	while (files[i])
	{
		if (ft_strnstr(ft_strnstr(files[i], last, ft_strlen(files[i])) + \
			ft_strlen(last), find, ft_strlen(files[i])) != NULL)
		{
			new[k] = ft_strdup(files[i]);
			k++;
		}
		i++;
	}
	new[k] = 0;
	ft_free_matrix(files);
	return (new);
}
