/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:09:14 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/07 20:30:21 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"

void	utils_draw_point(t_data *data, int x, int y, int color)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

double	double_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	shoot_ray(t_data *data, t_vec2 ray, int x)
{
	int		hit;
	int		side;
	t_vec2	map;
	t_vec2	inc;
	t_vec2	dis;
	t_vec2	step;

	map.x = (int)data->player.pos.x;
	map.y = (int)data->player.pos.y;

	inc.x = double_abs(1 / ray.x);
	inc.y = double_abs(1 / ray.y);

	hit = 0;
	if (ray.x < 0)
	{
		step.x = -1;
		dis.x = (data->player.pos.x - map.x) * inc.x;
	}
	else
	{
		step.x = 1;
		dis.x = (map.x + 1 - data->player.pos.x) * inc.x;
	}
	if (ray.y < 0)
	{
		step.y = -1;
		dis.y = (data->player.pos.y - map.y) * inc.y;
	}
	else
	{
		step.y = 1;
		dis.y = (map.y + 1 - data->player.pos.y) * inc.y;
	}
	
	while (!hit)
	{
		if (dis.x < dis.y)
		{
			dis.x += inc.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			dis.y += inc.y;
			map.y += step.y;
			side = 1;
		}
		if (data->map.data[(int)map.y][(int)map.x] == '1')
			hit = 1;
	}
	double	v_dis;
	if (!side)
		v_dis = (map.x - data->player.pos.x + (1 - step.x) / 2) / ray.x;
	else
		v_dis = (map.y - data->player.pos.y + (1 - step.y) / 2) / ray.y;
	int height = (int)(WIN_HEIGHT / v_dis);

	int draw_start = -height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	int i = 0;
	int color = 0x00ff00;
	if (side)
		color = color * 0.7;
	while (i < draw_start)
		utils_draw_point(data, x, i++, 0x0);
	while (i < draw_end)
		utils_draw_point(data, x, i++, color);
	while (i < WIN_HEIGHT)
		utils_draw_point(data, x, i++, 0x0);
}

int	main_loop(t_data *data)
{
	int		x;
	double	camera_x;
	t_vec2	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2 * x / (double) WIN_WIDTH - 1;
		ray.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.y = data->player.dir.y + data->player.plane.y * camera_x;
		shoot_ray(data, ray, x);
		x++;
	}
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
