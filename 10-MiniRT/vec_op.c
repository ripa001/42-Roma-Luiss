/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/30 18:27:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	reflect_ray(t_v3 R, t_v3 N)
{
	return (sub_vec(mult_vec_n(mult_vec_n(N, 2), dot(N, R)), R));
}

float	dot(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	norm(t_v3 v1)
{
	return (sqrtf(dot(v1, v1)));
}

t_v3	add_vec(t_v3 v1, t_v3 v2)
{
	t_v3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_v3	normalize(t_v3 v1)
{
	t_v3	ret;
	float	magnitude;

	magnitude = norm(v1);
	ret.x = v1.x / magnitude;
	ret.y = v1.y / magnitude;
	ret.z = v1.z / magnitude;
	return (ret);
}
