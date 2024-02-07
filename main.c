/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/07 20:00:59 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"

void	utils_draw_point(t_data *data, int x, int y, int color)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

int	main_loop(t_data *data)
{
	t_vec2	ray;

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	main_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->mlx_win)
		exit(1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_data		data;

	parse_map(&(data.map), &(data.player), argc, argv);
	main_init(&data);
	printf("player init! : pos.x:%f, pos.y:%f, dir.x:%f, dir.y:%f\n", data.player.pos.x, data.player.pos.y, data.player.dir.x, data.player.dir.y);
	// // mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
	// // mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
}
