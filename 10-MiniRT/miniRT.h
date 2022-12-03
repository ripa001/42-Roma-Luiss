/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:56:01 by dripanuc          #+#    #+#             */
/*   Updated: 2022/12/03 17:21:37 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "get_next_line/get_next_line.h"

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

typedef struct s_light
{
	char			t;
	float			ratio;
	t_v3			pos;
	t_v3			rgb;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_v3			pos;
	t_v3			ori;
	t_v3			dir;
	t_v3			up;
	t_v3			u;
	t_v3			v;
	t_v3			w;
	t_v3			screen_center;
	t_mat4x4		world;
	float			lenght;
	float			horizontal_size;
	float			aspect_ratio;
	float			fov;
	float			view_range;
	t_v3			look_at;
}	t_cam;

typedef struct s_ray
{
	t_v3		o;
	t_v3		d;
	t_v3		hit;
	t_v3		hit_int;
	float		min;
	float		max;
}	t_ray;

typedef struct s_obj
{
	char			*id;
	t_v3			pos;
	t_v3			ori;
	t_v3			rgb;
	float			r;
	float			h;
	float			spec;
	float			trasp;
	float			reflect;
	int				n;
	struct s_obj	*next;
}	t_obj;

typedef struct s_pattern
{
	void	*img;
	void	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_pattern;

typedef struct s_data {
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				obj_size;
	int				reflection;
	int				frame;
	int				checkerboard;
	int				nb_obj;
	int				sel_obj;
	char			**matrix;
	float			width;
	float			height;
	float			closest_t;
	float			closest_s;
	float			resize;
	float			t;
	t_v3			ori_vec;
	t_v3			new_pos;
	t_pattern		texture;
	t_pattern		bump;
	t_ray			ray;
	t_obj			*closest_obj;
	t_cam			cam;
	t_light			*light;
	t_obj			*obj;
}	t_data;

/* UTILITY */
void		ft_free_array(char **array);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_error(char *str);
int			check_arg(t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_arraylen(char **array);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(const char *s1);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_atoi(const char *str);
float		ft_atof(const char *s);
int			mouse_exit(t_data *data);
t_v3		ret_vec(char *args);
t_v3		vec_normalize(t_v3 v);

/* MLX_UTILITY */
void		*ft_get_pattern_addr(t_pattern pattern, float u, float v);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		ft_get_uv(t_obj *obj, t_ray ray, float *u, float *v);
int			create_trgb(float t, float r, float g, float b);
int			ft_hooks(int keycode, t_data *data);
int			ft_init(t_data *data, int fd);
int			ft_update(t_data *data);
float		find_edges(t_obj *cyl, t_v3 O, t_v3 D, float *t);
float		find_edges_cone(t_obj *cn, t_v3 O, t_v3 D, float *t);
t_v3		ft_get_rgb_vec(float x, float y, float z);
t_v3		ft_rgb_pattern(t_pattern pattern, double u, double v, float brigh);
t_v3		ft_rgb_brightness_adjustment(t_v3 rgb, float adjust);
t_v3		ft_rgb2gray(t_v3 rgb);
t_v3		ft_checkerboard(t_obj *sphere, t_ray ray);

/* PARSING */
void		parse_buff(char *buff, t_data *data);
void		add_light(char	**args, t_data *data);
void		add_obj(char **args, t_data *data);
int			camera_init(char **args, t_cam *cam);
t_obj		*add_sphere(char **args);
t_obj		*add_plane(char **args);
t_obj		*add_cyl(char **args);
t_obj		*add_cone(char **args);

/* VEC OPERATIONS */
t_v3		sub_vec(t_v3 v1, t_v3 v2);
t_v3		normalize(t_v3 v1);
t_v3		mult_vec(t_v3 v1, t_v3 v2);
t_v3		add_vec(t_v3 v1, t_v3 v2);
t_v3		div_vec(t_v3 v1, t_v3 v2);
t_v3		div_vec_n(t_v3 v1, float d);
t_v3		mult_vec_n(t_v3 v1, float d);
t_v3		cross(t_v3 v1, t_v3 v2);
t_v3		reflect_ray(t_v3 R, t_v3 N);
float		get_lenght(t_v3 *v1);
float		dot(t_v3 v1, t_v3 v2);
float		norm(t_v3 v1);
/* MATRIX OPERATIONS */

t_v3		mult_vec_by_matrix(t_v3 vec, float matrix[4][4]);
float		**rot_matrix(t_v3 rot, t_v3 dir);
t_mat4x4	mat4x4(t_v3 origin, t_v3 forward, t_v3 right, t_v3 up);
t_mat4x4	look_at(t_v3 origin, t_v3 dir);
t_v3		mat4_get(t_mat4x4 m4, int get);
t_v3		mat4_mult_dir(t_mat4x4 matrix, t_v3 dir);
t_v3		rot_x(t_v3 to_rot, int angle);
t_v3		rot_y(t_v3 to_rot, int angle);
t_v3		rot_z(t_v3 to_rot, int angle);
t_v3		translation(t_v3 V, t_v3 scaling);
void		translate_obj(t_data *data);

/* TRACING */

t_obj		*closest_intersect(t_ray ray, t_data *data, float min, float max);
t_v3		trace_ray(t_ray ray, t_data *data, int recursion);
void		ft_ray(t_data *data);
float		**rotation(t_data *data);
t_ray		get_direction(int x, int y, t_data *data);
t_v3		compute_lighting(t_ray ray, t_v3 V, t_data *data, float s);
float		compute_lighting2(t_ray ray, t_light *new, t_v3	arr[4]);
void		compute_lighting3(t_ray ray, t_light *new, t_v3 arr[4], float s);
float		intersect_plane(t_v3 O, t_v3 D, t_obj *plane, float t);
float		intersect_cylinder(t_v3 O, t_v3 D, t_obj *cyl, float t);
float		intersect_ray_sphere(t_v3 O, t_v3 D, t_obj *sphere, float t);
float		intersect_ray_cone(t_v3 O, t_v3 D, t_obj *cn, float t);
float		intersect_ray_cone2(t_v3 O, t_v3 D, t_obj *cn, float arr_float[7]);
t_v3		ft_vector_rotate_cw(t_v3 vector);
t_v3		ft_vector_rotate_ccw(t_v3 vector);
t_pattern	ft_get_pattern(t_data *data, char *filename);
t_pattern	ft_get_pattern(t_data *data, char *filename);
t_v3		ft_bump_and_texture(t_ray ray, t_obj *closest_obj, t_data *data);
int			check_valid_obj(t_data *data, char *line);
void		resize_obj(t_data *data);
void		ori_obj(t_data *data);

#endif