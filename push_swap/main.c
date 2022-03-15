/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:58:46 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/15 20:10:27 by dripanuc         ###   ########.fr       */
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

int ft_check_set(int *arr, int c, int size)
{
	int i;

	i = -1;
	while (++i < size)
		if (arr[i] == c)
			return (1);
	return (0);
}

void	push_in_b(t_struct *data, int pos, int val)
{
	int div;

	div = data->size_a / 2;
	if (pos < div)
		while (data->ar_a[0] != val)
			ft_rotate_a(data);
	else
		while (data->ar_a[0] != val)
			ft_rev_rotate_a(data);
	ft_push_b(data);
}

int get_max(int *arr, int size, int x)
{
	int i;
	int max;

	i = -1;
	max = 0;
	while (++i < size)
		if (arr[i] > max && arr[i] < x)
			max = arr[i];
	return (max);
}

int	*ft_count_moves(t_struct *data)
{
	int	i;
	int	count;
	int	min;
	int	max;
	int	div;
	int	*a;

	i = -1;
	count = 0;
	div = 0;
	min = 1;
	a = malloc(sizeof(int) * (data->size_b));
	while (++i < data->size_b)
	{
		count = -1;
		while (++count < data->size_a)
		{
			max = get_max(data->ar_a, data->size_a, data->ar_b[i]);
			if (data->ar_a[count] == max)
				break ;
		}
		min += count++;
		count = data->size_a;
		while (count--)
		{
			max = get_max(data->ar_a, data->size_a, data->ar_b[i]);
			if (data->ar_a[count] == max)
				break ;
		}
		count = data->size_a - count;
		max = 1;
		if (++count < min)
		{
			min = count;
			max = 0;
		}
		a[i] = min;
	}
	return (a);
}

int ft_check_chunk(t_struct *data, int c, int y, int *maxcomb)
{
	int i;

	i = -1;
	while (++i < data->size_a)
		if (data->ar_a[i] > c && data->ar_a[i] < y && !ft_check_set(maxcomb, data->ar_a[i], data->size_comb))
			return (1);
	return (0);
}

void	ft_sep(t_struct *data, int *max_comb, int *avg)
{
	int i;
	int f;
	int flag;

	i = -1;
	f = 0;
	flag = 1;
	while (++f < 5)
	{
		flag = 1;
		while (flag)
		{
			i = -1;
			while (++i < data->size_a)
			{
				if (!ft_check_set(max_comb, data->ar_a[i], data->size_comb))
					if (data->ar_a[i] > avg[f - 1] && data->ar_a[i] <= avg[f])
					{
						flag = 1;
						push_in_b(data, i, data->ar_a[i]);
						break ;
					}
				flag = 0;
			}
		}
	}
}

int *ft_avg(int size)
{
	int i;
	int *s;
	int g;

	s = (int *)malloc(sizeof(int) * 5);
	i = -1;
	g = 0;
	while (++i < size)
		g += i + 1;
	s[0] = 0;
	s[2] = g / (i + 1);
	i = -1;
	g = 0;
	while (++i < size / 2)
		g += i + 1;
	s[1] = g / (i + 1);
	g = 0;
	while (++i < size + 1)
		g += i;
	s[3] = g / ((i) / 2);
	s[4] = size;
	return (s);
}

void	ft_resolve(t_struct *data)
{
	int	max_size;
	int *max;
	int *avg;

	max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * max_size);
	data->size_b = 0;
	if(ft_order(data->ar_a, data->size_a) == 0)
	{
		max = ft_findcomb(data);
		avg = ft_avg(data->size_a);
		ft_sep(data, max, avg);
		ft_count_moves(data);
		ft_printarray(max, data->size_comb);
		printf("\n");
		ft_printarray(data->ar_a, data->size_a);
		printf("\n");
		ft_printarray(data->ar_b, data->size_b);
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
	data.ar_a = ft_trasformer(data.ar_a, data.size_a);
	data.min = ft_min(data.ar_a, data.size_a);
	data.min_pos = ft_findind(data.min, data.ar_a, data.size_a);
	ft_printarray(data.ar_a, data.size_a);
	printf("\n");
	data.max = ft_max(data.ar_a, data.size_a);
	data.max_pos = ft_findind(data.max, data.ar_a, data.size_a);
	ft_resolve(&data);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
