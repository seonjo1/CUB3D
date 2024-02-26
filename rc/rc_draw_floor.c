/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   rc_draw_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:34:34 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/16 17:35:25 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"
#include "../libft_s/libft_s.h"

void	rc_floor_draw_pixel(t_data *data, t_intvec2 xy, double cx, int cy)
{
	t_rc_floor f_data;

	f_data.ray.x = data->player.dir.x + data->player.plane.x * cx;
	f_data.ray.y = data->player.dir.y + data->player.plane.y * cx;
	f_data.floor_x = data->player.pos.x + f_data.ray.x * (cy >> 1) / xy.y;
	f_data.floor_y = data->player.pos.y + f_data.ray.y * (cy >> 1) / xy.y;
	if (f_data.floor_x >= 0 && f_data.floor_y >= 0
		&& f_data.floor_x < data->map.col && f_data.floor_y < data->map.row)
	{
		f_data.tex_x = (int)((ceil(f_data.floor_x) - f_data.floor_x) * data->tex[TC_F].width);
		f_data.tex_y = (int)((ceil(f_data.floor_y) - f_data.floor_y) * data->tex[TC_F].height);
		f_data.color = data->tex[TC_F].data[f_data.tex_y][f_data.tex_x];
		utils_draw_point(data, xy.x, xy.y + (WIN_HEIGHT >> 1), f_data.color);
	}
}

void	rc_floor_thread0(t_data *data)
{
	t_intvec2	xy;
	double		camera_x;
	int			camera_y;

	camera_y = WIN_HEIGHT * FOV_BASE / data->player.fov;
	xy.y = 1;
	while (xy.y < WIN_HEIGHT / 6)
	{
		xy.x = 0;
		while (xy.x < WIN_WIDTH)
		{
			camera_x = (xy.x << 1) / (double) WIN_WIDTH - 1;
			rc_floor_draw_pixel(data, xy, camera_x, camera_y);
			xy.x++;
		}
		xy.y++;
	}
}

void	rc_floor_thread1(t_data *data)
{
	t_intvec2	xy;
	double		camera_x;
	int			camera_y;

	camera_y = WIN_HEIGHT * FOV_BASE / data->player.fov;
	xy.y =  WIN_HEIGHT / 6;
	while (xy.y < WIN_HEIGHT / 3)
	{
		xy.x = 0;
		while (xy.x < WIN_WIDTH)
		{
			camera_x = (xy.x << 1) / (double) WIN_WIDTH - 1;
			rc_floor_draw_pixel(data, xy, camera_x, camera_y);
			xy.x++;
		}
		xy.y++;
	}
}

void	rc_floor_thread2(t_data *data)
{
	t_intvec2	xy;
	double		camera_x;
	int			camera_y;

	camera_y = WIN_HEIGHT * FOV_BASE / data->player.fov;
	xy.y =  WIN_HEIGHT / 3;
	while (xy.y < WIN_HEIGHT / 2)
	{
		xy.x = 0;
		while (xy.x < WIN_WIDTH)
		{
			camera_x = (xy.x << 1) / (double) WIN_WIDTH - 1;
			rc_floor_draw_pixel(data, xy, camera_x, camera_y);
			xy.x++;
		}
		xy.y++;
	}
}

void	rc_draw_floor(t_data *data)
{
	int	i;

	pthread_create(&(data->t_id[0]), NULL, (void *)rc_floor_thread0, (void *)data);
	pthread_create(&(data->t_id[1]), NULL, (void *)rc_floor_thread1, (void *)data);
	pthread_create(&(data->t_id[2]), NULL, (void *)rc_floor_thread2, (void *)data);
	i = 0;
	while (i < 3)
		pthread_join(data->t_id[i++], NULL);
}
