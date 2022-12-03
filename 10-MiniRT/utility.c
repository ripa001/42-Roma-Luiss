/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:26:46 by mcipolla          #+#    #+#             */
/*   Updated: 2022/12/03 18:31:45 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	return (-1);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

t_v3	ret_vec(char *args)
{
	char	**xyz;
	char	**xyz2;
	t_v3	vec;

	xyz = ft_split(args, ',');
	if (ft_arraylen(xyz) != 3)
	{
		ft_putendl_fd("Error\nInvalid vector", 1);
		exit(1);
	}
	vec.x = ft_atof(xyz[0]);
	vec.y = ft_atof(xyz[1]);
	xyz2 = ft_split(xyz[2], ' ');
	vec.z = ft_atof(xyz2[0]);
	ft_free_array(xyz);
	ft_free_array(xyz2);
	return (vec);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}
