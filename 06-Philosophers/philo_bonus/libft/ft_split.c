/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 00:45:17 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/14 19:51:18 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_num_el(char const *s, char c)
{
	char	*p;
	int		i;
	int		nbr;

	i = ft_strlen(s);
	nbr = 0;
	p = (char *)s;
	while (*p)
	{
		while (*p == c)
			p++;
		if (!*p)
			break ;
		nbr++;
		while (*p != c && *p)
			p++;
	}
	return (nbr);
}

char	**memall(char *s, char c, int nbr, char **new)
{
	int		counter;
	char	*ptr;
	int		i;

	counter = 0;
	i = 0;
	ptr = (char *)s;
	while (*ptr == c)
		ptr++;
	while (counter < nbr)
	{
		i = 0;
		while (*ptr == c)
			ptr++;
		while (*ptr != c && *ptr)
		{
			i++;
			ptr++;
		}
		new[counter] = (char *)malloc(sizeof(char) * (i + 1));
		new[counter][i] = 0;
		counter++;
	}
	new[counter] = 0;
	return (new);
}

char	**ft_split(char const *s, char c)
{
	int		nbr;
	char	**new;
	int		i;
	int		counter;

	nbr = get_num_el(s, c);
	new = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!new)
		return (0);
	new = memall((char *)s, c, nbr, new);
	counter = 0;
	while (*s)
	{
		i = 0;
		while (*s == c)
			s++;
		while (*s != c && *s)
		{
			new[counter][i] = *s;
			i++;
			s++;
		}
		counter++;
	}
	return (new);
}
