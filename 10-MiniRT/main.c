/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:12:57 by mcipolla          #+#    #+#             */
/*   Updated: 2022/12/03 18:40:29 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	find_edges(t_obj *cyl, t_v3 O, t_v3 D, float *t)
{
	float	max;
	t_v3	point;
	t_v3	len;
	float	t2;

	if (t[0] > t[1])
		t2 = t[1];
	else
		t2 = t[0];
	max = sqrtf(pow(cyl->h / 2, 2) + pow(cyl->r, 2));
	point = add_vec(O, mult_vec_n(D, t2));
	len = sub_vec(point, cyl->pos);
	if (norm(len) > max)
	{
		if (t[0] < t[1])
			t2 = t[1];
		else
			t2 = t[0];
		point = add_vec(O, mult_vec_n(D, t2));
		len = sub_vec(point, cyl->pos);
		if (norm(len) > max)
			t2 = INFINITY;
	}
	return (t2);
}

float	find_edges_cone(t_obj *cn, t_v3 O, t_v3 D, float *t)
{
	float	max;
	t_v3	point;
	t_v3	len;
	float	t2;

	if (t[0] > t[1])
		t2 = t[1];
	else
		t2 = t[0];
	max = sqrtf(((cn->h * cn->h) / 2) + pow(cn->r, 2));
	point = add_vec(O, mult_vec_n(D, t2));
	len = sub_vec(point, cn->pos);
	if (norm(len) > max)
	{
		if (t[0] < t[1])
			t2 = t[1];
		else
			t2 = t[0];
		point = add_vec(O, mult_vec_n(D, t2));
		len = sub_vec(point, cn->pos);
		if (norm(len) > max)
			t2 = INFINITY;
	}
	return (t2);
}

int	parse_and_check(t_data *data, int argc, char *argv[])
{
	int	fd;
	int	x;

	x = ft_strlen(argv[1]);
	x = x - 3;
	if (!argv[1] || ft_strcmp(&argv[1][x], ".rt") || argc > 3)
		return (ft_error("Error, Invalid Arguments\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("Error, Invalid Arguments\n"));
	if (argc > 3 || argc < 2)
		return (ft_error("Error, Invalid Arguments\n"));
	if (ft_init(data, fd) != 1)
		exit(0);
	printf("Done!\n\nOur comand:\n\tW - A - S - D  - Q - E\n");
	printf("\tup - down - left - right\n\tT | Input from command line\n\t");
	printf("C | Apply checkerboard on sphere\n\tESC | Exit program \n");
	return (fd);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse_and_check(&data, argc, argv) < 0)
		exit(0);
	data.width = 1080;
	data.height = 500;
	data.reflection = 0;
	if (argc == 3)
		data.reflection = ft_atoi(argv[2]);
	data.frame = 1;
	data.mlx = mlx_init();
	data.texture = ft_get_pattern(&data, "files/xpm/42.xpm");
	data.bump = ft_get_pattern(&data, "files/xpm/bump.xpm");
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
		&data.line_length, &data.endian);
	mlx_hook(data.mlx_win, 2, (1 >> 1L), ft_hooks, &data);
	mlx_hook(data.mlx_win, 17, 0, mouse_exit, &data);
	mlx_loop_hook(data.mlx, ft_update, &data);
	mlx_loop(data.mlx);
}
