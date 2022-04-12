/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:06 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/13 12:09:44 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		index;

	index = 0;
	dest = (char *)malloc(sizeof(char) * ft_strlen((char *)s1) + 1);
	if (!dest)
		return (0);
	while (((char *)s1)[index] != '\0')
	{
		dest[index] = ((char *)s1)[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
