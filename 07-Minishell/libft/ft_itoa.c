/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrini <mpatrini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 04:42:28 by mpatrini          #+#    #+#             */
/*   Updated: 2022/01/12 22:30:50 by mpatrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_malloc(int n)
{
	size_t			len;
	size_t			m;
	unsigned int	nb;

	len = 1;
	m = 1;
	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	while ((nb / m) > 9)
	{
		m *= 10;
		len++;
	}
	if (n < 0)
		len += 1;
	return (len);
}

static unsigned int	ft_itoa3(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	return (nb);
}

static char	*ft_itoa2(int n)
{
	size_t			i;
	size_t			m;
	unsigned int	nb;
	char			*r;

	i = 0;
	m = 1;
	r = (char *)malloc(ft_itoa_malloc(n) + 1);
	if (!r)
		return (NULL);
	if (n < 0)
	{
		r[i] = 45;
		i++;
	}
	nb = ft_itoa3(n);
	while ((nb / m) > 9)
		m *= 10;
	while (m > 0)
	{
		r[i++] = ((nb / m) % 10) + 48;
		m /= 10;
	}
	r[i] = 0;
	return (r);
}

char	*ft_itoa(int n)
{
	char			*r;

	if (n == 0)
	{
		r = (char *)malloc(2);
		if (!r)
			return (NULL);
		r[0] = 48;
		r[1] = 0;
		return (r);
	}
	else
	{
		r = ft_itoa2(n);
		return (r);
	}
}
