/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:00:01 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:00:02 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_enemy_to(t_enemy *enemy, t_tile *pos)
{
	enemy->tile->type = EMPTY;
	if (enemy->type == FOLLOW_ENEM)
		pos->type = FOLLOWER;
	else
		pos->type = ENEMY;
	enemy->tile = pos;
}

void	kill_player(t_game *game, t_vector pos)
{
	game->player.tile = NULL;
	effect_anim(&game->effect, pos);
}

t_bool	move_hor(t_enemy *enemy, t_game *game)
{
	if (enemy->dir == 0)
		return (move_left(enemy, game));
	else
		return (move_right(enemy, game));
}

t_bool	move_ver(t_enemy *enemy, t_game *game)
{
	if (enemy->dir == 0)
		return (move_up(enemy, game));
	else
		return (move_down(enemy, game));
}

void	move_follow(t_enemy *enemy, t_game *game)
{
	int	x;
	int	y;

	x = enemy->tile->position.x - game->player.tile->position.x;
	y = enemy->tile->position.y - game->player.tile->position.y;
	if (x < y)
	{
		enemy->dir = dist(x);
		if (!move_hor(enemy, game) || enemy->dir == -1)
		{
			enemy->dir = dist(y);
			move_ver(enemy, game);
		}
	}
	else
	{
		enemy->dir = dist(y);
		if (!move_ver(enemy, game) || enemy->dir == -1)
		{
			enemy->dir = dist(x);
			move_hor(enemy, game);
		}
	}
}
