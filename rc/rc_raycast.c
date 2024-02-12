/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:58:46 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/12 21:50:40 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void	rc_draw_col(t_data *data, t_vec2 ray, int x)
{
	int			i;
	int			color;
	double		dis;
	int			tex_x;
	t_height	h;
	t_rc_data	rc_data;

	dis = rc_get_distance(data, &rc_data, ray);

	double	wall_x;
	int		type;
	
	if (rc_data.side && ray.x > 0)
		type = TC_EA;
	else if (rc_data.side && ray.x < 0)
		type = TC_WE;
	else if (ray.y > 0)
		type = TC_SO;
	else
		type = TC_NO;
	if (rc_data.side)
		wall_x = data->player.pos.y + dis * ray.y;
	else
		wall_x = data->player.pos.x + dis * ray.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->tex[type].width);
	
	h.height = (int)(WIN_HEIGHT / dis) * FOV_BASE / data->player.fov;
	h.draw_start = -h.height / 2 + WIN_HEIGHT / 2 + data->player.pos.z / dis;
	h.draw_end = h.height / 2 + WIN_HEIGHT / 2 + data->player.pos.z / dis;
	int start = h.draw_start;
	int	end = h.draw_end;
	if (h.draw_start < 0)
		h.draw_start = 0;
	if (h.draw_end >= WIN_HEIGHT)
		h.draw_end = WIN_HEIGHT - 1;
	i = 0;
	if (rc_data.side)
		color = 0x777777;
	while (i < h.draw_start)
		utils_draw_point(data, x, i++, data->c_color);
	int tex_height = end - start;
	while (i < h.draw_end)
	{
		color = data->tex[type].data[((i - start) * data->tex[type].height) / tex_height][tex_x];
		utils_draw_point(data, x, i++, color);
	}
	while (i < WIN_HEIGHT)
		utils_draw_point(data, x, i++, data->f_color);
}

void	rc_raycast(t_data *data)
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
		rc_draw_col(data, ray, x);
		x++;
	}
}
