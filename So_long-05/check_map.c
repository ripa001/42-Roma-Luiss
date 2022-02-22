#include "includes/so_long.h"

char	**map_alloc(int fd)
{
	char	*line;
	int		i;
	char	**map;

	line = get_next_line(fd);
	i = 0;
	while (line != NULL && *line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!map)
		return (0);
	map[i] = 0;
	return (map);
}

void	sup_read(char **map, char *line, int fd)
{
	int		i;
	char	*temp;

	i = 0;
	while (line != NULL && *line)
	{
		temp = line;
		line = get_next_line(fd);
		if (line != NULL)
			map[i] = ft_substr(temp, 0, ft_strlen(temp) - 1);
		else
			map[i] = ft_substr(temp, 0, ft_strlen(temp));
		i++;
		free(temp);
	}
}

char	**readmap(char *file)
{
	char	*line;
	char	**map;
	int		fd;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (0);
	map = map_alloc(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (!map)
		return (0);
	line = get_next_line(fd);
	sup_read(map, line, fd);
	close(fd);
	return (map);
}

char	**sup_check(char **map, t_mapchecks *data)
{
	while (map[data->point.y])
	{
		if (ft_strlen(map[data->point.y]) != data->size.x)
		{
			error("La mappa deve essere rettangolare");
			return (0);
		}
		data->point.x = 0;
		while (map[data->point.y][data->point.x])
		{	
			if (valid_map(map, data) == FALSE)
			{
				error("Verifica che la tua mappa sia corretta!");
				return (0);
			}
			data->point.x++;
		}
		data->point.y++;
	}
	return (map);
}

char	**checks(char *file, int argc)
{
	t_mapchecks	data;
	char		**map;

	if (argc < 2)
	{
		error("Inserire il path alla mappa.");
		return (0);
	}
	if (!valid_file(file, argc))
		return (0);
	map = readmap(file);
	if (!map)
	{
		free_matrix(map);
		return (0);
	}
	data = init_checkerdata(map);
	map = sup_check(map, &data);
	if (!data.b_player || !data.b_exit || !data.b_collect)
	{
		error("Deve esserci almeno una 'P', una 'E', e una 'C'");
		return (0);
	}
	return (map);
}
