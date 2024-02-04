/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/04 18:08:50 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	parse_map(&map, argc, argv);
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