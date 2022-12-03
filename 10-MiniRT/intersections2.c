/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:48:01 by dripanuc          #+#    #+#             */
/*   Updated: 2022/10/29 19:06:16 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_closest(double t, t_data *data, float min, double max)
{
	if (t >= min && t < data->closest_t)
	{
		data->closest_t = t;
		return (1);
	}
	return (0);
}

t_obj	*closest_intersect(t_ray ray, t_data *data, float min, float max)
{
	t_obj		*closest_obj;
	t_obj		*new;
	float		t;

	new = data->obj;
	closest_obj = 0;
	data->closest_t = INFINITY;
	t = INFINITY;
	while (new)
	{
		if (ft_strcmp(new->id, "sp") == 0)
			t = intersect_ray_sphere(ray.o, ray.d, new, t);
		else if (ft_strcmp(new->id, "pl") == 0)
			t = intersect_plane(ray.o, ray.d, new, t);
		else if (ft_strcmp(new->id, "cy") == 0)
			t = intersect_cylinder(ray.o, ray.d, new, t);
		else if (ft_strcmp(new->id, "cn") == 0)
			t = intersect_ray_cone(ray.o, ray.d, new, t);
		if (get_closest(t, data, min, max))
			closest_obj = new;
		new = new->next;
	}
	return (closest_obj);
}

float	intersect_ray_sphere(t_v3 O, t_v3 D, t_obj *sphere, float t)
{
	float	a;
	float	b;
	float	c;
	float	ret;

	a = dot(D, D);
	b = 2 * dot(sub_vec(O, sphere->pos), D);
	c = dot(sub_vec(O, sphere->pos), sub_vec(O, sphere->pos)) \
		- (sphere->r * sphere->r);
	ret = b * b - (4 * a * c);
	if (ret < 0.001)
		t = INFINITY;
	else
	{
		c = (-b + sqrtf(ret)) / (2 * a);
		t = ((-b - sqrtf(ret)) / (2 * a));
		if (c < t)
			t = c;
	}
	return (t);
}
