/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:00:46 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/13 00:41:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if ((int)len == -1)
		len = ft_strlen(haystack);
	while (haystack[i] != 0 && i < (int)len)
	{
		if (haystack[i] == needle[j])
			j++;
		else if (needle[j] == 0)
			return ((char *)&haystack[i - ft_strlen(needle)]);
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	if (j == ft_strlen(needle))
		return ((char *)&haystack[i - ft_strlen(needle)]);
	return (0);
}
