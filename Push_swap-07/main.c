/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:58:46 by mabasset          #+#    #+#             */
/*   Updated: 2022/03/22 20:25:10 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_chunk(t_struct *data, int c, int y, int *maxcomb)
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

void	ft_resolve(t_struct *data)
{
	int	max_size;
	int	*max;
	int	*avg;

	data->ar_a = ft_trasformer(data->ar_a, data->size_a);
	data->min = ft_min(data->ar_a, data->size_a);
	data->min_pos = ft_findind(data->min, data->ar_a);
	data->max = ft_max(data->ar_a, data->size_a);
	data->max_pos = ft_findind(data->max, data->ar_a);
	max_size = data->size_a;
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
	free(data->ar_a);
	free(data->ar_b);
}

int	main(int argc, char *argv[])
{
	t_struct	data;

	if (argc == 1)
		ft_error();
	if (argc == 2)
		argv = ft_split_push(argv[1], ' ', &argc);
	if (ft_check(argv, argc) == 0)
		ft_error();
	ft_initializer(argv, argc, &data);
	if (ft_order(data.ar_a, data.size_a))
	{
		free(data.ar_a);
		free(data.ar_b);
		return (0);
	}
	if (ft_checkfordoubles(data.ar_a, data.size_a) == 0)
		ft_error();
	if (argc == 4)
		return (sort_3(&data, 1));
	if (argc < 7 && argc > 4)
		return (five_numbers(&data));
	ft_resolve(&data);
	return (0);
}
