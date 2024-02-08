/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 16:00:08 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
#include "evnt/evnt.h"
#include "rc/rc.h"

void	utils_draw_point(t_data *data, int x, int y, int color)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

int	main_loop(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		exit(1);
	play_update(data);
	ray_casting(data, &(data->player));
	draw_aim(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	mlx_do_sync(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	parse_map(&(data.map), &(data.player), argc, argv);
	main_init(&data);
	parse_map(&(data.map), &(data.player), argc, argv);
	printf("player init! : pos.x:%f, pos.y:%f, dir.x:%f, dir.y:%f\n",\
		data.player.pos.x, data.player.pos.y, data.player.dir.x, data.player.dir.y);
	mlx_hook(data.mlx_win, 17, 0, &evnt_leave, 0);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_hook(data.mlx_win, 2, 0, &evnt_keypress, &(data.player));
	mlx_hook(data.mlx_win, 3, 0, &evnt_keyrelease, &(data.player));
	mlx_loop(data.mlx);
}
