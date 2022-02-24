/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:00:22 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:22 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "basics.h"

typedef struct s_mapchecks
{
	t_vector	size;
	t_vector	point;
	t_bool		b_player;
	t_bool		b_exit;
	t_bool		b_collect;
}				t_mapchecks;

int		valid_file(char *file, int argc);
char	**readmap(char *file);
int		valid_map(char **map, t_mapchecks *data);
// void	add_enemy(t_game *game, t_enemyytpe type, t_tile *tile);

#endif
