/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:13:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/30 18:37:21 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	trace_ray(t_ray ray, t_data *data, int recursion)
{
	t_obj		*closest_obj;
	t_v3		col;
	t_v3		r;
	t_v3		reflected_col;
	t_ray		new_ray;

	closest_obj = closest_intersect(ray, data, 0.00001, INFINITY);
	if (closest_obj == NULL)
		return (ret_vec("0.2,0.2,0.2"));
	ray.hit = add_vec(ray.o, mult_vec_n(ray.d, data->closest_t));
	ray.hit_int = normalize(sub_vec(ray.hit, closest_obj->pos));
	col = ft_bump_and_texture(ray, closest_obj, data);
	if (recursion <= 0 || closest_obj->reflect == 0)
		return (col);
	r = reflect_ray(mult_vec_n(ray.d, -1), ray.hit_int);
	new_ray.o = ray.hit;
	new_ray.d = r;
	reflected_col = trace_ray(new_ray, data, recursion - 1);
	return (add_vec(mult_vec_n(col, 1 - closest_obj->reflect), \
		mult_vec_n(reflected_col, closest_obj->reflect)));
}

t_ray	get_direction(int x, int y, t_data *data)
{
	t_v3	ret;
	t_ray	ray;

	ret.x = (x * (1 / data->width)) * (data->width / data->height) * \
		tan(data->cam.fov / 2 * M_PI / 180);
	ret.y = (y * (1 / data->height)) * tan(data->cam.fov / 2 * M_PI / 180);
	ret.z = 1;
	ray.o = mat4_get(data->cam.world, 3);
	ray.d = normalize(mat4_mult_dir(data->cam.world, ret));
	ray.max = INFINITY;
	return (ray);
}

int	ft_update(t_data *data)
{
	if (data->frame == 1)
		ft_ray(data);
	return (0);
}

void	ft_ray(t_data *data)
{
	t_v3		col;
	t_v3		origin;
	int			x;
	int			y;

	data->frame = 0;
	col = ret_vec("0.2,0.2,0.2");
	x = -(data->width / 2);
	while (x < (data->width / 2))
	{
		y = (data->height / 2);
		while (y > -(data->height / 2))
		{
			data->ray = get_direction(x, y, data);
			col = trace_ray(data->ray, data, data->reflection);
			my_mlx_pixel_put(data, (data->width / 2) + x, (data->height / 2) \
				- y, create_trgb(data->t, col.x, col.y, col.z));
			y--;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
