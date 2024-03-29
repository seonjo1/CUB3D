/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_get_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:20:20 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/28 17:27:47 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"
#include "../libft_s/libft_s.h"

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
		rc_data->dis.x = (rc_data->map.x + 1 - data->player.pos.x) \
			* rc_data->inc.x;
	}
	if (ray.y < 0)
	{
		rc_data->step.y = -1;
		rc_data->dis.y = (data->player.pos.y - rc_data->map.y) * rc_data->inc.y;
	}
	else
	{
		rc_data->step.y = 1;
		rc_data->dis.y = (rc_data->map.y + 1 - data->player.pos.y) \
			* rc_data->inc.y;
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
		if (!utils_is_in_map(rc_data->map.x, rc_data->map.y, &(data->map)))
			break ;
		if (data->map.data[(int)rc_data->map.y][(int)rc_data->map.x] == '1')
			break ;
	}
}

void	rc_get_distance(t_data *data, t_rc_data *rc_data, t_draw_data *d_data, \
	t_vec2 ray)
{
	rc_init_map_and_inc(data, rc_data, ray);
	rc_init_dis_and_step(data, rc_data, ray);
	rc_shoot_ray(data, rc_data);
	if (rc_data->side)
		d_data->dist = (rc_data->map.x - data->player.pos.x + \
			(1 - rc_data->step.x) / 2) / ray.x;
	else
		d_data->dist = (rc_data->map.y - data->player.pos.y + \
			(1 - rc_data->step.y) / 2) / ray.y;
}
