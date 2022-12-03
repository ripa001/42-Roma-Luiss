/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/11/18 11:57:54 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	*last_light(t_light *light)
{
	if (!light)
		return (NULL);
	while (light->next)
		light = light->next;
	return (light);
}

void	add_light(char	**args, t_data *data)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	new->t = args[0][0];
	if (args[0][0] == 'A')
		new->ratio = ft_atof(args[1]);
	else
	{
		new->pos = ret_vec(args[1]);
		new->ratio = ft_atof(args[2]);
	}
	if (args[0][0] == 'A')
		new->rgb = div_vec_n(ret_vec(args[2]), 255);
	else
		new->rgb = div_vec_n(ret_vec(args[3]), 255);
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->light == NULL)
		data->light = new;
	else
		last_light(data->light)->next = new;
}

t_obj	*last_obj(t_obj	*obj)
{
	if (!obj)
		return (NULL);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

void	add_obj(char **args, t_data *data)
{
	t_obj		*new;
	static int	n;

	if (!(ft_strcmp(args[0], "sp")))
		new = add_sphere(args);
	else if (!(ft_strcmp(args[0], "pl")))
		new = add_plane(args);
	else if (!(ft_strcmp(args[0], "cy")))
		new = add_cyl(args);
	else if (!(ft_strcmp(args[0], "cn")))
		new = add_cone(args);
	new->n = ++n;
	data->nb_obj = n;
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->obj == NULL)
		data->obj = new;
	else
		last_obj(data->obj)->next = new;
}
