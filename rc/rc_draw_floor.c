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


void rc_draw_floor(t_data *data)
{
	int		x;
	int		y;
	int		camera_y;
	double	camera_x;
	t_vec2	ray;

	y = 1;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			camera_x = 2 * x / (double) WIN_WIDTH - 1;
			camera_y = WIN_HEIGHT * FOV_BASE / data->player.fov;
			ray.x = data->player.dir.x + data->player.plane.x * camera_x;
			ray.y = data->player.dir.y + data->player.plane.y * camera_x;
			double floor_x = data->player.pos.x + ray.x * (camera_y / 2) / y;
			double floor_y = data->player.pos.y + ray.y * (camera_y / 2) / y;
			if (floor_x >= 0 && floor_y >= 0 && floor_x < data->map.col && floor_y < data->map.row)
			{
				int tex_x = (int)((ceil(floor_x) - floor_x) * data->tex[TC_F].width);
				int tex_y = (int)((ceil(floor_y) - floor_y) * data->tex[TC_F].height);
				int color = data->tex[TC_F].data[tex_y][tex_x];
				utils_draw_point(data, x, y + WIN_HEIGHT / 2, color);
			}
			x++;
		}
		y++;
	}
}
