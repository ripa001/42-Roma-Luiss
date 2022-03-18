/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:31 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/18 19:13:56 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	checks(char *arg, int i, long long nbr)
{
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_error();
			exit(0);
		}
		i++;
	}
	i = 0;
	while (arg[i])
	{
		nbr = nbr * 10 + (arg[i] - 48);
		i++;
	}
	return (nbr);
}

int	ft_is_integer(char *arg)
{
	long long	nbr;
	int			i;
	int			sign;

	nbr = 0;
	sign = 1;
	i = 0;
	if (arg[0] == '-')
	{
		i++;
		sign = -1;
	}
	nbr = checks(arg, i, nbr);
	nbr *= sign;
	if (nbr > 2147483647 || nbr < -2147483648)
		return (0);
	return (1);
}

void	ft_checkmalloc(void *ptr)
{
	if (ptr == NULL)
		ft_error();
}

int	ft_order(int *ar, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (ar[i] > ar[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(char **argv, int size)
{
	int	row;
	int	col;

	row = 1;
	while (row < size)
	{
		col = 0;
		if (argv[row][col] == '-' || argv[row][col] == '+')
			col += 1;
		if (argv[row][col] == '\0')
			return (0);
		if (!ft_is_integer(argv[row]))
			return (0);
		while (argv[row][col] != '\0')
		{
			if (ft_isdigit(argv[row][col]) == 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}
