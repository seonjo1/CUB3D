/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:58:46 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 15:17:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"

double	double_abs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	rc_init_map_and_inc(t_data *data, t_rc_data *rc_data, t_vec2 ray)
{
	rc_data->map.x = (int)data->player.pos.x;
	rc_data->map.y = (int)data->player.pos.y;
	if (ray.x == 0)
		rc_data->inc.x = INFINITY;
	else
		rc_data->inc.x = double_abs(1 / ray.x);
	if (ray.y == 0)
		rc_data->inc.y = INFINITY;
	else
		rc_data->inc.y = double_abs(1 / ray.y);	
}

void	rc_init_dis_and_step(t_data *data, t_rc_data *rc_data, t_vec2 ray)
{
	if (ray.x < 0)
	{
		rc_data->step.x = -1;
		rc_data->dis.x = (data->player.pos.x - rc_data->map.x) * rc_data->inc.x;
	}
	else
	{
		rc_data->step.x = 1;
		rc_data->dis.x = (rc_data->map.x + 1 - data->player.pos.x) * rc_data->inc.x;
	}
	if (ray.y < 0)
	{
		rc_data->step.y = -1;
		rc_data->dis.y = (data->player.pos.y - rc_data->map.y) * rc_data->inc.y;
	}
	else
	{
		rc_data->step.y = 1;
		rc_data->dis.y = (rc_data->map.y + 1 - data->player.pos.y) * rc_data->inc.y;
	}
}

void	rc_shoot_ray(t_data *data, t_rc_data *rc_data)
{
	while (1)
	{
		if (rc_data->dis.x < rc_data->dis.y)
		{
			rc_data->side = 1;
			rc_data->dis.x += rc_data->inc.x;
			rc_data->map.x += rc_data->step.x;
		}
		else
		{
			rc_data->side = 0;
			rc_data->dis.y += rc_data->inc.y;
			rc_data->map.y += rc_data->step.y;
		}
		if (data->map.data[(int)rc_data->map.y][(int)rc_data->map.x] == '1')
			break ;
	}
}

double	rc_get_distance(t_data *data, t_vec2 ray)
{
	t_rc_data	rc_data;

	rc_init_map_and_inc(data, &rc_data, ray);
	rc_init_dis_and_step(data, &rc_data, ray);
	rc_shoot_ray(data, &rc_data);
	if (rc_data.side)
		return ((rc_data.map.x - data->player.pos.x + \
			(1 - rc_data.step.x) / 2) / ray.x);
	else
		return ((rc_data.map.y - data->player.pos.y + \
			(1 - rc_data.step.y) / 2) / ray.y);
}

void	rc_draw_col(t_data *data, t_vec2 ray, int x)
{
	int			i;
	double		dis;
	t_height	h;

	dis = rc_get_distance(data, ray);
	h.height = (int)(WIN_HEIGHT / dis);
	h.draw_start = -h.height / 2 + WIN_HEIGHT / 2;
	if (h.draw_start < 0)
		h.draw_start = 0;
	h.draw_end = h.height / 2 + WIN_HEIGHT / 2;
	if (h.draw_end >= WIN_HEIGHT)
		h.draw_end = WIN_HEIGHT - 1;
	i = 0;
	while (i < h.draw_start)
		utils_draw_point(data, x, i++, 0x0);
	while (i < h.draw_end)
		utils_draw_point(data, x, i++, 0x00ff00);
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
