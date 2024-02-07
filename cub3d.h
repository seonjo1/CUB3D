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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WALL_HEIGHT 1080

typedef enum s_keycode {
	KEY_A = 123,
	KEY_W = 126,
	KEY_D = 124,
	KEY_S = 125,
	KEY_LEFT = 0,
	KEY_UP = 13,
	KEY_RIGHT = 2,
	KEY_DOWN = 1
}	t_keycode;

typedef enum s_keybinds {
	forward = 1 << 1,
	backward = 1 << 2,
	left = 1 << 3,
	right = 1 << 4,
	rotate_left = 1 << 5,
	rotate_right = 1 << 6,
	rotate_up = 1 << 7,
	rotate_down = 1 << 8,
	jump = 1 << 9,
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