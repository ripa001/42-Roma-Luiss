/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:29:59 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/29 18:55:25 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	mat4_get(t_mat4x4 m4, int get)
{
	if (get == 0)
		return ((t_v3){m4.m[0][0], m4.m[0][1], m4.m[0][2]});
	if (get == 1)
		return ((t_v3){m4.m[1][0], m4.m[1][1], m4.m[1][2]});
	if (get == 2)
		return ((t_v3){m4.m[2][0], m4.m[2][1], m4.m[2][2]});
	if (get == 3)
		return ((t_v3){m4.m[3][0], m4.m[3][1], m4.m[3][2]});
	return (ret_vec("0,0,0"));
}

t_v3	mat4_mult_dir(t_mat4x4 matrix, t_v3 dir)
{
	t_v3	new;

	new.x = dir.x * matrix.m[0][0] + dir.y
		* matrix.m[1][0] + dir.z * matrix.m[2][0];
	new.y = dir.x * matrix.m[0][1] + dir.y
		* matrix.m[1][1] + dir.z * matrix.m[2][1];
	new.z = dir.x * matrix.m[0][2] + dir.y
		* matrix.m[1][2] + dir.z * matrix.m[2][2];
	return (new);
}

t_v3	mult_vec_by_matrix(t_v3 vec, float matrix[4][4])
{
	t_v3	ret;

	ret.x = vec.x * matrix[0][0] + vec.y * matrix[1][0] + \
		vec.z * matrix[2][0] + matrix[3][0] * 0;
	ret.y = vec.x * matrix[0][1] + vec.y * matrix[1][1] + \
		vec.z * matrix[2][1] + matrix[3][1] * 0;
	ret.z = vec.x * matrix[0][2] + vec.y * matrix[1][2] + \
		vec.z * matrix[2][2] + matrix[3][2] * 0;
	return (ret);
}

t_mat4x4	mat4x4(t_v3 origin, t_v3 forward, t_v3 right, t_v3 up)
{
	t_mat4x4		coords;

	coords.m[0][0] = right.x;
	coords.m[0][1] = right.y;
	coords.m[0][2] = right.z;
	coords.m[0][3] = 0;
	coords.m[1][0] = up.x;
	coords.m[1][1] = up.y;
	coords.m[1][2] = up.z;
	coords.m[1][3] = 0;
	coords.m[2][0] = forward.x;
	coords.m[2][1] = forward.y;
	coords.m[2][2] = forward.z;
	coords.m[2][3] = 0;
	coords.m[3][0] = origin.x;
	coords.m[3][1] = origin.y;
	coords.m[3][2] = origin.z;
	coords.m[3][3] = 1;
	return (coords);
}

float	**rot_matrix(t_v3 rot, t_v3 dir)
{
	float	**matrix;
	int		i;
	t_v3	ret;
	float	angle;

	i = -1;
	matrix = (float **)malloc(sizeof(float *) * 3);
	while (++i < 4)
		matrix[i] = malloc(sizeof(float) * 3);
	matrix[0][0] = cos(rot.y * M_PI) * cos(rot.z * M_PI);
	matrix[0][1] = cos(rot.z * M_PI) * sin(rot.x * M_PI) * sin(rot.y * M_PI) \
		- cos(rot.x * M_PI) * sin(rot.z * M_PI);
	matrix[0][2] = cos(rot.x * M_PI) * cos(rot.y * M_PI) * sin(rot.x * M_PI) \
		+ sin(rot.x * M_PI) * sin(rot.z * M_PI);
	matrix[1][0] = cos(rot.y * M_PI) * sin(rot.z * M_PI);
	matrix[1][1] = cos(rot.x * M_PI) * cos(rot.y * M_PI) + sin(rot.x * M_PI) \
		* sin(rot.y * M_PI) * sin(rot.z * M_PI);
	matrix[1][2] = cos(rot.x * M_PI) * sin(rot.y * M_PI) * sin(rot.z * M_PI) \
		- cos(rot.z * M_PI) * sin(rot.x * M_PI);
	matrix[2][0] = -sin(rot.y * M_PI);
	matrix[2][1] = cos(rot.y * M_PI) * sin(rot.x * M_PI);
	matrix[2][2] = cos(rot.x * M_PI) * cos(rot.y * M_PI);
	return (matrix);
}
