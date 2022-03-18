/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:43:45 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/18 17:31:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_struct *data)
{
	if (data->ar_a[0] < data->ar_a[1] && data->ar_a[0] \
		< data->ar_a[2] && data->ar_a[1] > data->ar_a[2])
		ft_swap_a(data->ar_a);
	if (data->ar_a[0] < data->ar_a[1] \
		&& data->ar_a[0] > data->ar_a[2])
		ft_rev_rotate_a(data);
	if (data->ar_a[0] > data->ar_a[2])
		ft_rotate_a(data);
	if (data->ar_a[0] > data->ar_a[1])
		ft_swap_a(data->ar_a);
}

void	sort_u6_2(t_struct *data)
{
	if (data->ar_b[0] < get_this_min(data))
		ft_push_a(data);
	else if (data->ar_b[0] > get_max(data))
	{
		ft_push_a(data);
		ft_rotate_a(data);
	}
	else
	{
		ft_push_a(data);
		find_smallest(data);
	}
}

int	sort_u6(t_struct *data)
{
	if (data->size_a > 3)
	{
		if (data->size_a == 5)
			ft_push_b(data);
		ft_push_b(data);
	}
	sort_3(data);
	while (data->size_b)
		sort_u6_2(data);
	return (0);
}
