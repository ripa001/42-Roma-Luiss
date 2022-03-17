/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:20:53 by mabasset          #+#    #+#             */
/*   Updated: 2022/02/12 08:42:11 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int	*a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_a(int *ar)
{
	write(1, "sa\n", 3);
	ft_swap(ar, ar + 1);
}

void	ft_swap_b(int *ar)
{
	write(1, "sb\n", 3);
	ft_swap(ar, ar + 1);
}

void	ft_swap_s(int *ar_a, int *ar_b)
{
	write(1, "ss\n", 3);
	ft_swap(ar_a, ar_a + 1);
	ft_swap(ar_b, ar_b + 1);
}
