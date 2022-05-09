/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:24:02 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/20 01:04:32 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				j;
	unsigned char	*str;
	unsigned char	ch;

	j = 0;
	i = 0;
	str = (unsigned char *) s;
	ch = (unsigned char) c;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			j = i;
		i++;
	}
	if (str[j] == ch)
		return ((char *)str + j);
	if (ch == '\0')
		return ((char *)str + i);
	return (NULL);
}
