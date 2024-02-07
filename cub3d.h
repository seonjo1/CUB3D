/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:32:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/05 19:00:21 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WALL_HEIGHT 1080

typedef enum s_keycode {
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_A = 0,
	KEY_W = 13,
	KEY_D = 2,
	KEY_S = 1,
	KEY_ESC = 53
}	t_keycode;

typedef enum s_keybinds {
	KB_FORWARD,
	KB_BACKWARD,
	KB_LEFT,
	KB_RIGHT,
	KB_ROTATE_LEFT,
	KB_ROTATE_RIGHT,
	KB_ROTATE_UP,
	KB_ROTATE_DOWN,
	KB_JUMP
}	t_keybinds;

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_intvec2 {
	int	x;
	int	y;
}	t_intvec2;

typedef struct s_player {
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
	t_vec2	move;
	t_vec2	motion;
	t_vec2	motion_dir;
	double	speed;
	int		keybinds;
}	t_player;

typedef struct s_map {
	char	**data;
	int		row;
	int		col;
}	t_map;

typedef struct s_data {
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_map		map;
	t_player	player;
}	t_data;

#endif