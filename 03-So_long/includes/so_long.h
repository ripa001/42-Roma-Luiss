/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:59:07 by dripanuc          #+#    #+#             */
/*   Updated: 2022/02/23 16:59:07 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include "../my_lib/gnl/get_next_line.h"
# include "../my_lib/libft/libft.h"
# include "map.h"
# include "type.h"

# define IMG_SIZE 64

typedef struct s_window {
	void		*reference;
	t_vector	size;
}t_window;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}t_color;

enum e_keycode
{
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	RESET = 15,
	ESC = 53
};

typedef struct s_image {
	void		*reference;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_enemy
{
	t_enemytype			type;
	int					dir;
	t_tile				*og_tile;
	t_tile				*tile;
	struct s_enemy		*next;
}	t_enemy;

typedef struct s_player
{
	t_tile	*tile;
	void	*current_img;
	int		framecount;
	int		idle_frames;
	void	*idle_img_0;
	void	*idle_img_1;
	int		action_frames;
	void	*action_img;
}	t_player;

typedef struct s_game
{
	void			*mlx;
	t_window		window;
	t_vector		wndw_size;
	t_tile			**tilemap;
	t_player		player;
	int				og_collects;
	int				collects;
	int				moves;
	t_enemy			*enemy_list;
	t_vector		img_size;
	void			*wall_img;
	void			*wall_bord;
	t_collect_img	collects_imgs;
	t_enemy_img		enemy_imgs;
	void			*door_open_img;
	void			*door_close_img;
	t_effect		effect;
	void			*red_panel;
	void			*white_panel;
	int				enemy_exist;
}	t_game;

t_color		new_color(int r, int g, int b, int a);
void		turn_pixel_to_color(char *pixel, t_color color);
void		turn_img_to_color(t_image *image, t_color color);
t_window	ft_new_window(void *mlx, int widht, int height, char *name);
t_tile		**generate_tilemap(char **map, t_game *game);
int			ft_chartable_linecount(char **map);
void		effect_anim(t_effect *effect, t_vector pos);
void		action_anim(t_player *player);
void		remove_player(t_game *game);
void		move_to_empty(t_game *game, t_tile *tile);
void		move_to_exit(t_game *game, t_tile *tile);
void		pick_collect(t_game *game, t_tile *tile);
t_bool		move_to(t_game *game, t_tile *tile);
void		*new_panel(t_game *game, t_color color);
void		draw_effect(t_game *game);
void		effect_animation(t_effect *effect);
void		set_gamevars(t_tile *tile, t_enemytype c, t_game *game);
void		move_enemies(t_game *game);
t_bool		move_ver(t_enemy *enemy, t_game *game);
t_bool		move_hor(t_enemy *enemy, t_game *game);
void		move_follow(t_enemy *enemy, t_game *game);
int			end_program(t_game *game);
void		kill_player(t_game *game, t_vector pos);
void		setup_tile(t_tile **tilemap, int x, int y);
t_tile		**alloc_tilemap(char **map);
t_enemy		*last_enemy(t_enemy *list);
int			add_enemy(t_game *game, t_enemytype c, t_tile *tile);
t_tiletype	define_tiletype(char type);
t_tile		**allocate_tilemap(char **map);
t_tile		**generate_tilemap(char **map, t_game *game);
void		get_collects_imgs(t_game *game);
void		get_players_imgs(t_game *game);
void		get_trap_imgs(t_game *game);
void		get_enemies_imgs(t_game *game);
void		get_exit_imgs(t_game *game);
void		collec_animation(t_collect_img *img);
void		enemy_animation(t_enemy_img *img);
void		player_animation(t_player *player);
t_game		get_images(t_game *game);
void		setup_animation(t_game *game);
void		effect_animation(t_effect *effect);
void		move_enemy_to(t_enemy *enemy, t_tile *pos);
void		kill_player(t_game *game, t_vector pos);
int			dist(int x);
t_bool		move_down(t_enemy *enemy, t_game *game);
t_bool		move_up(t_enemy *enemy, t_game *game);
t_bool		move_left(t_enemy *enemy, t_game *game);
t_bool		move_right(t_enemy *enemy, t_game *game);
void		draw_text(t_game *game);
void		put_enemy(t_game *game, t_tile tile);
void		put_image(t_game *game, t_tile tile);
void		put_map(t_game *game);
char		**map_alloc(int fd);
char		**readmap(char *file);
char		**checks(char *file, int argc);
int			free_matrix(char **table);
t_mapchecks	init_checkerdata(char **map);
void		trap_animation(t_game *game, t_enemy_img *img, int *flag);
int			update(t_game *game);
int			ft_chartable_linecount(char **map);
t_mapchecks	init_checkerdata(char **map);
void		effect_anim(t_effect *effect, t_vector pos);
void		action_anim(t_player *player);
void		remove_player(t_game *game);

#endif
