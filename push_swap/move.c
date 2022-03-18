/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:52:42 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/18 16:52:43 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_move_1(t_struct *data, t_moves *moves, int min)
{
	int	a;
	int	b;

	a = moves[min].min_a;
	b = moves[min].min_b - 1;
	while (b--)
		ft_rotate_b(data);
	while (a--)
		ft_rev_rotate_a(data);
	ft_push_a(data);
}

void	ft_move_2(t_struct *data, t_moves *moves, int min)
{
	int	a;
	int	b;

	a = moves[min].min_a;
	b = moves[min].min_b - 1;
	while (b--)
		ft_rotate_b(data);
	while (a--)
		ft_rotate_a(data);
	ft_push_a(data);
}

void	ft_move_3(t_struct *data, t_moves *moves, int min)
{
	int	a;
	int	b;

	a = moves[min].min_a;
	b = moves[min].min_b - 1;
	while (b--)
		ft_rev_rotate_b(data);
	while (a--)
		ft_rev_rotate_a(data);
	ft_push_a(data);
}

void	ft_move_4(t_struct *data, t_moves *moves, int min)
{
	int	a;
	int	b;

	a = moves[min].min_a;
	b = moves[min].min_b - 1;
	while (b--)
		ft_rev_rotate_b(data);
	while (a--)
		ft_rotate_a(data);
	ft_push_a(data);
}

void	ft_move(t_struct *data, t_moves *moves, int min)
{
	if (moves[min].dir_b && moves[min].dir_a)
		ft_move_1(data, moves, min);
	else if (moves[min].dir_b && !moves[min].dir_a)
		ft_move_2(data, moves, min);
	else if (!moves[min].dir_b && moves[min].dir_a)
		ft_move_3(data, moves, min);
	else
		ft_move_4(data, moves, min);
}
