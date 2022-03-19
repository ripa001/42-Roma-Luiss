/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:15:13 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/18 19:16:59 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_this_min(t_struct *data)
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
	return (min);
}

int	get_max(t_struct *data)
{
	int	len;
	int	max;

	max = -2147483648;
	len = 0;
	while (len < data->size_a)
	{
		if (data->ar_a[len] > max)
			max = data->ar_a[len];
		len++;
	}
	return (max);
}

void	exec_middle(t_struct *data, int min)
{
	while (data->ar_a[0] != min)
		ft_rotate_a(data);
	if (data->ar_a[0] == min)
		ft_push_b(data);
}

void	exec_swap2(t_struct *data, int min)
{
	if (data->ar_a[data->size_a - 1] == min)
	{
		ft_rev_rotate_a(data);
		ft_push_b(data);
	}
	else if (data->ar_a[data->size_a - 2] == min)
	{
		ft_rev_rotate_a(data);
		ft_rev_rotate_a(data);
		ft_push_b(data);
	}
	else
		exec_middle(data, min);
}

void	exec_swap(t_struct *data, int min)
{
	if (data->ar_a[0] == min)
		ft_push_b(data);
	else if (data->ar_a[1] == min)
	{
		ft_swap_a(data->ar_a);
		ft_push_b(data);
	}
	else
		exec_swap2(data, min);
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

