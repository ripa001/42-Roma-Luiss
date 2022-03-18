/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:58:46 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/18 17:30:51 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_move_until_orded(t_struct *data)
{
	int	div;
	int	i;
	int	ix;

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

int	ft_check_set(int *arr, int c, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (arr[i] == c)
			return (1);
	return (0);
}

int	push_in_b(t_struct *data, int pos, int val, int *flag)
{
	int	div;

	div = data->size_a / 2;
	if (pos < div)
		while (data->ar_a[0] != val)
			ft_rotate_a(data);
	else
		while (data->ar_a[0] != val)
			ft_rev_rotate_a(data);
	*flag = 1;
	ft_push_b(data);
	return (0);
}

int	get_max_move(int *arr, int size, int x)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (++i < size)
		if (arr[i] > max && arr[i] < x)
			max = arr[i];
	return (max);
}

int	ft_get_min_arr(t_moves *moves, int size)
{
	int	i;
	int	ix;
	int	min;

	i = -1;
	min = 0;
	ix = 0;
	while (++i < size)
	{
		if (min > moves[i].sum || i == 0)
		{
			ix = i;
			min = moves[i].sum;
		}
	}
	return (ix);
}

int	ft_count_front_a(t_struct *data, int i)
{
	int	count;
	int	max;

	count = -1;
	max = 0;
	while (++count < data->size_a)
	{
		max = get_max_move(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (count + 1);
}

int ft_count_back_a(t_struct *data, int i)
{
	int	count;
	int	max;

	count = data->size_a;
	max = 0;
	while (count--)
	{
		max = get_max_move(data->ar_a, data->size_a, data->ar_b[i]);
		if (data->ar_a[count] == max)
			break ;
	}
	return (data->size_a - count - 1);
}

t_moves ft_get_moves_el(t_struct *data, int i)
{
	int		count;
	t_moves	el;

	count = 0;
	el.min_a = ft_count_back_a(data, i);
	count = ft_count_front_a(data, i);
	el.dir_a = 1;
	if (count < el.min_a)
	{
		el.min_a = count;
		el.dir_a = 0;
	}
	count = data->size_b - i + 1;
	el.min_b = i + 1;
	el.dir_b = 1;
	if (count < el.min_b)
	{
		el.min_b = count;
		el.dir_b = 0;
	}
	el.sum = el.min_b + el.min_a;
	return (el);
}

void	ft_count_moves(t_struct *data)
{
	t_moves	*moves;
	int		i;
	int		count;
	int		min;

	i = -1;
	count = 0;
	moves = malloc(sizeof(t_moves) * (data->size_b));
	while (++i < data->size_b)
		moves[i] = ft_get_moves_el(data, i);
	min = ft_get_min_arr(moves, data->size_b);
	ft_move(data, moves, min);
	free(moves);
}

int ft_check_chunk(t_struct *data, int c, int y, int *maxcomb)
{
	int	i;

	i = -1;
	while (++i < data->size_a)
		if (data->ar_a[i] > c && data->ar_a[i] < y && \
			!ft_check_set(maxcomb, data->ar_a[i], data->size_comb))
			return (1);
	return (0);
}

void	ft_sep(t_struct *data, int *max_comb, int *avg)
{
	int	i;
	int	f;
	int	flag;

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
						if (!push_in_b(data, i, data->ar_a[i], &flag))
							break ;
				flag = 0;
			}
		}
	}
}

int	*ft_avg(int size)
{
	int	i;
	int	*s;
	int	g;

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
	int	*max;
	int	*avg;

	max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * max_size);
	data->size_b = 0;
	if (ft_order(data->ar_a, data->size_a) == 0)
	{
		max = ft_findcomb(data);
		avg = ft_avg(data->size_a);
		ft_sep(data, max, avg);
		free(max);
		free(avg);
		while (data->size_b)
			ft_count_moves(data);
		ft_move_until_orded(data);
	}
}

int	*ft_trasformer(int *ar, int size)
{
	int	*temp;
	int	*new;
	int	i;
	int	j;

	new = ft_ardup(ar, size);
	temp = (int *)malloc(sizeof(int) * size);
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
	t_struct	data;
	int			i;

	i = 0;
	if (argc == 1)
		ft_error();
	if (argc == 2)
		argv = ft_split_push(argv[1], ' ', &argc);
	if (ft_check(argv, argc) == 0)
		ft_error();
	data.ar_a = ft_initializer(argv, argc);
	if (argc < 6)
		return (sort_u6(&data));
	data.size_a = argc - 1;
	if (ft_checkfordoubles(data.ar_a, data.size_a) == 0)
		ft_error();
	data.ar_a = ft_trasformer(data.ar_a, data.size_a);
	data.min = ft_min(data.ar_a, data.size_a);
	data.min_pos = ft_findind(data.min, data.ar_a);
	data.max = ft_max(data.ar_a, data.size_a);
	data.max_pos = ft_findind(data.max, data.ar_a);
	ft_resolve(&data);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
