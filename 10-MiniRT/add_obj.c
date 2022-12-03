/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:55:53 by mcipolla          #+#    #+#             */
/*   Updated: 2022/11/18 11:57:34 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*add_sphere(char **args)
{
	t_obj	*new;

	if (ft_arraylen(args) < 4 || ft_arraylen(args) > 6)
		exit(ft_error("Error\nInvalid sphere"));
	new = malloc(sizeof(t_obj));
	new->id = ft_strdup(args[0]);
	new->pos = ret_vec(args[1]);
	new->r = ft_atof(args[2]) / 2;
	new->rgb = div_vec_n(ret_vec(args[3]), 255);
	if (args[4])
		new->spec = ft_atof(args[4]);
	else
		new->spec = -1;
	if (args[5])
		new->reflect = ft_atof(args[5]);
	else
		new->reflect = 0;
	return (new);
}

t_obj	*add_plane(char **args)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (ft_arraylen(args) < 5 || ft_arraylen(args) > 6)
		exit(ft_error("Error\nInvalid plane"));
	new->id = ft_strdup(*args);
	new->pos = ret_vec(args[1]);
	new->ori = ret_vec(args[2]);
	new->rgb = div_vec_n(ret_vec(args[3]), 255);
	if (args[4])
		new->spec = ft_atof(args[4]);
	else
		new->spec = -1;
	if (args[5])
		new->reflect = ft_atof(args[5]);
	else
		new->reflect = 0;
	return (new);
}

t_obj	*add_cyl(char **args)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	new->id = ft_strdup(args[0]);
	new->pos = ret_vec(args[1]);
	new->ori = normalize(ret_vec(args[2]));
	new->r = ft_atof(args[3]);
	new->h = ft_atof(args[4]);
	new->rgb = div_vec_n(ret_vec(args[5]), 255);
	if (args[6])
		new->spec = ft_atof(args[6]);
	else
		new->spec = -1;
	if (args[7])
		new->reflect = ft_atof(args[7]);
	else
		new->reflect = 0;
	return (new);
}

t_obj	*add_cone(char **args)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	new->id = ft_strdup(args[0]);
	new->pos = ret_vec(args[1]);
	new->ori = normalize(ret_vec(args[2]));
	new->r = ft_atof(args[3]);
	new->h = ft_atof(args[4]);
	new->rgb = div_vec_n(ret_vec(args[5]), 255);
	if (args[6])
		new->spec = ft_atof(args[6]);
	else
		new->spec = -1;
	if (args[7])
		new->reflect = ft_atof(args[7]);
	else
		new->reflect = 0;
	return (new);
}
