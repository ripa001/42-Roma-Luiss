#include "../includes/so_long.h"

void	setup_tile(t_tile **tilemap, int x, int y)
{
	tilemap[y][x].og_type = tilemap[y][x].type;
	tilemap[y][x].position.x = x * IMG_SIZE;
	tilemap[y][x].position.y = y * IMG_SIZE;
	if (y != 0)
		tilemap[y][x].up = &tilemap[y - 1][x];
	if (tilemap[y + 1] != NULL)
		tilemap[y][x].down = &tilemap[y + 1][x];
	if (x != 0)
		tilemap[y][x].left = &tilemap[y][x - 1];
	tilemap[y][x].right = &tilemap[y][x + 1];
}

t_tile	**alloc_tilemap(char **map)
{
	t_tile	**tilemap;
	int		i;

	tilemap = malloc(sizeof(t_tile *) * ft_chartable_linecount(map) + 1);
	if (!tilemap)
		return (NULL);
	i = 0;
	while (map[i] != NULL)
	{
		tilemap[i] = malloc(sizeof(t_tile) * ft_strlen(*map) + 1);
		if (!tilemap[i])
		{
			while (i > 0)
				free(tilemap[--i]);
			return (NULL);
		}
		i++;
	}
	return (tilemap);
}

t_enemy	*last_enemy(t_enemy *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	add_enemy(t_game *game, t_enemytype c, t_tile *tile)
{
	t_enemy	*new;

	new = malloc(sizeof(t_enemy));
	if (new == NULL)
		return (error("Malloc error creazione nemico"));
	game->enemy_exist = 1;
	new->type = c;
	new->tile = tile;
	new->dir = 0;
	new->og_tile = tile;
	new->next = NULL;
	if (game->enemy_list == NULL)
		game->enemy_list = new;
	else
		last_enemy(game->enemy_list)->next = new;
	return (1);
}

void	set_gamevars(t_tile *tile, t_enemytype c, t_game *game)
{
	if (tile->type == PLAYER)
		game->player.tile = tile;
	else if (tile->type == COLLECTABLE)
		game->collects++;
	else if (tile->type == ENEMY || tile->type == FOLLOWER
		|| tile->type == TRAP)
		add_enemy(game, c, tile);
}
