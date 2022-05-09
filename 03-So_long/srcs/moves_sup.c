/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_sup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:00:05 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:05 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	effect_anim(t_effect *effect, t_vector pos)
{
	effect->counter = 0;
	effect->pos = pos;
}

void	action_anim(t_player *player)
{
	player->framecount = 0;
	player->current_img = player->action_img;
}

void	remove_player(t_game *game)
{
	game->player.tile->type = EMPTY;
	game->player.tile = NULL;
}
