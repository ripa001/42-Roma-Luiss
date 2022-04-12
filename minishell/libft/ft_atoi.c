/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebassi <ebassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:03:28 by ebassi            #+#    #+#             */
/*   Updated: 2022/01/13 12:35:46 by ebassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	is_space(char *str);
static long	ft_sign(char *str, long int index);
static long	find_sign(char *str, long int index);

int	ft_atoi(const char *str)
{
	long	nbr;
	long	index;
	long	index2;
	int		sign;

	nbr = 0;
	index = is_space(((char *)str));
	sign = find_sign(((char *)str), index);
	index2 = ft_sign(((char *)str), index) - index;
	if (index2 > 1)
		return (0);
	index += index2;
	while (((char *)str)[index] == '-' || ((char *)str)[index] == '+')
		index++;
	while (((char *)str)[index] >= '0' && ((char *)str)[index] <= '9')
	{
		nbr = nbr * 10 + ((char *)str)[index] - '0';
		index++;
	}
	if (sign)
		return (nbr);
	return (nbr * -1);
}

static long	find_sign(char *str, long int index)
{
	long	sign;

	sign = 0;
	while (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
		{
			sign++;
			index++;
		}
		else
			index++;
	}
	if (sign % 2 == 0)
		return (1);
	return (0);
}

static long	ft_sign(char *str, long int index)
{
	long	sign;

	sign = 0;
	while (str[index] == '+' || str[index] == '-')
		index++;
	return (index);
}

static long	is_space(char *str)
{
	long	index;

	index = 0;
	while (str[index] != '+' || str[index] != '-')
	{
		if (str[index] == ' ' || str[index] == '\t')
			index++;
		else if (str[index] == '\n' || str[index] == '\r')
			index++;
		else if (str[index] == '\f' || str[index] == '\v')
			index++;
		else
			return (index);
	}
	return (index);
}
