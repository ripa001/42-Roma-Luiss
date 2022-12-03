/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:16:20 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/30 18:42:44 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	*ft_get_pattern_addr(t_pattern pattern, float u, float v)
{
	int	x;
	int	y;

	x = (int)fmod(fmod(u, pattern.width) + pattern.width, pattern.width);
	y = (int)fmod(fmod(v, pattern.height) + pattern.height, pattern.height);
	x *= pattern.bits_per_pixel / 8;
	y *= pattern.size_line;
	return (pattern.addr + y + x);
}

t_v3	cross(t_v3 v1, t_v3 v2)
{
	t_v3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}
