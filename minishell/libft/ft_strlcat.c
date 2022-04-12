/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:30 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/12 15:41:36 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	index_dest;
	unsigned int	len_dest;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	index_dest = 0;
	len_dest = ft_strlen(dst);
	while (src[index_dest] != '\0' && len_dest + 1 < (unsigned int)dstsize)
	{
		dst[len_dest] = src[index_dest];
		index_dest++;
		len_dest++;
	}
	dst[len_dest] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[index_dest]));
}
