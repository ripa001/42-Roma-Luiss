/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:43:45 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/22 18:59:35 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	decrescent_algorithm(t_struct *data)
{
	while (data->size_a > 3)
	{
		ft_rev_rotate_a(data);
		ft_push_b(data);
	}
	ft_rotate_a(data);
	ft_swap_a(data->ar_a);
}

int	sort_3(t_struct *data, int flag)
{
	if (data->ar_a[0] < data->ar_a[2] && data->ar_a[2] < data->ar_a[1])
	{
		ft_rotate_a(data);
		ft_rotate_a(data);
		ft_swap_a(data->ar_a);
	}
	else if (data->ar_a[1] < data->ar_a[0] && data->ar_a[0] < data->ar_a[2])
		ft_swap_a(data->ar_a);
	else if (data->ar_a[1] < data->ar_a[2] && data->ar_a[2] < data->ar_a[0])
		ft_rotate_a(data);
	else if (data->ar_a[2] < data->ar_a[1] && data->ar_a[1] < data->ar_a[0])
		decrescent_algorithm(data);
	else if (data->ar_a[2] < data->ar_a[0] && data->ar_a[0] < data->ar_a[1])
		ft_rev_rotate_a(data);
	if (flag)
	{
		free(data->ar_a);
		free(data->ar_b);
	}
	return (0);
}

int	find_min_pos(t_struct *data)
{
	int	i;
	int	min;

	i = -1;
	min = 0;
	while (++i < data->size_a)
		if (data->ar_a[i] < data->ar_a[min])
			min = i;
	return (min);
}

int	five_numbers(t_struct *data)
{
	int	i;

	while (data->size_a > 3)
	{
		i = find_min_pos(data);
		if (i < 3)
			while (i-- > 0)
				ft_rotate_a(data);
		else
		{
			while (data->size_a - i > 0)
			{
				ft_rev_rotate_a(data);
				i++;
			}
		}
		ft_push_b(data);
	}
	sort_3(data, 0);
	ft_push_a(data);
	ft_push_a(data);
	free(data->ar_b);
	free(data->ar_a);
	return (0);
}

void	find_smallest(t_struct *data)
{
	int	len;
	int	min;

	min = 2147483647;
	len = 0;
	while (len < data->size_a)
	{
		if (data->ar_a[len] < min)
			min = data->ar_a[len];
		len++;
	}
	exec_swap(data, min);
}
