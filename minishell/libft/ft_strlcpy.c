/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:38 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/12 15:51:50 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_dest(const char *src);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	index_src;
	unsigned int	index_dest;

	index_src = 0;
	index_dest = 0;
	if ((int)dstsize != 0)
	{
		while (src[index_src] != '\0'
			&& index_src < ((unsigned int)dstsize - 1))
		{
			dst[index_dest] = src[index_src];
			index_src++;
			index_dest++;
		}
		dst[index_dest] = '\0';
	}
	return (len_dest(src));
}

static size_t	len_dest(const char *src)
{
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	return (len);
}
