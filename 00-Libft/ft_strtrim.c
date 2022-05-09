/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 00:39:33 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/23 23:53:38 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int check_set(char c, char *set)
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
