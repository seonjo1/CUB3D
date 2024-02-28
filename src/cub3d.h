/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:32:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 20:56:01 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../bass/bass.h"
# include "gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# define TRUE 1
# define FALSE 0
# define ENTER 0
# define RUN 1
# define EXIT 2
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WALL_HEIGHT 1080
# define FOV_BASE 1.41
# define RECALL_STORE_MAX 80
# define RECALL_COOLDOWN 450
# define BASS_SAMPLE_LOOP 4
# define MAX_MAG 60
# define Z_BASE 200

typedef enum s_keycode
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_OTHER = 3,
	MOUSE_UP = 4,
	MOUSE_DOWN = 5,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_E = 14,
	KEY_R = 15,
	KEY_V = 9,
	KEY_SHIFT = 257,
	KEY_SPACE = 49,
	KEY_CTRL = 256,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_ESC = 53
}	t_keycode;

typedef enum s_keybinds
{
	KB_FORWARD,
	KB_D_FORWARD,
	KB_BACKWARD,
	KB_LEFT,
	KB_RIGHT,
	KB_ROTATE_LEFT,
	KB_ROTATE_RIGHT,
	KB_ROTATE_UP,
	KB_ROTATE_DOWN,
	KB_FLASH,
	KB_JUMP,
	KB_CROUCH,
	KB_RECALL,
	KB_ATTACK,
	KB_RELOAD,
	KB_1,
	KB_M_LEFT,
	KB_M_RIGHT
}	t_keybinds;

typedef enum s_parse_code
{
	PC_EA = 1,
	PC_WE = 2,
	PC_SO = 4,
	PC_NO = 8,
	PC_F = 16,
	PC_C = 32,
	PC_END = 63
}	t_parse_code;

typedef enum s_tex_code
{
	TC_EA = 0,
	TC_WE = 1,
	TC_SO = 2,
	TC_NO = 3
}	t_tex_code;

typedef enum e_h_state
{
	HS_FLASH = 'f',
	HS_ATTACK = 'a',
	HS_PULSE = 'p',
	HS_RECALL = 'i',
	HS_RELOAD = 'l',
	HS_SHOT = 's',
	HS_WALK = 'w',
	HS_RUN = 'r',
	HS_NONE = 'n'
}	t_h_state;

typedef enum e_hand_res_num
{
	HN_FLASH = 4,
	HN_ATTACK = 16,
	HN_PULSE = 15,
	HN_RECALL = 28,
	HN_RELOAD = 23,
	HN_SHOT = 9,
	HN_WALK = 32,
}	t_hand_res_num;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_intvec2
{
	int	x;
	int	y;
}	t_intvec2;

typedef struct s_recall
{
	t_vec3	pos[RECALL_STORE_MAX];
	t_vec2	euler_dir[RECALL_STORE_MAX];
	int		idx;
	int		frame;
	int		cooldown;
}	t_recall;

typedef struct s_sounds
{
	uint32_t	attack;
	uint32_t	flash[3];
	uint32_t	gun;
	uint32_t	recall;
	uint32_t	reload;
	uint32_t	walk;
	uint32_t	run;
}	t_sounds;

typedef struct s_player
{
	t_vec3		pos;
	double		fov;
	t_vec2		move;
	t_vec2		dir;
	t_vec2		plane;
	t_vec2		euler_dir;
	t_vec3		motion_dir;
	t_vec3		motion;
	int			keybinds;
	char		state[4];
	t_h_state	h_state;
	t_recall	recall;
	int			flash_frame;
	int			reload_frame;
	long long	time;
	t_sounds	*s_res;
}	t_player;

typedef struct s_map
{
	char	**data;
	int		row;
	int		col;
}	t_map;

typedef struct s_tex
{
	char	*file;
	int		**data;
	int		width;
	int		height;
	int		gap;
}	t_tex;

typedef struct s_mini
{
	int			size;
	int			color;
	t_intvec2	pos;
	double		x;
	double		y;
	double		distance;
	double		radius;
	double		rot_x;
	double		rot_y;
	double		start_i;
	double		start_j;
	double		ratio;
}	t_mini;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			c_color;
	int			f_color;
	t_mini		mini;
	t_map		map;
	t_tex		tex[4];
	t_player	player;
	t_sounds	s_res;
	long long	time;
}	t_data;

typedef struct s_rc_data
{
	int		side;
	t_vec2	map;
	t_vec2	dis;
	t_vec2	inc;
	t_vec2	step;
}	t_rc_data;

typedef struct s_draw_data
{
	int		type;
	int		start;
	int		end;
	int		color;
	int		tex_x;
	int		tex_h;
	int		offset;
	double	wall_x;
	double	dist;
}	t_draw_data;

#endif