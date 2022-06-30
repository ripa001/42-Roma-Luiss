/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 03:32:37 by mpatrini          #+#    #+#             */
/*   Updated: 2022/01/13 03:19:19 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strleng2(char const *str, int count, int i)
{
	int		k;
	char	*st;

	st = (char *)malloc(count + 1);
	if (!st)
		return (NULL);
	k = 0;
	while ((i - count) < i)
	{
		st[k] = str[i - count];
		k++;
		count--;
	}
	st[k] = 0;
	return (st);
}

static int	ft_strleng(char const *str, char charset, char **mat)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (str[i])
	{
		count = 0;
		while (str[i] == charset)
			i++;
		while (str[i] != charset && str[i])
		{
			i++;
			count++;
		}
		if (count > 0)
		{
			mat[j] = ft_strleng2(str, count, i);
			j++;
		}
	}
	mat[j] = 0;
	return (1);
}

static	int	ft_strcount(char const *str, char charset)
{
	size_t	i;
	int		count;
	size_t	h;

	i = 0;
	count = 0;
	while (str[i])
	{
		h = 0;
		while (str[i] == charset)
			i++;
		while (str[i] != charset && str[i])
		{
			i++;
			h++;
		}
		count++;
	}
	if (h == 0)
		count -= 1;
	return (count + 1);
}

static char	**ft_split2(char const *str)
{
	char	**matrix;

	matrix = (char **)malloc(sizeof(char *) * 2);
	if (!matrix)
		return (NULL);
	matrix[0] = ft_strdup(str);
	matrix[1] = 0;
	return (matrix);
}

char	**ft_split(char const *str, char charset)
{
	int		count;
	char	**matrix;

	if (!str || !*str)
	{
		matrix = malloc(sizeof(char *) * 1);
		if (!matrix)
			return (NULL);
		*matrix = (void *)0;
		return (matrix);
	}
	if (ft_strchr(str, charset) == NULL)
	{
		matrix = ft_split2(str);
		if (!matrix)
			return (NULL);
		return (matrix);
	}
	count = ft_strcount(str, charset);
	matrix = (char **)malloc(sizeof(char *) * (count));
	if (!matrix)
		return (NULL);
	if (ft_strleng(str, charset, matrix) == 1)
		return (matrix);
	return (NULL);
}
