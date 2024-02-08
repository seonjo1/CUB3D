/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:58:46 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 15:25:37 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

void	rc_draw_col(t_data *data, t_vec2 ray, int x)
{
	int			i;
	int			color;
	double		dis;
	t_height	h;
	t_rc_data	rc_data;

	dis = rc_get_distance(data, &rc_data, ray);
	h.height = (int)(WIN_HEIGHT / dis);
	h.draw_start = -h.height / 2 + WIN_HEIGHT / 2;
	if (h.draw_start < 0)
		h.draw_start = 0;
	h.draw_end = h.height / 2 + WIN_HEIGHT / 2;
	if (h.draw_end >= WIN_HEIGHT)
		h.draw_end = WIN_HEIGHT - 1;
	i = 0;
	color = 0x00ff00;
	if (rc_data.side)
		color = color * 0.8;
	while (i < h.draw_start)
		utils_draw_point(data, x, i++, 0x0);
	while (i < h.draw_end)
		utils_draw_point(data, x, i++, color);
	while (i < WIN_HEIGHT)
		utils_draw_point(data, x, i++, 0x0);
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
