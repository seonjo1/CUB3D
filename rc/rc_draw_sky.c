/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_draw_sky.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:24:10 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/18 18:00:35 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void	rc_draw_sky(t_data *data)
{
	int		x;
	int		y;
	double	start;
	int		tex_len;
	double	camera_x;
	t_vec2	ray;
	
	start = fmod(((M_PI * 2 + data->player.euler_dir.y) - (FOV_BASE / 2)), M_PI * 2);
	start = (start * data->tex[TC_C].width) / M_PI * 2;
	tex_len = data->tex[TC_C].width * (FOV_BASE / (M_PI * 2));
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			camera_x = 2 * x / (double) WIN_WIDTH - 1;
			ray.x = data->player.dir.x + data->player.plane.x * camera_x;
			ray.y = data->player.dir.y + data->player.plane.y * camera_x;
			int tex_x = (int)fmod(((x * tex_len) / WIN_WIDTH + start), data->tex[TC_C].width);
			int tex_y = (y * data->tex[TC_C].height) / (WIN_HEIGHT / 2);
			int color = data->tex[TC_C].data[tex_y][tex_x];
			utils_draw_point(data, x, y, color);
			x++;
		}
		y++;
	}
}