/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:04:52 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/13 11:59:31 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ret(char *fin_dest, char *fin_src, int i, int len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*fin_src;
	char	*fin_dest;
	int		i;

	if (dst == src)
		return (dst);
	fin_src = (char *) src;
	fin_dest = (char *) dst;
	i = 0;
	ft_ret(fin_dest, fin_src, i, len);
	return (dst);
}

static char	*ft_ret(char *fin_dest, char *fin_src, int i, int len)
{
	if (fin_dest > fin_src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			fin_dest[i] = fin_src[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			fin_dest[i] = fin_src[i];
			i++;
		}
	}
	return (fin_dest);
}
