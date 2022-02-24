/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy_sup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:26 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 16:55:27 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_bool	move_left(t_enemy *enemy, t_game *game)
{
	if (enemy->tile->left->type == EMPTY)
		move_enemy_to(enemy, enemy->tile->left);
	else if (enemy->tile->left->type == PLAYER)
	{
		move_enemy_to(enemy, enemy->tile->left);
		kill_player(game, enemy->tile->position);
	}
	else
	{
		enemy->dir = 1;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	move_right(t_enemy *enemy, t_game *game)
{
	if (enemy->tile->right->type == EMPTY)
		move_enemy_to(enemy, enemy->tile->right);
	else if (enemy->tile->right->type == PLAYER)
	{
		move_enemy_to(enemy, enemy->tile->right);
		kill_player(game, enemy->tile->position);
	}
	else
	{
		enemy->dir = 0;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	move_up(t_enemy *enemy, t_game *game)
{
	if (enemy->tile->up->type == EMPTY)
		move_enemy_to(enemy, enemy->tile->up);
	else if (enemy->tile->up->type == PLAYER)
	{
		move_enemy_to(enemy, enemy->tile->up);
		kill_player(game, enemy->tile->position);
	}
	else
	{
		enemy->dir = 1;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	move_down(t_enemy *enemy, t_game *game)
{
	if (enemy->tile->down->type == EMPTY)
		move_enemy_to(enemy, enemy->tile->down);
	else if (enemy->tile->down->type == PLAYER)
	{
		move_enemy_to(enemy, enemy->tile->down);
		kill_player(game, enemy->tile->position);
	}
	else
	{
		enemy->dir = 0;
		return (FALSE);
	}
	return (TRUE);
}

int	dist(int x)
{
	if (x < 0)
		return (1);
	else if (x > 0)
		return (0);
	return (-1);
}
