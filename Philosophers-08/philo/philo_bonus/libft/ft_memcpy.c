/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:52:00 by dripanuc          #+#    #+#             */
/*   Updated: 2022/01/10 19:52:01 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*ptr;
	const char	*source;

	i = 0;
	ptr = dst;
	source = src;
	while (n--)
	{
		ptr[i] = source[i];
		i++;
	}
	return (dst);
}
