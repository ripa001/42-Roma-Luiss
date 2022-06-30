/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 03:51:54 by mpatrini          #+#    #+#             */
/*   Updated: 2022/02/05 19:24:55 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoa_len2(size_t n)
{
	int		len;
	size_t	tmp;

	len = 0;
	tmp = n;
	if (n == 0)
		len = 1;
	else
	{
		while (tmp)
		{
			tmp /= 16;
			len++;
		}
	}
	return (len);
}

char	*ft_hex_long_itoa(size_t n, const char *base)
{
	int				len;
	char			*str;

	len = ft_itoa_len2(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	len -= 1;
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (n)
	{
		str[len] = base[n % 16];
		n /= 16;
		len--;
	}
	return (str);
}

char	*ft_hex_itoa(unsigned int n, const char *base)
{
	int				len;
	char			*str;

	len = ft_itoa_len2(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	len -= 1;
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (n)
	{
		str[len] = base[n % 16];
		n /= 16;
		len--;
	}
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	a[2];
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	r = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
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
	free(s2);
	return (r);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	int		i;
	int		j;
	size_t	a;
	char	*r;

	if (!s)
		return (NULL);
	if (ft_strlen(s) > len)
		a = len;
	else
		a = ft_strlen(s);
	r = ft_calloc(a + 1, sizeof(char));
	if (!r)
		return (NULL);
	i = -1;
	j = -1;
	while (s[++i])
		if (i >= (int)start && ++j < (int)len)
			r[j] = s[i];
	r[j + 1] = 0;
	free(s);
	return (r);
}
