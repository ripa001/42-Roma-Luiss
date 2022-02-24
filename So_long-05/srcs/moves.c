/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:00:27 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:28 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_to_empty(t_game *game, t_tile *tile)
{
	tile->type = PLAYER;
	if (game->player.tile->type == PLAYER_TRAP)
		game->player.tile->type = TRAP;
	else if (game->player.tile->type != EXIT)
		game->player.tile->type = EMPTY;
	game->player.tile = tile;
}

void	move_to_exit(t_game *game, t_tile *tile)
{
	effect_anim(&game->effect, tile->position);
	remove_player(game);
	game->collects = -1;
}

void	pick_collect(t_game *game, t_tile *tile)
{
	tile->type = EMPTY;
	game->collects--;
	effect_anim(&game->effect, tile->position);
	action_anim(&game->player);
	move_to_empty(game, tile);
}

void	move_to_trap(t_game *game, t_tile *tile)
{
	int	moves;

	moves = game->moves % 3;
	if (!moves)
		kill_player(game, tile->position);
	else
	{
		tile->type = PLAYER_TRAP;
		if (game->player.tile->type != EXIT)
			game->player.tile->type = EMPTY;
		game->player.tile = tile;
	}
}

t_bool	move_to(t_game *game, t_tile *tile)
{
	if (tile->type == EMPTY)
		move_to_empty(game, tile);
	else if (tile->type == COLLECTABLE)
		pick_collect(game, tile);
	else if (tile->type == EXIT && game->collects == 0)
		move_to_exit(game, tile);
	else if (tile->type == TRAP)
		move_to_trap(game, tile);
	else if (tile->type == ENEMY || tile->type == FOLLOWER)
		kill_player(game, tile->position);
	else
		return (FALSE);
	if (game->enemy_exist && game->player.tile != NULL)
		move_enemies(game);
	return (TRUE);
}
