#include "includes/so_long.h"

int	valid_file(char *file, int argc)
{
	if (!ft_strnstr(file + ft_strlen(file) - 4, ".ber", ft_strlen(file)))
		return (error("Il file mappa deve avere un'estenzione .ber"));
	if (argc > 2)
		return (error("Solo il primo file verrà considerato"));
	if (argc == 1)
		return (error("Inserire una mappa"));
	return (1);
}

int	valid_char(char c, char *s)
{
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}

int	valid_unique_char(char c, char s, t_bool *bool)
{
	if (c == s && *bool == FALSE)
		*bool = TRUE;
	else if (c == s && *bool == TRUE)
		return (FALSE);
	return (TRUE);
}

int	valid_border(char c, t_vector point, t_vector size)
{
	if (point.y == 0 || point.x == 0
		|| point.y == size.y - 1 || point.x == size.x - 1)
		if (c != '1')
			return (FALSE);
	return (TRUE);
}

int	valid_map(char **map, t_mapchecks *data)
{
	t_bool	valid;
	int		y;
	int		x;

	valid = TRUE;
	y = data->point.y;
	x = data->point.x;
	if (!valid_char(map[y][x], "01CPTVHDEF"))
		return (error("I caratteri ammessi nella mappa sono 01CPET"));
	if (!valid_unique_char(map[y][x], 'P', &data->b_player))
		return (error("Può esistere un solo player 'P'"));
	if (map[y][x] == 'E')
		data->b_exit = TRUE;
	if (!valid_border(map[y][x], data->point, data->size))
		return (error("La mappa deve essere circondata da '1'"));
	if (map[y][x] == 'C')
		data->b_collect = TRUE;
	return (1);
}
