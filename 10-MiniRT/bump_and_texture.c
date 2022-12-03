/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_and_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:37:52 by dripanuc          #+#    #+#             */
/*   Updated: 2022/11/01 18:04:13 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_get_uv(t_obj *obj, t_ray ray, float *u, float *v)
{
	t_v3	local;
	t_v3	ulocal;
	float	costheta;

	local = sub_vec(ray.hit_int, ray.d);
	ulocal = local;
	ulocal = normalize(ulocal);
	costheta = dot(ulocal, ft_vector_rotate_cw(ray.hit_int));
	*u = sqrt(dot(local, ulocal)) * costheta * 700;
	costheta = dot(ulocal, ft_vector_rotate_ccw(ray.hit_int));
	*v = sqrt(dot(local, ulocal)) * costheta * 700;
}

t_pattern	ft_get_pattern(t_data *data, char *filename)
{
	t_pattern	tmp;

	tmp.img = 0;
	tmp.addr = 0;
	if (filename)
		tmp.img = mlx_xpm_file_to_image(data->mlx, filename,
				&tmp.width, &tmp.height);
	if (tmp.img)
		tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel,
				&tmp.size_line, &tmp.endian);
	if (!tmp.img || !tmp.addr)
		printf("Failed to load %s pattern\n", filename);
	return (tmp);
}

t_v3	ft_bump_and_texture(t_ray ray, t_obj *c_obj, t_data *data)
{
	float		u;
	float		v;
	t_v3		col;

	ft_get_uv(c_obj, ray, &u, &v);
	if (!ft_strcmp(c_obj->id, "sp") && data->checkerboard)
		col = ft_checkerboard(c_obj, ray);
	else if (ft_strcmp(c_obj->id, "sp") && ft_strcmp(c_obj->id, "cy"))
		col = mult_vec(c_obj->rgb, compute_lighting(ray, \
			mult_vec_n(ray.d, -1), data, c_obj->spec));
	else if (!ft_strcmp(c_obj->id, "cy"))
	{
		col = ft_rgb_pattern(data->bump, u, v, 0.8);
		col = mult_vec(c_obj->rgb, ft_rgb2gray(col));
		col = mult_vec(col, compute_lighting(ray, \
				mult_vec_n(ray.d, -1), data, c_obj->spec));
	}
	else
	{
		col = ft_rgb_pattern(data->texture, u, v, 0.75);
		col = mult_vec(col, compute_lighting \
			(ray, mult_vec_n(ray.d, -1), data, c_obj->spec));
	}
	return (col);
}

t_v3	ft_checkerboard(t_obj *sphere, t_ray ray)
{
	double		v;
	double		u;
	double		theta;
	double		phi;
	t_v3		upd_ray;

	upd_ray = sub_vec(ray.hit, sphere->pos);
	theta = atan2(upd_ray.x, upd_ray.z);
	phi = acos(upd_ray.y / sphere->r);
	u = theta / (2 * M_PI);
	u = floor(10 * (1 - (u + 0.5)));
	v = floor(10 * (1 - (phi / M_PI)) / 2);
	if (fmod(u + v, 2) == 0)
		return ((t_v3) \
			{255 - sphere->rgb.x, 255 - sphere->rgb.y, 255 - sphere->rgb.z});
	else
		return (sphere->rgb);
}
