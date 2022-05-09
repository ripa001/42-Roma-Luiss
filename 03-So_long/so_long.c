/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:32 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 16:58:59 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	free_matrix(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
	return (0);
}

void	setup_animation(t_game *game)
{
	game->collects_imgs.anim_frames = 25;
	game->player.idle_frames = 17;
	game->player.action_frames = 10;
	game->effect.frames = 10;
	game->enemy_imgs.basic_anim = 16;
	game->enemy_imgs.follow_anim = 6;
	game->enemy_imgs.trap_anim = 3;
	game->effect.counter = 8;
	game->moves = 1;
}

void	move_enemies(t_game *game)
{
	t_enemy	*current;
	int		trap;

	current = game->enemy_list;
	trap = 0;
	while (TRUE)
	{
		if (current->type == HORIZONTAL_ENEM)
			move_hor(current, game);
		else if (current->type == VERTICAL_ENEM)
			move_ver(current, game);
		else if (current->type == FOLLOWER)
			move_follow(current, game);
		else if (current->type == TRAP)
			trap_animation(game, &game->enemy_imgs, &trap);
		if (!current->next)
			break ;
		current = current->next;
	}
}

int	input(int key, t_game *game)
{
	t_bool	moved;

	moved = 0;
	if (key == ESC)
		end_program(game);
	if (game->collects != -1)
	{
		if (key == KEY_UP && !(game->player.tile == NULL))
			moved = move_to(game, game->player.tile->up);
		else if (key == KEY_DOWN && !(game->player.tile == NULL))
			moved = move_to(game, game->player.tile->down);
		else if (key == KEY_LEFT && !(game->player.tile == NULL))
			moved = move_to(game, game->player.tile->left);
		else if (key == KEY_RIGHT && !(game->player.tile == NULL))
			moved = move_to(game, game->player.tile->right);
		else
			return (0);
		if (moved)
			printf("Mosse -> %02d\n", game->moves++);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	char	**matrix;

	matrix = checks(argv[1], argc);
	if (!matrix)
		return (0);
	game.tilemap = generate_tilemap(matrix, &game);
	free_matrix(matrix);
	setup_animation(&game);
	game = get_images(&game);
	game.mlx = mlx_init();
	game.window = ft_new_window(game.mlx, game.wndw_size.x,
			game.wndw_size.y, "So long!");
	mlx_hook(game.window.reference, 2, 0, input, (void *)&game);
	mlx_loop_hook(game.mlx, update, (void *)&game);
	mlx_loop(game.mlx);
}
