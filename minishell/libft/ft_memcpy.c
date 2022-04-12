/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:04:43 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/13 11:55:17 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*fin_src;
	char	*fin_dest;
	size_t	i;

	if ((dst == src) || n == 0)
		return (dst);
	if (!src && !dst)
		return (NULL);
	fin_src = (char *) src;
	fin_dest = (char *) dst;
	i = 0;
	while (i < n)
	{
		fin_dest[i] = fin_src[i];
		i++;
	}
	return (dst);
}
