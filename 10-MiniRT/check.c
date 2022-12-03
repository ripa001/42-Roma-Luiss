/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:04:03 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/30 19:22:40 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_arg(t_data *data)
{
	int	a;
	int	c;
	int	l;
	int	i;

	i = -1;
	a = 0;
	c = 0;
	l = 0;
	while (data->matrix[++i])
	{
		if (data->matrix[i][0] == 'A')
			a++;
		if (data->matrix[i][0] == 'C')
			c++;
		if (data->matrix[i][0] == 'L')
			l++;
	}
	if (a != 1 || c != 1 || l != 1)
		return (0);
	return (1);
}

void	parse_buff(char *buff, t_data *data)
{
	char	**args;

	if (!*buff)
		return ;
	args = ft_split(buff, ' ');
	if (!args[1])
	{
		ft_free_array(args);
		ft_error("Error, Invalid line\n");
		exit(1);
	}
	if (args[0][0] == 'C')
	{
		if (camera_init(args, &data->cam) == -1)
			exit(0);
	}
	else
	{
		if (ft_strcmp(args[0], "pl") == 0 || ft_strcmp(args[0], "sp") == 0 || \
			ft_strcmp(args[0], "cn") == 0 || ft_strcmp(args[0], "cy") == 0)
			add_obj(args, data);
		else
			add_light(args, data);
	}
	ft_free_array(args);
}

char	*read_map(int fd)
{
	char	*buff;
	char	*tmp;
	char	*to_matrix;

	to_matrix = 0;
	tmp = NULL;
	while (fd > 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		tmp = ft_strjoin(to_matrix, buff);
		to_matrix = tmp;
		free (buff);
	}
	return (to_matrix);
}

int	ft_init(t_data *data, int fd)
{
	char	*to_matrix;
	int		i;

	to_matrix = read_map(fd);
	data->matrix = ft_split(to_matrix, '\n');
	if (check_arg(data) == 0)
		return (ft_error("Invalid Arguments\n"));
	i = -1;
	printf("Reading file map...\n");
	while (data->matrix[++i])
	{
		parse_buff(data->matrix[i], data);
		printf("%s\n", data->matrix[i]);
	}
	free(to_matrix);
	ft_free_array(data->matrix);
	return (1);
}
