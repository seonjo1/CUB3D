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

#include "parse/parse.h"

void	utils_draw_point(t_data *data, int x, int y)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = 0xFFFFFF;
}

void	ray_dda(t_data *data, t_player *player, t_vec2 ray_dir)
{
	t_intvec2	map;
	t_vec2		side_dist;
	t_vec2		delta_dist;
	double		perpwall_dist;

	map.x = (int)(player->pos.x);
	map.y = (int)(player->pos.y);
	delta_dist.x = abs(1 / ray_dir.x);
	delta_dist.y = abs(1 / ray_dir.y);

	t_intvec2	step;
	int hit = 0;
	int side;
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (player->pos.x - map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map.x + 1.0 - player->pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (player->pos.y - map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map.y + 1.0 - player->pos.y) * delta_dist.y;
	}
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (data->map.data[map.x][map.y] > 0)
			hit = 1;
	} 
}

void	ray_casting(t_data *data, t_player	*player)
{
	int		x;
	t_vec2	camera;
	t_vec2	ray_dir;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera.x = 2 * x / (double)WIN_WIDTH - 1;
		ray_dir.x = player->dir.x + player->plane.x * camera.x;
		ray_dir.y = player->dir.y + player->plane.y * camera.x;
		
		x++;
	}
}

int	main_loop(t_data *data)
{
	static int x = 0, y = 0;
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit (1);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->line_length), &(data->endian));
	if (!data->addr)
		exit(1);
	usleep(1000);
	utils_draw_point(data, x++, y++);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
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

	main_init(&data);
	parse_map(&(data.map), &(data.player), argc, argv);
	printf("player init! : pos.x:%f, pos.y:%f, dir.x:%f, dir.y:%f\n",\
		data.player.pos.x, data.player.pos.y, data.player.dir.x, data.player.dir.y);
	// // mlx_hook(data.mlx_win, 2, 0, &keypress_event, &data);
	// // mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
}