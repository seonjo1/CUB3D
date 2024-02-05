/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:32:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 17:41:46 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft_s/libft_s.h"
# include "minilibx/mlx.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		endian;
}	t_data;

typedef struct s_map {
	char	*data;
	int		row;
	int		col;
}	t_map;

#endif