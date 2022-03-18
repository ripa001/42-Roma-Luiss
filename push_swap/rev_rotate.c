/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:08:10 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/27 21:42:56 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rev_rotate(int *ar, int size)
{
	int	temp;

	size -= 1;
	temp = ar[size];
	while (size > 0)
	{
		ar[size] = ar[size - 1];
		size--;
	}
	ar[size] = temp;
}

void	ft_rev_rotate_a(t_struct *data)
{
	write(1, "rra\n", 4);
	ft_rev_rotate(data->ar_a, data->size_a);
}

void	ft_rev_rotate_b(t_struct *data)
{
	write(1, "rrb\n", 4);
	ft_rev_rotate(data->ar_b, data->size_b);
}

void	ft_rev_rotate_r(t_struct *data)
{
	write(1, "rrr\n", 4);
	ft_rev_rotate(data->ar_a, data->size_a);
	ft_rev_rotate(data->ar_b, data->size_b);
}
