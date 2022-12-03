/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:59:47 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/30 20:09:45 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	mat4_mult_scale(t_mat4x4 matrix, t_v3 to_scale)
{
	t_v3	new;

	new.x = to_scale.x * matrix.m[0][0] + to_scale.y
		* matrix.m[1][0] + to_scale.z * matrix.m[2][0];
	new.y = to_scale.x * matrix.m[0][1] + to_scale.y
		* matrix.m[1][1] + to_scale.z * matrix.m[2][1];
	new.z = to_scale.x * matrix.m[0][2] + to_scale.y
		* matrix.m[1][2] + to_scale.z * matrix.m[2][2];
	return (new);
}

t_v3	translation(t_v3 V, t_v3 scaling)
{
	t_mat4x4	m;

	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[1][3] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	m.m[2][3] = 0;
	m.m[3][0] = scaling.x;
	m.m[3][1] = scaling.y;
	m.m[3][2] = scaling.z;
	m.m[3][3] = 1;
	return (mat4_mult_dir(m, V));
}

// t_v3	mat4_mult_scale(t_mat4x4 matrix, t_v3 to_scale)
// {
// 	t_v3	new;

// 	new.x = to_scale.x * matrix.m[0][0] + to_scale.y
// 		* matrix.m[1][0] + to_scale.z * matrix.m[2][0];
// 	new.y = to_scale.x * matrix.m[0][1] + to_scale.y
// 		* matrix.m[1][1] + to_scale.z * matrix.m[2][1];
// 	new.z = to_scale.x * matrix.m[0][2] + to_scale.y
// 		* matrix.m[1][2] + to_scale.z * matrix.m[2][2];
// 	return (new);
// }

t_v3	scale(t_v3 V, t_v3 scaling)
{
	t_mat4x4	m;

	m.m[0][0] = scaling.x;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[0][3] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = scaling.y;
	m.m[1][2] = 0;
	m.m[1][3] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = scaling.z;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
	return (mat4_mult_scale(m, V));
}
