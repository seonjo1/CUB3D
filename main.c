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
#include "libft_s/libft_s.h"
#include "play/play.h"
#include "evnt/evnt.h"

void	draw_point(t_data *data, int x, int y, int color)
{
	if ((x >= 0 && y >= 0) && (WIN_HEIGHT > y && WIN_WIDTH > x))
		*(int *)(data->addr + (y * data->line_length + x * (data->bpp / 8))) = color;
}

void	draw_vertical_line(t_data *data, int now_x, double perpwall_dist, int color)
{
	int		y_start;
	int		y_end;
	int		line_height;
	
	line_height = (int)(WALL_HEIGHT / perpwall_dist);
	y_start = -1 * line_height / 2 + WALL_HEIGHT / 2 + data->player.pos.z;
	if (y_start < 0)
		y_start = 0;
	y_end = line_height / 2 + WALL_HEIGHT / 2 + data->player.pos.z;
	if (y_end >= WALL_HEIGHT)
		y_end = WALL_HEIGHT - 1;
	// printf("x:%d, perp:%f, y_start:%d, y_end:%d\n", x, perpwall_dist, y_start, y_end);
	while (y_start <= y_end)
	{
		draw_point(data, now_x, y_start, color);
		y_start++;
	}
}

void	draw_aim(t_data *data)
{
	t_intvec2	aim;
	int			i;

	aim.x = WIN_WIDTH / 2 - 20;
	aim.y = WIN_HEIGHT / 2;
	i = -1;
	while (++i < 40)
		draw_point(data, aim.x + i, aim.y, 0xFF00FF);
	aim.x = WIN_WIDTH / 2;
	aim.y = WIN_HEIGHT / 2 - 20;
	i = -1;
	while (++i < 40)
		draw_point(data, aim.x, aim.y + i, 0xFF00FF);
}

int	draw_get_color(int side)
{
	if (side == 1)
		return (0x00808080);
	return (0x00666666);
}

void	ray_dda(t_data *data, t_player *player, t_vec2 ray_dir, int now_x)
{
	t_intvec2	map;
	t_vec2		side_dist;
	t_vec2		delta_dist;
	double		perpwall_dist;

	map.x = (int)(player->pos.x);
	map.y = (int)(player->pos.y);
	delta_dist.x = fabs(1 / ray_dir.x);
	delta_dist.y = fabs(1 / ray_dir.y);

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
		if (data->map.data[map.y][map.x] != '0')
			hit = 1;
	}
	if (side == 0)
		perpwall_dist = (map.x - player->pos.x + (1 - step.x) / 2) / ray_dir.x;
	else
		perpwall_dist = (map.y - player->pos.y + (1 - step.y) / 2) / ray_dir.y;
	draw_vertical_line(data, now_x, perpwall_dist, draw_get_color(side));
}

void	ray_casting(t_data *data, t_player	*player)
{
	int		now_x;
	t_vec2	camera;
	t_vec2	ray_dir;

	now_x = 0;
	while (now_x < WIN_WIDTH)
	{
		camera = vec2_creat(2 * now_x / (double)WIN_WIDTH - 1, 0);
		ray_dir = vec2_add(player->dir, vec2_scala_mul(player->plane, camera.x));
		ray_dda(data, player, ray_dir, now_x);
		now_x++;
	}
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
	// usleep(100000000);
	mlx_destroy_image(data->mlx, data->img);
	mlx_do_sync(data->mlx);
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
	ft_bzero(&(data->player), sizeof(t_player));
}

int	main(int argc, char **argv)
{
	t_data		data;

	main_init(&data);
	parse_map(&(data.map), &(data.player), argc, argv);
	printf("player init! : pos.x:%f, pos.y:%f, dir.x:%f, dir.y:%f\n",\
		data.player.pos.x, data.player.pos.y, data.player.dir.x, data.player.dir.y);
	// // mlx_hook(data.mlx_win, 17, 0, &leave_event, &data);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_hook(data.mlx_win, 2, 0, &evnt_keypress, &(data.player));
	mlx_hook(data.mlx_win, 3, 0, &evnt_keyrelease, &(data.player));
	mlx_loop(data.mlx);
}
