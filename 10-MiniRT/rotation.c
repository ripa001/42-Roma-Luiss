/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:56:44 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/24 11:18:06 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	rot_x(t_v3 to_rot, int angle)
{
	t_mat4x4	rot;
	float		rad;

	rad = (angle / 180) * M_PI;
	rot.m[0][0] = 1;
	rot.m[0][1] = 0;
	rot.m[0][2] = 0;
	rot.m[0][3] = 0;
	rot.m[1][0] = 0;
	rot.m[1][1] = cos(rad);
	rot.m[1][2] = -(sin(rad));
	rot.m[1][3] = 0;
	rot.m[2][0] = 0;
	rot.m[2][1] = sin(rad);
	rot.m[2][2] = cos(rad);
	rot.m[2][3] = 0;
	rot.m[3][0] = 0;
	rot.m[3][1] = 0;
	rot.m[3][2] = 0;
	rot.m[3][3] = 1;
	return (mult_vec_by_matrix(to_rot, rot.m));
}

t_v3	rot_y(t_v3 to_rot, int angle)
{
	t_mat4x4	rot;
	float		rad;

	rad = (angle / 180) * M_PI;
	rot.m[0][0] = cos(rad);
	rot.m[0][1] = 0;
	rot.m[0][2] = sin(rad);
	rot.m[0][3] = 0;
	rot.m[1][0] = 0;
	rot.m[1][1] = 1;
	rot.m[1][2] = 0;
	rot.m[1][3] = 0;
	rot.m[2][0] = -(sin(rad));
	rot.m[2][1] = 0;
	rot.m[2][2] = cos(rad);
	rot.m[2][3] = 0;
	rot.m[3][0] = 0;
	rot.m[3][1] = 0;
	rot.m[3][2] = 0;
	rot.m[3][3] = 1;
	return (mult_vec_by_matrix(to_rot, rot.m));
}

t_v3	rot_z(t_v3 to_rot, int angle)
{
	t_mat4x4	rot;
	float		rad;

	rad = (angle / 180) * M_PI;
	rot.m[0][0] = cos(rad);
	rot.m[0][1] = -(sin(rad));
	rot.m[0][2] = 0;
	rot.m[0][3] = 0;
	rot.m[1][0] = sin(rad);
	rot.m[1][1] = cos(rad);
	rot.m[1][2] = 0;
	rot.m[1][3] = 0;
	rot.m[2][0] = 0;
	rot.m[2][1] = 0;
	rot.m[2][2] = 1;
	rot.m[2][3] = 0;
	rot.m[3][0] = 0;
	rot.m[3][1] = 0;
	rot.m[3][2] = 0;
	rot.m[3][3] = 1;
	return (mult_vec_by_matrix(to_rot, rot.m));
}
