#ifndef TYPE_H
# define TYPE_H

# include "basics.h"

typedef enum e_tiletype
{
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
	ENEMY = 'M',
	FOLLOWER = 'F',
	TRAP = 'T',
	PLAYER_TRAP = 'X'
}	t_tiletype;

typedef struct s_tile
{
	t_tiletype		type;
	t_tiletype		og_type;
	t_vector		position;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}	t_tile;

typedef enum e_enemytype
{
	HORIZONTAL_ENEM = 'H',
	VERTICAL_ENEM = 'V',
	FOLLOW_ENEM = 'F',
	TRAP_ENEM = 'T'
}	t_enemytype;

typedef struct s_enemy_imgs
{
	int		basic_anim;
	void	*basic_current;
	void	*basic_01;
	void	*basic_02;
	int		follow_anim;
	void	*follow_current;
	void	*follow_01;
	void	*follow_02;
	int		trap_anim;
	void	*trap_current;
	void	*trap_01;
	void	*trap_02;
	void	*trap_03;
	void	*trap_04;
}	t_enemy_img;

typedef struct s_effect
{
	void		*img;
	t_vector	pos;
	int			frames;
	int			counter;
}	t_effect;

typedef struct s_coll_img
{
	void	*current_img;
	int		anim_frames;
	void	*img_0;
	void	*img_1;
}	t_collect_img;

#endif