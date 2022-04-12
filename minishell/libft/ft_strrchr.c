/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:05:59 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/18 12:27:53 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*res;
	int		temp_index;
	char	ch;

	ch = c;
	i = 0;
	len = 0;
	temp_index = -1;
	while (s[len] != '\0')
		len++;
	while (i < len + 1)
	{
		if (s[i] == ch)
			temp_index = i;
		i++;
	}
	res = (char *)&s[temp_index];
	if (temp_index == -1)
		return (NULL);
	else
		return (res);
}
