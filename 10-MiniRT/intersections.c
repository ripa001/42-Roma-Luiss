/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:48:01 by dripanuc          #+#    #+#             */
/*   Updated: 2022/10/29 18:53:43 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	intersect_ray_cone2(t_v3 O, t_v3 D, t_obj *cn, float arr_float[7])
{
	float	t_arr[2];
	float	t;

	t = sqrt(arr_float[6]);
	t_arr[0] = (-arr_float[3] - t) / (2 * arr_float[2]);
	t_arr[1] = (-arr_float[3] + t) / (2 * arr_float[2]);
	if (t_arr[0] > t_arr[1])
		t = t_arr[0];
	else
		t = t_arr[1];
	return (find_edges_cone(cn, O, D, t_arr));
}

float	intersect_ray_cone(t_v3 O, t_v3 D, t_obj *cn, float t)
{
	float	arr_float[7];
	t_v3	theta;
	t_v3	w;

	theta = vec_normalize(cn->ori);
	arr_float[5] = tan(pow(cn->r / cn->h, 2));
	w = sub_vec(O, cn->pos);
	arr_float[0] = dot(D, theta);
	arr_float[1] = dot(w, theta);
	arr_float[2] = pow(arr_float[0], 2);
	arr_float[2] = dot(D, D) - arr_float[5] * arr_float[2] - arr_float[2];
	arr_float[3] = 2 * (dot(D, w) - arr_float[5] * arr_float[0] * \
		arr_float[1] - arr_float[0] * arr_float[1]);
	arr_float[4] = dot(w, w) - arr_float[5] * \
		pow(arr_float[1], 2) - pow(arr_float[1], 2);
	t = pow(arr_float[3], 2) - (4 * arr_float[2] * arr_float[4]);
	if (t < 0)
		return (INFINITY);
	arr_float[6] = t;
	return (intersect_ray_cone2(O, D, cn, arr_float));
}

float	intersect_cylinder(t_v3 O, t_v3 D, t_obj *cyl, float t)
{
	t_v3	inter;
	float	ret;
	t_v3	r;
	t_v3	c_to_o;
	float	t_arr[2];

	r = cross(D, cyl->ori);
	c_to_o = sub_vec(O, cyl->pos);
	inter.x = dot(r, r);
	inter.y = 2 * dot(r, cross(c_to_o, cyl->ori));
	inter.z = dot(cross(c_to_o, cyl->ori), cross(c_to_o, cyl->ori)) \
		- pow(cyl->r, 2);
	ret = (inter.y * inter.y - (4 * inter.x * inter.z));
	if (ret < 0)
		return (INFINITY);
	t_arr[0] = ((-inter.y - sqrtf(ret)) / (2 * inter.x));
	t_arr[1] = ((-inter.y + sqrtf(ret)) / (2 * inter.x));
	return (find_edges(cyl, O, D, t_arr));
}

float	intersect_plane(t_v3 O, t_v3 D, t_obj *plane, float t)
{
	float	denom;

	denom = dot(plane->ori, plane->ori);
	t = -(denom + dot(O, plane->ori)) / dot(D, plane->ori);
	if (t > 1e-4)
		return (t);
	return (INFINITY);
}
