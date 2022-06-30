/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:55:22 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:19:34 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_get(char *s1, char *s2)
{
	size_t	a[2];
	char	*r;

	r = (char *)malloc((ft_strlen_get(s1) + ft_strlen_get(s2) + 1));
	if (!r)
		return (NULL);
	a[0] = -1;
	a[1] = 0;
	while (s1[++a[0]])
	{
		r[a[1]] = s1[a[0]];
		a[1]++;
	}
	a[0] = -1;
	while (s2[++a[0]])
	{
		r[a[1]] = s2[a[0]];
		a[1]++;
	}
	r[a[1]] = 0;
	free(s1);
	return (r);
}

char	*ft_substr_get(char *s, unsigned int start, size_t len)
{
	int		i;
	int		j;
	size_t	a;
	char	*r;

	if (!s)
		return (NULL);
	if (ft_strlen_get(s) > (int)len)
		a = len;
	else
		a = ft_strlen_get(s);
	r = malloc((a + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
		if (i >= (int)start && ++j < (int)len)
			r[j] = s[i];
	r[j + 1] = 0;
	return (r);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)(s + i));
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return ((char *)(s + i));
// 	return (NULL);
// }

int	ft_strlen_get(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strdup_get(char *s1)
{
	char	*s2;
	size_t	i;

	s2 = (char *)malloc((ft_strlen(s1) + 1) * sizeof(*s1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
