/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:03 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/18 12:27:03 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*res;
	char	ch;

	ch = c;
	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (i < len + 1)
	{
		if (s[i] == ch)
		{
			res = (char *)&s[i];
			return (res);
		}
		i++;
	}
	return (NULL);
}
