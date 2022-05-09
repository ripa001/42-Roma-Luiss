/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:30:29 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/18 19:30:30 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	check_integer(char *str)
{
	int		i;
	char	**nbrs;

	i = 0;
	nbrs = ft_split(str, ' ');
	while (nbrs[i])
	{
		if (!ft_is_integer(nbrs[i]))
		{
			free_nbrs(nbrs);
			return (0);
		}
		i++;
	}
	free_nbrs(nbrs);
	return (1);
}

void	handle_arg(t_struct *data, char **nums, char *argv[], int i)
{
	int	j;

	j = 0;
	free(data->ar_a);
	free(data->ar_b);
	nums = ft_split(argv[1], ' ');
	i = 0;
	while (nums[i])
		i++;
	data->ar_a = malloc(sizeof(int *) * i);
	data->ar_b = malloc(sizeof(int *) * i);
	while (nums[j])
	{
		data->ar_a[j] = ft_atoi(nums[j]);
		data->size_a++;
		j++;
	}
	i = 0;
	while (nums[i])
	{
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	fill_args(t_struct *data, char *argv[], int argc)
{
	int		i;
	int		j;
	char	**nums;

	i = 1;
	j = 0;
	nums = 0;
	data->ar_a = malloc(sizeof(int *) * argc - 1);
	data->ar_b = malloc(sizeof(int *) * argc - 1);
	if (argc == 2)
		handle_arg(data, nums, argv, i);
	else
	{
		while (i < argc)
		{
			data->ar_a[j] = ft_atoi(argv[i]);
			data->size_a++;
			i++;
			j++;
		}
	}
}

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 2)
		return (0);
	if (argc == 2)
	{
		if (check_integer(argv[1]))
			return (1);
		return (0);
	}
	while (i < argc)
	{
		if (!ft_is_integer(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ordered_stack(t_struct *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->size_b)
		return (-1);
	while (i < data->size_a)
	{
		j = i + 1;
		while (j < data->size_a)
		{
			if (!(data->ar_a[i] < data->ar_a[j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}
