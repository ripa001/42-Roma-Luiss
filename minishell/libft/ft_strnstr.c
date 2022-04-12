/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:56 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/19 16:08:20 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		a;

	a = 0;
	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i++] == needle[j] && needle[j] != '\0')
			j++;
		else if (haystack[i] != needle[j])
		{
			j = 0;
			a++;
			i = a;
		}
		if (j == (int)ft_strlen(needle))
			return (((char *)haystack) + i - j);
	}
	return (0);
}
