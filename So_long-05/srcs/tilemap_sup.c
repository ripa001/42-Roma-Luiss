#include "../includes/so_long.h"

t_tiletype	define_tiletype(char type)
{
	if (type == '1')
		return (WALL);
	if (type == 'C')
		return (COLLECTABLE);
	if (type == 'P')
		return (PLAYER);
	if (type == 'E')
		return (EXIT);
	if (type == 'H' || type == 'V')
		return (ENEMY);
	else if (type == 'F')
		return (FOLLOWER);
	else if (type == 'T')
		return (TRAP);
	return (EMPTY);
}

t_tile	**allocate_tilemap(char **map)
{
	t_tile	**tilemap;

	if (!map)
		return (null_error("Errore mappa"));
	tilemap = alloc_tilemap(map);
	if (!tilemap)
		return (null_error("Errore malloc tilemap"));
	return (tilemap);
}

t_tile	**generate_tilemap(char **map, t_game *game)
{
	t_tile		**tilemap;
	int			x;
	int			y;

	tilemap = allocate_tilemap(map);
	y = 0;
	game->enemy_exist = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			tilemap[y][x].type = define_tiletype(map[y][x]);
			setup_tile(tilemap, x, y);
			set_gamevars(&tilemap[y][x], map[y][x], game);
			x++;
		}
		tilemap[y][x].type = 0;
		y++;
	}
	tilemap[y] = NULL;
	game->wndw_size.x = x * IMG_SIZE;
	game->wndw_size.y = y * IMG_SIZE;
	return (tilemap);
}
