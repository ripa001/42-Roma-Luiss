/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:50:24 by mpatrini          #+#    #+#             */
/*   Updated: 2022/05/17 03:15:22 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	a;

	i = 0;
	j = 0;
	a = 0;
	if (*n == 0 || h == NULL)
		return ((char *)h);
	while (h[i] && i < len)
	{
		while (h[i] == n[j] && h[i] && i < len && n[j])
		{
			i++;
			j++;
			if (n[j] == '\0')
				return ((char *)(h + (i - j)));
		}
		j = 0;
		a++;
		i = a;
	}
	return (NULL);
}
