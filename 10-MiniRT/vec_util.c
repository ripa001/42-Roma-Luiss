/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:15:26 by dripanuc          #+#    #+#             */
/*   Updated: 2022/10/30 18:43:44 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	ft_get_rgb_vec(float x, float y, float z)
{
	t_v3	tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}

t_v3	ft_rgb2gray(t_v3 rgb)
{
	unsigned char	gray;

	rgb = mult_vec_n(rgb, 255);
	gray = 0.299 * rgb.x + 0.587 * rgb.y + 0.114 * rgb.z;
	return (div_vec_n(ft_get_rgb_vec(gray, gray, gray), 255));
}

t_v3	ft_rgb_pattern(t_pattern pattern, double u, double v, float brigh)
{
	t_v3	tmp;
	void	*color;

	brigh += 1;
	if (brigh > 1)
		brigh = 1;
	if (brigh < 0)
		brigh = 0;
	color = ft_get_pattern_addr(pattern, u, v);
	tmp = ft_get_rgb_vec((*(unsigned int *) color & 0x00ff0000) >> 16,
			(*(unsigned int *) color & 0x0000ff00) >> 8,
			(*(unsigned int *) color & 0x000000ff));
	tmp = ft_rgb_brightness_adjustment(tmp, brigh);
	return (tmp);
}

int	create_trgb(float t, float r, float g, float b)
{
	r *= 255;
	g *= 255;
	b *= 255;
	return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

t_v3	ft_rgb_brightness_adjustment(t_v3 rgb, float adjust)
{
	rgb.x *= adjust;
	rgb.y *= adjust;
	rgb.z *= adjust;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (div_vec_n(rgb, 255));
}
