/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_dir_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:04:08 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:04:07 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play_bonus.h"
#include "../libft_s/libft_s_bonus.h"

void	play_motion_dir_set(t_data *data)
{
	int	kb;

	kb = data->player.keybinds;
	if (!(kb & (1 << KB_ROTATE_LEFT)) && kb & (1 << KB_ROTATE_RIGHT))
		data->player.motion_dir.y = 0.02;
	else if (!(kb & (1 << KB_ROTATE_RIGHT)) && kb & (1 << KB_ROTATE_LEFT))
		data->player.motion_dir.y = -0.02;
	else
		data->player.motion_dir.y *= 0.795;
	if (!(kb & (1 << KB_ROTATE_UP)) && kb & (1 << KB_ROTATE_DOWN))
		data->player.motion_dir.x = -8;
	else if (!(kb & (1 << KB_ROTATE_DOWN)) && kb & (1 << KB_ROTATE_UP))
		data->player.motion_dir.x = 8;
	else
		data->player.motion_dir.x *= 0.795;
}

void	play_motion_dir_get_mouse(t_data *data)
{
	static unsigned int	delay = 0;
	int					kb;
	t_intvec2			mouse;

	kb = data->player.keybinds;
	if (kb & (1 << KB_1))
	{
		mlx_mouse_get_pos(data->mlx_win, &(mouse.x), &(mouse.y));
		mlx_mouse_move(data->mlx_win, (WIN_WIDTH >> 1), (WIN_HEIGHT >> 1));
		delay++;
		if (delay >= 5)
		{
			if (mouse.x - (WIN_WIDTH >> 1) != 0)
				data->player.motion_dir.y = (mouse.x - WIN_WIDTH / 2) / 314.0;
			else
				data->player.motion_dir.y *= 0.795;
			if (mouse.y - (WIN_HEIGHT >> 1) != 0)
				data->player.motion_dir.x = -(mouse.y - WIN_HEIGHT / 2) * 1.5;
			else
				data->player.motion_dir.x *= 0.795;
			delay = data->player.time;
		}
	}
	else
		delay = 0;
}

void	play_dir_plane_set(t_player *player)
{
	double	sn;
	double	cs;

	sn = sin(player->euler_dir.y);
	cs = cos(player->euler_dir.y);
	player->dir = vec2_creat(cs, sn);
	player->plane = vec2_scala_mul(vec2_creat(-sn, cs), tan(player->fov / 2.0));
}

int	play_target_update(double *target, double goal, double delta, double offset)
{
	if (*target + offset < goal)
		*target += delta;
	else if (*target - offset > goal)
		*target -= delta;
	else
	{
		*target = goal;
		return (1);
	}
	return (0);
}
