/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:42:35 by dripanuc          #+#    #+#             */
/*   Updated: 2022/12/03 18:30:58 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_valid_obj(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	while ((line[i] >= '0' && line[i] <= '9') || \
		line[i] == 0 || line[i] == '\n')
		i--;
	data->sel_obj = ft_atoi(&line[++i]);
	if (data->sel_obj >= 1 && data->sel_obj <= data->nb_obj)
		return (1);
	return (0);
}

void	resize_obj(t_data *data)
{
	t_obj	*new;

	new = data->obj;
	printf("Resize: %f - ", data->resize);
	while (new)
	{
		if (new->n == data->sel_obj)
		{
			printf("Obj: %s\n", new->id);
			new->h *= data->resize;
			new->r *= data->resize;
			return ;
		}
		new = new->next;
	}
}

void	translate_obj(t_data *data)
{
	t_obj	*new;

	new = data->obj;
	while (new)
	{
		if (new->n == data->sel_obj)
		{
			new->pos = add_vec(new->pos, data->new_pos);
			return ;
		}
		new = new->next;
	}
}

void	ori_obj(t_data *data)
{
	t_obj	*new;

	new = data->obj;
	printf("Orientation: %f %f %f\n", data->ori_vec.x, \
			data->ori_vec.y, data->ori_vec.z);
	while (new)
	{
		if (new->n == data->sel_obj)
		{
			printf("Old Orientation : %f %f %f\n", new->ori.x, \
			new->ori.y, new->ori.z);
			new->ori = add_vec(new->ori, data->ori_vec);
			printf("New Orientation obj %s: %f %f %f\n\n", new->id, new->ori.x, \
			new->ori.y, new->ori.z);
			return ;
		}
		new = new->next;
	}
}
