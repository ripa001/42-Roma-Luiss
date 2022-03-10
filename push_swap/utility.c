/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 05:30:57 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/10 12:44:19 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(void)
{
	write(2, "Error", 5);
	exit(1);
}

int		*ft_ardup(int *ar, int size)
{
	int	*ptr;
	int	i;

	ptr = (int *) malloc (sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		ptr[i] = ar[i];
		i++;
	}
	return (ptr);
}

void	ft_printarray(int *ar, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		printf("%d\n", ar[i]);
		i++;
	}
}

void	ft_sort_ar(int *ar, int size)
{
	int	i;
	int	flag;

	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < size - 1)
		{
			if(ar[i] > ar[i + 1])
			{
				ft_swap(ar + i, ar + (i + 1));
				flag = 0;
			}
			i++;
		}
	}
}

int	*ft_initializer(char **matrix, int size)
{
	int row;
	int	*ar;
	int	i;

	ar = (int *) malloc (sizeof(int) * (size - 1));
	if (ar == NULL)
		ft_error();
	i = 0;
	row = 1;
	while (row < size)
	{
		ar[i] = ft_atoi(matrix[row]);
		i++;
		row++;
	}
	return (ar);
}
