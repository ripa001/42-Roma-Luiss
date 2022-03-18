/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:47:40 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/18 13:11:13 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_min(int *array, int size)
{
	int	min;
	int	i;

	min = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] < min)
			min = array[i];
		i++;
	}
	return (min);
}

int	ft_max(int *array, int size)
{
	int	max;
	int	i;

	max = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	return (max);
}

int	ft_findind(int nb, int *array)
{
	int	i;

	i = 0;
	while (nb != array[i])
		i++;
	return (i);
}

void	free_matrix(int **matrix, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(matrix[i]);
	free(matrix);
}
