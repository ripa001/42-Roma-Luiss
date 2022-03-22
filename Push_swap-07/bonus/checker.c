/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:44:08 by dripanuc          #+#    #+#             */
/*   Updated: 2022/03/21 13:02:04 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_struct	*init_game(void)
{
	t_struct	*data;

	data = malloc(sizeof(t_struct));
	data->ar_a = 0;
	data->ar_b = 0;
	data->size_a = 0;
	data->size_b = 0;
	return (data);
}

void	handle_result_line2(char *line, t_struct *data)
{
	if (!(ft_strncmp(line, "rb", ft_strlen(line) - 1)))
		ft_rotate_b(data);
	else if (!(ft_strncmp(line, "rr", ft_strlen(line) - 1)))
		ft_rotate_r(data);
	else if (!(ft_strncmp(line, "sb", ft_strlen(line) - 1)))
		ft_swap_b(data->ar_b);
	else if (!(ft_strncmp(line, "ss", ft_strlen(line) - 1)))
		ft_swap_s(data->ar_a, data->ar_b);
	else
	{
		ft_error();
		exit(0);
	}
}

void	handle_result_line(char *line, t_struct *data)
{
	if (!(ft_strncmp(line, "sa", ft_strlen(line) - 1)))
		ft_swap_a(data->ar_a);
	else if (!(ft_strncmp(line, "pa", ft_strlen(line) - 1)))
		ft_push_a(data);
	else if (!(ft_strncmp(line, "pb", ft_strlen(line) - 1)))
		ft_push_b(data);
	else if (!(ft_strncmp(line, "rra", ft_strlen(line) - 1)))
		ft_rev_rotate_a(data);
	else if (!(ft_strncmp(line, "rrb", ft_strlen(line) - 1)))
		ft_rev_rotate_b(data);
	else if (!(ft_strncmp(line, "rrr", ft_strlen(line) - 1)))
		ft_rev_rotate_r(data);
	else if (!(ft_strncmp(line, "ra", ft_strlen(line) - 1)))
		ft_rotate_a(data);
	else
		handle_result_line2(line, data);
}

void	read_finish(char *line, t_struct *data)
{
	line = get_next_line(0);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			ft_exit("Error\n");
			exit(0);
		}
		handle_result_line(line, data);
		free(line);
		line = get_next_line(0);
	}
	if (ordered_stack(data) > 0)
		ft_exit("\nOK\n");
	else
		ft_exit("\nKO\n");
}

int	main(int argc, char *argv[])
{
	t_struct	*data;
	char		*line;

	data = init_game();
	line = NULL;
	if (argc < 2)
		return (0);
	fill_args(data, argv, argc);
	if (!check_args(argc, argv)
		|| !ft_checkfordoubles(data->ar_a, data->size_a))
	{
		free_all2(data);
		ft_exit("Error\n");
		return (0);
	}
	read_finish(line, data);
	free_all2(data);
	return (0);
}
