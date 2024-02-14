/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:32:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/10 20:00:39 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "math.h"

# define TRUE 1
# define FALSE 0
# define ENTER 0
# define RUN 1
# define EXIT 2
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WALL_HEIGHT 1080
# define FOV_BASE 1.15192
# define RECALL_STORE_MAX 50
# define RECALL_COOLDOWN 450

typedef enum s_keycode {
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_E = 14,
	KEY_SHIFT = 257,
	KEY_SPACE = 49,
	KEY_CTRL = 256,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_ESC = 53
}	t_keycode;

typedef enum s_keybinds {
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
	KB_1
}	t_keybinds;

typedef enum s_texture {
	TX_NO = 1,
	TX_SO = 2,
	TX_WE = 4,
	TX_EA = 8,
	TX_F = 16,
	TX_C = 32,
	TX_END = 63
}	t_texture;

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_intvec2 {
	int	x;
	int	y;
}	t_intvec2;

typedef struct s_recall {
	t_vec3	pos[RECALL_STORE_MAX];
	t_vec2	euler_dir[RECALL_STORE_MAX];
	int		idx;
	int		frame;
	int		cooldown;
}	t_recall;

typedef struct s_player {
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
	t_recall	recall;	
	long long	time;
}	t_player;

typedef struct s_map {
	char	**data;
	int		row;
	int		col;
}	t_map;

typedef struct s_tex {
	char	*file;
	int		*tex;
	int		width;
	int		height;
}	t_tex;

typedef enum e_hand_res_num {
	HN_FLASH = 5,
	HN_ATTACK = 24,
	HN_PULSE = 15,
	HN_RECALL = 24,
	HN_RELOAD = 23,
	HN_SHOT = 11,
	HN_WALK = 19,
}	t_hand_res_num;

typedef struct s_hand_res {
	void	*flash[HN_FLASH];
	void	*attack[HN_ATTACK];
	void	*pulse[HN_PULSE];
	void	*recall[HN_RECALL];
	void	*reload[HN_RELOAD];
	void	*shot[HN_SHOT];
	void	*walk[HN_WALK];
}	t_hand_res;

typedef struct s_data {
	void			*mlx;
	void			*mlx_win;
	void			*img;
	void			*hand;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				c_color;
	int				f_color;
	t_map			map;
	t_tex			tex[4];
	t_player		player;
	t_hand_res	hand_res;
	long long	time;
}	t_data;

typedef struct s_rc_data {
	int		tmp;
	int		side;
	t_vec2	map;
	t_vec2	dis;
	t_vec2	inc;
	t_vec2	step;
}	t_rc_data;

typedef struct s_height {
	int	height;
	int	draw_start;
	int	draw_end;
}	t_height;

void	utils_draw_point(t_data *data, int x, int y, int color);

#endif