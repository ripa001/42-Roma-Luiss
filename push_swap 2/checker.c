/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:06:31 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/06 12:14:13 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int ft_check(char **matrix, int size)
{
	int row;
	int col;

	row = 1;
	while (row < size)
	{
		col = 0;
		if (matrix[row][col] == '-' || matrix[row][col] == '+')
			col += 1;
		if (matrix[row][col] == '\0')
			return (0);
		while (matrix[row][col] != '\0')
		{
			if (ft_isdigit(matrix[row][col]) == 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	ft_checkfordoubles(int *ar, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if( ar[i] == ar[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
