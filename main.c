/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/06 20:08:54 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"

void	utils_draw_point(t_data *data, int x, int y)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = 0xFFFFFF;
}

double	abs_c(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	veclen(t_vec2 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
}

void	shoot_ray(t_data *data, t_vec2 ray, int window_x)
{
	t_vec2	map;
	t_vec2	dis;
	t_vec2	inc;
	t_vec2	step;

	inc.x = abs_c(veclen(ray) / ray.x);
	inc.y = abs_c(veclen(ray) / ray.y);
	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;
	if (ray.x < 0)
	{
		step.x = -1;
		dis.x = inc.x * (data->player.pos.x - map.x);
	}
	else
	{
		step.x = 1;
		map.x++;
		dis.x = inc.x * (map.x - data->player.pos.x);
	}
	if (ray.y < 0)
	{
		step.y = -1;
		dis.y = inc.y * (data->player.pos.y - map.y);
	}
	else
	{
		step.y = 1;
		map.y++;
		dis.y = inc.y * (map.y - data->player.pos.y);
	}
}

int	main_loop(t_data *data)
{
	t_vec2	ray;
	int		window_x;
	double	i;
	double	gap;

	i = -1;
	window_x = 0;
	gap = (double) 2 / WIN_WIDTH;
	while (window_x < WIN_WIDTH)
	{
		ray.x = data->player.dir.x + (data->player.plane.x * i);
		ray.y = data->player.dir.y + (data->player.plane.y * i);
		shoot_ray(data, ray, window_x);
		i += gap;
		window_x++;
	}
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		exit(1);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	// mlx_destroy_image(data->mlx, data->img);
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
