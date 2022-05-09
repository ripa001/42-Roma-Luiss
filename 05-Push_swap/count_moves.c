/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:14:47 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/22 17:58:29 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_count_front_a(t_struct *data, int i)
{
	int	count;
	int	max;

	count = -1;
	max = 0;
	while (++count < data->size_a)
	{
		max = get_max_move(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (count + 1);
}

int	ft_count_back_a(t_struct *data, int i)
{
	int	count;
	int	max;

	count = data->size_a;
	max = 0;
	while (count--)
	{
		max = get_max_move(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (data->size_a - count - 1);
}

t_moves	ft_get_moves_el(t_struct *data, int i)
{
	int		count;
	t_moves	el;

	count = 0;
	el.min_a = ft_count_back_a(data, i);
	count = ft_count_front_a(data, i);
	el.dir_a = 1;
	if (count < el.min_a)
	{
		el.min_a = count;
		el.dir_a = 0;
	}
	count = data->size_b - i + 1;
	el.min_b = i + 1;
	el.dir_b = 1;
	if (count < el.min_b)
	{
		el.min_b = count;
		el.dir_b = 0;
	}
	el.sum = el.min_b + el.min_a;
	return (el);
}

void	ft_count_moves(t_struct *data)
{
	t_moves	*moves;
	int		i;
	int		min;

	i = -1;
	moves = malloc(sizeof(t_moves) * (data->size_b));
	while (++i < data->size_b)
		moves[i] = ft_get_moves_el(data, i);
	min = ft_get_min_arr(moves, data->size_b);
	ft_move(data, moves, min);
	free(moves);
}

int	ft_checkfordoubles(int *ar, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = i + 1;
		while (j < size)
			if (ar[i] == ar[j++])
				return (0);
	}
	return (1);
}
