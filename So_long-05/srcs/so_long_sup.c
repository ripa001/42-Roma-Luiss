/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_sup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:56:03 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 17:11:26 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	win(t_game *game)
{
	mlx_clear_window(&game->mlx, game->window.reference);
		game->effect.img = mlx_xpm_file_to_image(&game->mlx,
			"sprites/respect.xpm",
			&game->img_size.x, &game->img_size.y);
	mlx_put_image_to_window(game->mlx, game->window.reference,
		game->effect.img,
		(game->wndw_size.x - 455) / 2,
		(game->wndw_size.y - 256) / 2);
}

int	update(t_game *game)
{
	if (game->collects != -1)
	{
		player_animation(&game->player);
		collec_animation(&game->collects_imgs);
		effect_animation(&game->effect);
		enemy_animation(&game->enemy_imgs);
		mlx_clear_window(&game->mlx, game->window.reference);
		put_map(game);
	}
	if (game->collects == -1)
	{
		win(game);
	}
	else if (game->player.tile == NULL)
	{
		mlx_clear_window(&game->mlx, game->window.reference);
		game->effect.img = mlx_xpm_file_to_image(&game->mlx,
				"sprites/wasted.xpm",
				&game->img_size.x, &game->img_size.y);
		mlx_put_image_to_window(game->mlx, game->window.reference,
			game->effect.img,
			(game->wndw_size.x - 530) / 2,
			(game->wndw_size.y - 256) / 2);
	}
	return (1);
}

int	ft_chartable_linecount(char **map)
{
	int	i;

	i = 0;
	while (*map++)
		i++;
	return (i);
}

t_mapchecks	init_checkerdata(char **map)
{
	t_mapchecks	data;

	data.size.x = ft_strlen(map[0]);
	data.size.y = ft_chartable_linecount(map);
	data.b_player = FALSE;
	data.b_exit = FALSE;
	data.b_collect = FALSE;
	data.point.y = 0;
	data.point.x = 0;
	return (data);
}
