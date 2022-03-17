/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:58:46 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/17 19:11:20 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_move_until_orded(t_struct *data)
{
	int div;
	int i;
	int ix;

	div = data->size_a / 2;
	i = -1;
	while (++i < data->size_a)
		if (data->ar_a[i] == 1)
			ix = i;
	if (ix < div)
		while (data->ar_a[0] != 1)
			ft_rotate_a(data);
	else
		while (data->ar_a[0] != 1)
			ft_rev_rotate_a(data);
}

void	ft_move(t_struct *data, t_moves *moves, int min)
{
	int a;
	int b;

	a = moves[min].min_a;
	b = moves[min].min_b - 1;
	if (moves[min].dir_b && moves[min].dir_a)
	{
		while (b--)
			ft_rotate_b(data);
		while (a--)
			ft_rev_rotate_a(data);
		ft_push_a(data);
	}
	else if (moves[min].dir_b && !moves[min].dir_a)
	{
		while (b--)
			ft_rev_rotate_b(data);
		while (a--)
			ft_rotate_a(data);
		ft_push_a(data);
	}
	else if (!moves[min].dir_b && moves[min].dir_a)
	{
		while (b--)
			ft_rev_rotate_b(data);
		while (a--)
			ft_rev_rotate_a(data);
		ft_push_a(data);
	}
	else
	{
		while (b--)
			ft_rev_rotate_b(data);
		while (a--)
			ft_rotate_a(data);
		ft_push_a(data);
	}
}

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

int	ft_get_min_arr(t_moves *moves, int size)
{
	int i;
	int ix;
	int min;

	i = -1;
	min = 0;
	ix = 0;
	while (++i < size)
		if (min > moves[i].sum || i == 0)
		{
			ix = i;
			min = moves[i].sum;
		}
	return (ix);
}


int ft_count_front_b(t_struct *data, int i)
{
	int count;
	int max;

	count = -1;
	max = 0;
	while (++count < data->size_b)
	{
		max = get_max(data->ar_b, data->size_b, data->ar_b[i]);
		if (data->ar_b[count] == max)
			break ;
	}
	return (data->size_b - i + 1);
}

int ft_count_back_b(t_struct *data, int i)
{
	int count;
	int max;

	count = data->size_b;
	max = 0;
	while (count--)
	{
		max = get_max(data->ar_b, data->size_b, data->ar_b[i]);
		if (data->ar_b[count] == max)
			break ;
	}
	return (i + 1);
}
int ft_count_front_a(t_struct *data, int i)
{
	int count;
	int max;

	count = -1;
	max = 0;
	while (++count < data->size_a)
	{
		max = get_max(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (count + 1);
}

int ft_count_back_a(t_struct *data, int i)
{
	int count;
	int max;

	count = data->size_a;
	max = 0;
	while (count--)
	{
		max = get_max(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (data->size_a - count - 1);
}

void	ft_count_moves(t_struct *data)
{
	t_moves *moves;
	int	i;
	int	count;
	int	min;

	i = -1;
	count = 0;
	// min = 0;
	moves = malloc(sizeof(t_moves) * (data->size_b));
	while (++i < data->size_b)
	{
		moves[i].min_a = ft_count_back_a(data, i);
		count = ft_count_front_a(data, i);
		moves[i].dir_a = 1;
		if (count < moves[i].min_a)
		{
			moves[i].min_a = count;
			moves[i].dir_a = 0;
		}
		count = ft_count_front_b(data, i);
		moves[i].min_b = ft_count_back_b(data, i);
		moves[i].dir_b = 1;
		if (count < moves[i].min_b)
		{
			moves[i].min_b = count;
			moves[i].dir_b = 0;
		}
		moves[i].sum = moves[i].min_b + moves[i].min_a;
		printf("min_b - dir: %d - %d | min_a - dir: %d - %d | sum: %d \n", moves[i].min_b, moves[i].dir_b, moves[i].min_a, moves[i].dir_a, moves[i].sum);
	}
	min = ft_get_min_arr(moves, data->size_b);
	printf("Chosed min index: %d\n", min);
	ft_move(data, moves, min);
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

		while (data->size_b){
			printf("Arr a:\n");
		ft_printarray(data->ar_a, data->size_a);
		printf("Arr b:\n");
		ft_printarray(data->ar_b, data->size_b);
			ft_count_moves(data);
			}
		// 	printf("Arr a moved:\n");
		// ft_printarray(data->ar_a, data->size_a);
		// printf("Arr b moved:\n");
		// ft_printarray(data->ar_b, data->size_b);
		// 	ft_count_moves(data);
		ft_move_until_orded(data);
		printf("Arr a moved:\n");
		ft_printarray(data->ar_a, data->size_a);
		printf("Arr b moved:\n");
		ft_printarray(data->ar_b, data->size_b);
		printf("\n");
		// ft_printarray(ft_count_moves(data), data->size_b);
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
