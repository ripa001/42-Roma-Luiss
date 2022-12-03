/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:53:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/29 18:34:19 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_closest_light(double t, double max, t_data *data, t_obj *new)
{
	if ((t > 0.001 && t < max) || (t > 0.001 && t < max))
	{
		data->closest_t = t;
		return (1);
	}
	return (0);
}

t_obj	*cast_shadow(t_v3 o, t_v3 d, t_data *data, double max)
{
	t_obj		*closest_obj;
	t_obj		*new;
	double		t;

	new = data->obj;
	closest_obj = NULL;
	data->closest_t = INFINITY;
	t = INFINITY;
	while (new)
	{
		if (ft_strcmp(new->id, "sp") == 0)
			t = intersect_ray_sphere(o, d, new, t);
		else if (ft_strcmp(new->id, "pl") == 0)
			t = intersect_plane(o, d, new, t);
		else if (ft_strcmp(new->id, "cy") == 0)
			t = intersect_cylinder(o, d, new, t);
		else if (ft_strcmp(new->id, "cn") == 0)
			t = intersect_ray_cone(o, d, new, t);
		if (get_closest_light(t, max, data, new))
			closest_obj = new;
		new = new->next;
	}
	return (closest_obj);
}

void	compute_lighting3(t_ray ray, t_light *new, t_v3	arr[4], float s)
{
	float	n_dot_l;
	float	r_dot_v;

	n_dot_l = dot(ray.hit_int, arr[0]);
	if (n_dot_l > 0)
		arr[2] = add_vec(arr[2], mult_vec_n(new->rgb, new->ratio * n_dot_l / \
			(norm(arr[0]) * norm(ray.hit_int))));
	if (s != -1)
	{
		arr[1] = sub_vec(mult_vec_n(mult_vec_n(ray.hit_int, 2), \
			dot(ray.hit_int, arr[0])), arr[0]);
		r_dot_v = dot(arr[1], arr[3]);
		if (r_dot_v > 0)
			arr[2] = add_vec(arr[2], mult_vec_n(new->rgb, new->ratio * \
				pow(r_dot_v / (norm(arr[1]) * norm(arr[3])), s)));
	}
}

float	compute_lighting2(t_ray ray, t_light *new, t_v3	arr[4])
{
	float	max;

	if (new->t == 'L')
	{
		arr[0] = sub_vec(new->pos, ray.hit);
		max = 1;
	}
	else
	{
		max = INFINITY;
		arr[0] = normalize(new->pos);
	}
	return (max);
}

t_v3	compute_lighting(t_ray ray, t_v3 v, t_data *data, float s)
{
	float	i;
	t_v3	arr[4];
	float	dot_l;
	t_light	*new;
	float	max;

	i = 0.0;
	new = data->light;
	arr[3] = v;
	while (new)
	{
		if (new->t == 'A')
		arr[2] = mult_vec_n(new->rgb, new->ratio);
		else
		{
			max = compute_lighting2(ray, new, arr);
			if (cast_shadow(ray.hit, arr[0], data, max) == NULL)
				compute_lighting3(ray, new, arr, s);
		}
		new = new->next;
	}
	return (arr[2]);
}
