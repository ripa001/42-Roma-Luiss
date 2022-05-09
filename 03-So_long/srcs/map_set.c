/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:03:40 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:03:41 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_effect(t_game *game)
{
	if (game->effect.counter < game->effect.frames)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->effect.img,
			game->effect.pos.x, game->effect.pos.y);
}

void	draw_text(t_game *game)
{
	char	*str;

	str = ft_itoa(game->moves - 1);
	if (game->collects > 0)
		mlx_string_put(game->mlx, game->window.reference,
			game->wndw_size.x - IMG_SIZE / 2.3,
			IMG_SIZE - IMG_SIZE / 1.5,
			15859712, str);
	else
		mlx_string_put(game->mlx, game->window.reference,
			game->wndw_size.x - IMG_SIZE / 2.3,
			IMG_SIZE - IMG_SIZE / 1.5,
			65310, str);
	free(str);
}

void	put_enemy(t_game *game, t_tile tile)
{
	if (tile.type == ENEMY)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->enemy_imgs.basic_current, tile.position.x, tile.position.y);
	else if (tile.type == FOLLOWER)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->enemy_imgs.follow_current, tile.position.x, tile.position.y);
	else if (tile.type == TRAP)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->enemy_imgs.trap_current, tile.position.x, tile.position.y);
	else if (tile.type == PLAYER_TRAP)
	{
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->enemy_imgs.trap_current, tile.position.x, tile.position.y);
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->player.current_img, tile.position.x, tile.position.y);
	}
}

void	put_image(t_game *game, t_tile tile)
{
	if (tile.position.x == 0 || tile.position.y == 0
		|| tile.position.x == game->wndw_size.x - IMG_SIZE
		|| tile.position.y == game->wndw_size.y - IMG_SIZE)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->wall_bord, tile.position.x, tile.position.y);
	else if (tile.type == WALL)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->wall_img, tile.position.x, tile.position.y);
	else if (tile.type == COLLECTABLE)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->collects_imgs.current_img, tile.position.x, tile.position.y);
	else if (tile.type == PLAYER)
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->player.current_img, tile.position.x, tile.position.y);
	else if (tile.type == EXIT)
	{
		if (game->collects == 0)
			mlx_put_image_to_window(game->mlx, game->window.reference,
				game->door_open_img, tile.position.x, tile.position.y);
		else
			mlx_put_image_to_window(game->mlx, game->window.reference,
				game->door_close_img, tile.position.x, tile.position.y);
	}
	else
		put_enemy(game, tile);
}

void	put_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	mlx_clear_window(game->mlx, game->window.reference);
	while (game->tilemap[++y] != NULL)
	{
		x = 0;
		while (game->tilemap[y][x].type)
		{
			put_image(game, game->tilemap[y][x++]);
			draw_effect(game);
		}
	}
	draw_text(game);
}
