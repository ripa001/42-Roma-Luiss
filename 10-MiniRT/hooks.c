/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:03:34 by dripanuc          #+#    #+#             */
/*   Updated: 2022/12/03 18:30:31 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_prints(void)
{
	ft_putstr_fd("Inserire 'R <percentuale> <n_obj>' per il resize\n", 1);
	ft_putstr_fd("Inserire 'V <x>,<y>,<z> <n_obj>' per il translate\n", 1);
	ft_putstr_fd("Inserire 'O <x>,<y>,<z> <n_obj>' per l'orientation\n", 1);
	ft_putendl_fd("n_obj corrisponde all'oggetto da aggiornare\n", 1);
}

char	*parse_line(char *line, t_data *data)
{
	ft_prints();
	line = get_next_line(0);
	if (line)
	{
		while (line && *line != 'R' && *line != 'V' && *line != 'O')
			line++;
		ft_putendl_fd(line, 1);
		if (line && *line == 'R' && check_valid_obj(data, line))
			data->resize = ft_atof(++line) / 100;
		else if (line && *line == 'O' && check_valid_obj(data, line))
			data->ori_vec = div_vec_n(ret_vec(++line), 90);
		else if (line && *line == 'V' && check_valid_obj(data, line))
			data->new_pos = ret_vec(++line);
		else
			ft_putendl_fd("Not valid input, retry by pressing letter T", 1);
	}
	if (data->resize)
		resize_obj(data);
	if (data->ori_vec.x > 0)
		ori_obj(data);
	if (data->new_pos.x > 0)
		translate_obj(data);
	return (line);
}

void	get_keycode2(int keycode, t_data *data)
{
	char	*line;

	line = 0;
	if (keycode == 125)
		data->cam.ori.y -= 0.1;
	else if (keycode == 126)
		data->cam.ori.y += 0.1;
	else if (keycode == 12)
		data->cam.pos.z -= 0.5;
	else if (keycode == 14)
		data->cam.pos.z += 0.5;
	else if (keycode == 17)
		parse_line(line, data);
	else if (keycode == 8)
	{
		if (data->checkerboard)
			data->checkerboard = 0;
		else
			data->checkerboard = 1;
	}
}

void	get_keycode(int keycode, t_data *data)
{
	if (keycode == 1)
		data->cam.pos.y -= 0.5;
	else if (keycode == 13)
		data->cam.pos.y += 0.5;
	else if (keycode == 0)
		data->cam.pos.x -= 0.5;
	else if (keycode == 2)
		data->cam.pos.x += 0.5;
	else if (keycode == 69)
		data->cam.fov -= 3;
	else if (keycode == 78)
		data->cam.fov += 3;
	else if (keycode == 123)
		data->cam.ori.x -= 0.1;
	else if (keycode == 124)
		data->cam.ori.x += 0.1;
	else
		get_keycode2(keycode, data);
}

int	ft_hooks(int keycode, t_data *data)
{
	data->resize = 0;
	data->ori_vec.x = -1;
	data->ori_vec.y = -1;
	data->ori_vec.z = -1;
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	get_keycode(keycode, data);
	data->cam.view_range = tan((data->cam.fov * 0.5) * (M_PI / 180));
	data->cam.world = look_at(data->cam.pos, \
		add_vec(data->cam.pos, data->cam.ori));
	mlx_clear_window(data->mlx, data->mlx_win);
	data->frame = 1;
	return (0);
}
