/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:45:18 by mpatrini          #+#    #+#             */
/*   Updated: 2022/06/29 20:21:15 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char *set)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (c == set[k])
			return (1);
		k++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		c;
	int		k;

	c = 0;
	while (check_set(s1[c], (char *)set))
		c++;
	k = ft_strlen(s1);
	while (check_set(s1[k - 1], (char *)set) && k > c)
		k--;
	return (ft_substr((char *)s1, c, k - c));
}
