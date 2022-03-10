/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:58:46 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/10 12:43:47 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void	ft_go_away(t_struct *data, int x)
// {
// 	int	i;
// 	int	nb;

// 	nb = data->ar_a[x];
// 	i = 0;
// 	while(data->ar_a[0] != nb)
// 	{
// 		if (x <= data->size_a / 2)
// 			ft_rotate_a(data);
// 		else if (x > data->size_a / 2)
// 			ft_rev_rotate_a(data);
// 	}
// 	ft_push_b(data);
// }

// void	ft_sep(t_struct *data)
// {
// 	int	i;
// 	int	j;
// 	int	flag;

// 	i = 0;
// 	while (i < data->size_a)
// 	{
// 		flag = 0;
// 		j = 0;
// 		while (j < data->size_best)
// 		{
// 			if(data->best[j] == data->ar_a[i])
// 				flag = 1;
// 			j++;
// 		}
// 		if (flag == 0)
// 		{
// 			ft_go_away(data, i);
// 			i = -1;
// 		}
// 		i++;
// 	}
// 	printf("\n");
// 	printf("A:\n");
// 	ft_printarray(data->ar_a, data->size_a);
// 	printf("\n");
// 	printf("B:\n");
// 	ft_printarray(data->ar_b, data->size_b);
// 	printf("\n");
// }

//int		ft_nbcheck()

// int		ft_moves(int nb, t_struct *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->ar_a[i] != nb + 1)
// 	{
// 		if (i == )
// 	}
// }

// void	ft_brainfuck(t_struct *data)
// {
// 	printf("%d\n", data->ar_a[0]);
// 	printf("%d\n", data->ar_b[0]);
// 	while (data->size_b != 0)
// 	{
// 		if ()
// 			while (data->ar_a[0] != data->ar_b[0] + 1)
// 				ft_rotate_a(data);
// 			ft_push_a(data);
// 	}
// 	printf("\n");
// 	printf("A:\n");
// 	ft_printarray(data->ar_a, data->size_a);
// 	printf("\n");
// 	printf("B:\n");
// 	ft_printarray(data->ar_b, data->size_b);
// 	printf("\n");
// }

void	ft_resolve(t_struct *data)
{
	int	max_size;

	max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * max_size);
	data->size_b = 0;
	if(ft_order(data->ar_a, data->size_a) == 0)
	{
		ft_printarray(ft_findcomb(data), data->size_comb);

		//ft_sep(data);
		//ft_brainfuck(data);
	}
}

int	*ft_trasformer(int *ar, int size)
{
	int	*temp;
	int *new;
	int	i;
	int	j;

	new = ft_ardup(ar, size);
	temp = (int *) malloc (sizeof(int) * size);
	ft_sort_ar(new, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (new[i] != ar[j])
			j++;
		temp[j] = i + 1;
		i++;
	}
	free(ar);
	free(new);
	return (temp);
}

int main(int argc, char *argv[])
{
	t_struct data;

    if (argc < 2)
        ft_error();
    if (ft_check(argv, argc) == 0)
        ft_error();
	data.ar_a = ft_initializer(argv, argc);
	data.size_a = argc - 1;
	if (ft_checkfordoubles(data.ar_a, data.size_a) == 0)
		ft_error();
	// data.ar_a = ft_trasformer(data.ar_a, data.size_a);
	data.min = ft_min(data.ar_a, data.size_a);
	data.min_pos = ft_findind(data.min, data.ar_a, data.size_a);
	data.max = ft_max(data.ar_a, data.size_a);
	data.max_pos = ft_findind(data.max, data.ar_a, data.size_a);
	ft_resolve(&data);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
