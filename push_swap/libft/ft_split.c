/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:32:07 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/18 16:29:48 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rowcount(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count += 1;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_rowlen(char const *str, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static int	ft_putstr(char *matrix, char const *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		matrix[j] = str[i];
		i++;
		j++;
	}
	matrix[j] = '\0';
	return (i);
}

char	**ft_split_push(char const *s, char c, int *argc)
{
	char	**matrix;
	int		count;
	int		len;
	int		row;

	count = ft_rowcount(s, c) + 1;
	matrix = (char **) malloc (sizeof(char *) * (count + 2));
	matrix[count + 1] = NULL;
	len = 0;
	row = 0;
	matrix[row++] = "nome";
	while (row < count)
	{
		len = ft_rowlen(s, c);
		matrix[row] = (char *) malloc (sizeof(char) * (len + 1));
		s += ft_putstr(matrix[row], s, c);
		row++;
	}
	*argc = count;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		count;
	int		len;
	int		row;

	count = ft_rowcount(s, c) + 1;
	matrix = (char **) malloc (sizeof(char *) * (count + 1));
	matrix[count] = NULL;
	len = 0;
	row = -1;
	while (++row < count)
	{
		len = ft_rowlen(s, c);
		matrix[row] = (char *) malloc (sizeof(char) * (len + 1));
		s += ft_putstr(matrix[row], s, c);
	}
	return (matrix);
}