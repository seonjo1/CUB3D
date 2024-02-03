/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/31 18:22:17 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

int	main(void)
{
	t_data	data;

	printf("here");
	printf("here");
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	// data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	// data.addr = mlx_get_data_addr(data.img, &(data.map.bpp),
	// 		&(data.map.line_length), &(data.endian));
	// mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
	// mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
	mlx_loop(data.mlx);
}