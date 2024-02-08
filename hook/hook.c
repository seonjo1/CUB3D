/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:35:23 by seonjo            #+#    #+#             */
/*   Updated: 2024/02/08 16:05:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_vec2	rotate_vec2(t_vec2 vec, int deg)
{
	t_vec2	ret_vec;
	double	rad;

	rad = deg * (PI / 180);
	ret_vec.x = vec.x * cos(rad) - vec.y * sin(rad);
	ret_vec.y = vec.x * sin(rad) + vec. y * cos(rad);
	return (ret_vec);
}

int	keypress_event(int keycode, t_data *data)
{
	t_vec2	vec;

	if (keycode == KEY_W)
	{
		printf("KEY_W : %d\n", keycode);
		data->player.pos.x += data->player.dir.x;
		data->player.pos.y += data->player.dir.y;
	}
	else if (keycode == KEY_D)
	{
		printf("KEY_D : %d\n", keycode);
		vec = rotate_vec2(data->player.dir, 90);
		data->player.pos.x += vec.x;
		data->player.pos.y += vec.y;
	}
	else if (keycode == KEY_S)
	{
		printf("KEY_S : %d\n", keycode);
		vec = rotate_vec2(data->player.dir, 180);
		data->player.pos.x += vec.x;
		data->player.pos.y += vec.y;
	}
	else if (keycode == KEY_A)
	{
		printf("KEY_A : %d\n", keycode);
		vec = rotate_vec2(data->player.dir, 270);
		data->player.pos.x += vec.x;
		data->player.pos.y += vec.y;
	}
	else if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(1);
	}
	return (0);
}

int	leave_event(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(1);
	return (0);
}