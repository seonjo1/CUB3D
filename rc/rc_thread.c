/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:02:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/26 19:00:28 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rc.h"


void	rc_thread0(t_data *data)
{
	int		x;
	int		end;
	double	camera_x;
	t_vec2	ray;
	
	
	x = 0;
	end = (WIN_WIDTH / 3);
	while (x < end)
	{
		camera_x = 2 * x / (double) WIN_WIDTH - 1;
		ray.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.y = data->player.dir.y + data->player.plane.y * camera_x;
		rc_draw_col(data, ray, x);
		x++;	
	}
}

void	rc_thread1(t_data *data)
{
	int		x;
	int		end;
	double	camera_x;
	t_vec2	ray;
	
	
	x = (WIN_WIDTH / 3) * 1;
	end = (WIN_WIDTH / 3) * 2;
	while (x < end)
	{
		camera_x = 2 * x / (double) WIN_WIDTH - 1;
		ray.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.y = data->player.dir.y + data->player.plane.y * camera_x;
		rc_draw_col(data, ray, x);
		x++;	
	}
}

void	rc_thread2(t_data *data)
{
	int		x;
	int		end;
	double	camera_x;
	t_vec2	ray;
	
	
	x = (WIN_WIDTH / 3) * 2;
	end = (WIN_WIDTH / 3) * 3;
	while (x < end)
	{
		camera_x = 2 * x / (double) WIN_WIDTH - 1;
		ray.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.y = data->player.dir.y + data->player.plane.y * camera_x;
		rc_draw_col(data, ray, x);
		x++;	
	}
}
