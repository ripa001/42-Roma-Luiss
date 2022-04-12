/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:13 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/12 15:57:46 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_res(char const *s1, char const *s2, char *res, int len);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len;

	len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	res = (char *) malloc (len + 1);
	if (!res)
		return (NULL);
	ft_res(s1, s2, res, len);
	return (res);
}

static char	*ft_res(char const *s1, char const *s2, char *res, int len)
{
	int	index;
	int	j;

	index = 0;
	j = 0;
	while (index < len)
	{
		while (j < (int)ft_strlen(s1))
		{
			res[index] = s1[j];
			index++;
			j++;
		}
		j = 0;
		while (j < (int)ft_strlen(s2))
		{
			res[index] = s2[j];
			index++;
			j++;
		}
	}
	res[index] = '\0';
	return (res);
}
