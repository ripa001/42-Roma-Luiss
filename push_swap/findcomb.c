/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:45:51 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/10 12:47:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_newcomb(int **ar, int nb, int pos)
{
	*ar = (int *)malloc(sizeof(int) * 1);
	ft_checkmalloc(*ar);
	*ar[pos] = nb;
}

void ft_newrow(int **ar, int nb, int pos)
{
	int i;

	i = -1;
	ar[pos] = (int *) malloc(sizeof(int) * (pos + 1));
	ft_checkmalloc(ar);
	while (++i != pos)
		ar[pos][i] = ar[pos - 1][i];
	ar[pos][i] = nb;
}

void ft_checkmiddle(int **ar, int nb, int pos)
{
	int i;

	i = -1;
	while(nb < ar[pos][pos])
		pos--;
	while (++i < pos + 1)
		ar[pos + 1][i] = ar[pos][i];
	ar[pos + 1][pos + 1] = nb;
}

int	*ft_findcomb(t_struct *data)
{
	int		**comb;
	int		row;

	int		i;

	comb = (int **) malloc (sizeof(int *) * data->size_a);
	ft_checkmalloc(comb);
	i = data->min_pos;
	ft_newcomb(comb, data->ar_a[i], 0);
	row = 0;
	i += 1;
	if (i == data->size_a)
		i = 0;
	while (i != data->min_pos)
	{
		if (data->ar_a[i] > comb[row][row])
			ft_newrow(comb, data->ar_a[i], ++row);
		else
			ft_checkmiddle(comb, data->ar_a[i], row);
}
		i++;
		if (i == data->size_a)
			i = 0;
	}
	// free(comb);
	data->size_comb = row;
	return (comb[row]);
}
