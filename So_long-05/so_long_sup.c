#include "includes/so_long.h"

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
		mlx_string_put(game->mlx, game->window.reference,
			game->wndw_size.x/ 2,
			game->wndw_size.y / 2,
			15859712, "RESPECT +");
	if (game->player.tile == NULL)
		mlx_string_put(game->mlx, game->window.reference,
			game->wndw_size.x/ 2,
			game->wndw_size.y / 2,
			15859712, "WASTED");
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
