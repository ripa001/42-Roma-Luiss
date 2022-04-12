/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:06:25 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/19 16:54:37 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		tmp_start;
	int		i;

	tmp_start = (int)start;
	if (!s)
		return (NULL);
	if ((int)start > (int)ft_strlen(s))
		return (ft_strdup(""));
	substr = (char *) malloc (len + 1);
	substr[len] = '\0';
	if (!substr)
		return (0);
	i = 0;
	while (start < (tmp_start + len))
	{
		substr[i] = s[(int)start];
		start++;
		i++;
	}
	return (substr);
}
