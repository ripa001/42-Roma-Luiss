/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:49 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/19 13:42:53 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0' && index < n)
	{
		if (((unsigned char *)s1)[index] > ((unsigned char *)s2)[index])
			return (1);
		else if (((unsigned char *)s1)[index] < ((unsigned char *)s2)[index])
			return (-1);
		index++;
	}
	if (((unsigned char *)s2)[index] != '\0' && index < n)
		return (-1);
	return (0);
}
