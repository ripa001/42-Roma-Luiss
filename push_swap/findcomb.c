/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:45:51 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/09 20:22:24 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int		ft_smallest(t_best *comb, int lines, int nb)
// {
// 	int	i;

// 	i = 0;
// 	while (i < lines)
// 	{
// 		if (comb[i].array[comb[i].size - 1] < nb)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }



// void	ft_newcomb(t_best *comb, int j, int nb)
// {
// 	comb[j].array = (int *) malloc (sizeof(int) * data->size_a);
// 	if (comb[i].array == NULL)
// 		ft_error();
// 	comb[j].array[0] = nb];
// 	comb[j].size = 1;
// }

// void	ft_extendcomb(comb, data->ar_a[i])
// {

// }

// int	*ft_findcomb(t_struct *data)
// {
// 	t_best	*comb;
// 	int		i;
// 	int		j;
// 	int		lines;

// 	comb = (t_best *) malloc (sizeof(t_best) * data->size_a);
// 	ft_checkmalloc(comb);
// 	ft_newcomb(comb, 0, data->ar_a[0])
// 	lines = 1;
// 	j = 1;
// 	i = 1;
// 	while (i < data->size_a)
// 	{
// 		if (ft_smallest(comb, lines, data->ar_a[i]) == 1)
// 			ft_newcomb(comb, ++j, data->ar_a[i]);
// 		else if (ft_largest(comb, lines, data->ar_a[i]) == 1)
//             ft_extendcomb(comb, data->ar_a[i]);
// 		else

// 		i++;
// 	}
// 	free(comb);
// }

void	ft_newcomb(int *ar, int nb, int pos)
{
	ar = (int *)malloc(sizeof(int) * 1);
	ft_checkmalloc(ar);
	ar[pos] = nb;
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
	while(nb < ar[pos][pos])
		pos--;
	ft_memcpy(ar[pos + 1], ar[pos], pos + 1);
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
	ft_newcomb(comb[0], data->ar_a[i], 0);
	row = 0;
	i += 1;
	if (i == data->size_a)
		i = 0;
	printf("x\n");
	while (data->ar_a[i] != data->min)
	{
		printf("row %d\n", row);
		printf("%d\n", comb[row][row]);
		if (data->ar_a[i] > comb[row][row])
		{
			printf("x\n");
			ft_newrow(comb, data->ar_a[i], ++row);
			printf("x\n");
		}
		else
			ft_checkmiddle(comb, data->ar_a[i], row);
		i++;
		if (i == data->size_a)
			i = 0;
		printf("x\n");
	}
	// free(comb);
	data->size_comb = row;
	return (comb[row]);
}
