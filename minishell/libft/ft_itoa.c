/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:19:38 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/17 11:43:08 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nbr(long nbr);
static char	*convert_itoa(char *res, long nbr, int len, int sign);

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nbr;
	int		sign;

	res = 0;
	nbr = n;
	len = len_nbr(nbr);
	sign = 0;
	res = convert_itoa(res, nbr, len, sign);
	if (!res)
		return (0);
	return (res);
}

static int	len_nbr(long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static char	*convert_itoa(char *res, long nbr, int len, int sign)
{
	if (nbr != 0)
		res = (char *) malloc (len + 1);
	else
		return (res = ft_strdup("0"));
	if (!res)
		return (0);
	sign = 0;
	if (nbr < 0)
	{
		sign++;
		nbr *= -1;
	}
	res[len] = '\0';
	while (--len)
	{
		res[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign == 1)
		res[0] = '-';
	else
		res[0] = nbr % 10 + '0';
	return (res);
}
