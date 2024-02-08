/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:58:46 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 14:04:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

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

	if (ray.x == 0)
		inc.x = INFINITY;
	else
		inc.x = double_abs(1 / ray.x);
	if (ray.y == 0)
		inc.y = INFINITY;
	else
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
			side = 1;
			dis.x += inc.x;
			map.x += step.x;
		}
		else
		{
			side = 0;
			dis.y += inc.y;
			map.y += step.y;
		}
		if (data->map.data[(int)map.y][(int)map.x] == '1')
			hit = 1;
	}
	double	v_dis;
	if (side)
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
		shoot_ray(data, ray, x);
		x++;
	}
}