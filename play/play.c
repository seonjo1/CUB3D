/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:00:08 by michang           #+#    #+#             */
/*   Updated: 2024/02/07 18:00:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play.h"
#include "../libft_s/libft_s.h"

void	play_dir_update(t_data *data)
{
	static unsigned int	delay = 0;
	int					kb;
	t_intvec2			mouse_pos;

	kb = data->player.keybinds;
	if (kb & (1 << KB_1))
	{
		mlx_mouse_get_pos(data->mlx_win, &(mouse_pos.x), &(mouse_pos.y));
		mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		delay++;
		if (delay >= 5)
		{
			if (mouse_pos.x - WIN_WIDTH / 2 != 0)
				data->player.motion_dir.y = (mouse_pos.x - WIN_WIDTH / 2) / 314.0;
			else
				data->player.motion_dir.y *= 0.795;
			delay = data->player.time;
		}
	}
	else
		delay = 0;
	if (!(kb & (1 << KB_ROTATE_LEFT)) && kb & (1 << KB_ROTATE_RIGHT))
		data->player.motion_dir.y = 0.02;
	else if (!(kb & (1 << KB_ROTATE_RIGHT)) && kb & (1 << KB_ROTATE_LEFT))
		data->player.motion_dir.y = -0.02;
	else
		data->player.motion_dir.y *= 0.795;
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

void	play_movement_update(t_player *player)
{
	int	kb;
	
	kb = player->keybinds;
	player->move.x = 0;
	if (!(kb & (1 << KB_FORWARD) && kb & (1 << KB_BACKWARD)))
	{
		if (kb & (1 << KB_FORWARD))
			player->move.x = 1;
		else if (kb & (1 << KB_BACKWARD))
			player->move.x = -1;
	}
	player->move.y = 0;
	if (!(kb & (1 << KB_LEFT) && kb & (1 << KB_RIGHT)))
	{
		if (kb & (1 << KB_LEFT))
			player->move.y = -1;
		else if (kb & (1 << KB_RIGHT))
			player->move.y = 1;
	}
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

void	play_state_update(t_player *player)
{
	int	kb;

	kb = player->keybinds;
	player->state = 0 | (player->state & (1 << PLS_JUMP)) | (player->state & (1 << PLS_CROUCH));
	if (!(player->move.x || player->move.y))
	{
		player->state |= (1 << PLS_IDLE);
		if (!(player->state & (1 << PLS_JUMP)) && !(player->state & (1 << PLS_CROUCH)))
			player->pos.z = sin(player->time / (double)25.0) * 20;
		player->time += 1;
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (!(kb & (1 << KB_D_FORWARD)))
	{
		player->state |= (1 << PLS_WALK);
		vec2_normalize(&(player->move), 0.0085);
		if (!(player->state & (1 << PLS_JUMP)) && !(player->state & (1 << PLS_CROUCH)))
		{
			player->pos.z = sin(player->time / (double)25.0) * 30;
			player->time += 5;
		}
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (kb & (1 << KB_D_FORWARD))
	{
		vec2_normalize(&(player->move), 0.0085 * 1.5);
		if (!(player->state & (1 << PLS_JUMP)) && !(player->state & (1 << PLS_CROUCH)))
		{
			player->pos.z = sin(player->time / (double)25.0) * 50;
			player->time += 7;
		}
		play_target_update(&(player->fov), FOV_BASE * 1.1, 0.015, 0.03);
	}
	if (kb & (1 << KB_JUMP) && !(player->state & (1 << PLS_JUMP)) && !(player->state & (1 << PLS_CROUCH)))
	{
		player->state = (player->state & ~(1 << PLS_JUMP)) | (1 << PLS_JUMP);
		player->motion.z = 45;
		player->time = 0;
	}
	else if (kb & (1 << KB_CROUCH) && !(player->state & (1 << PLS_JUMP)))
	{
		player->time = 0;
		player->state |= (1 << PLS_CROUCH);
		vec2_normalize(&(player->move), 0.0085 * 0.25);
		play_target_update(&(player->pos.z), -150, 30, 40);
	}
	else if (!(kb & (1 << KB_CROUCH)) && (player->state & (1 << PLS_CROUCH))
		&& play_target_update(&(player->pos.z), 0, 30, 40))
			player->state = player->state & ~(1 << PLS_CROUCH);
}

void	play_motion(t_player *player)
{
	t_vec2	old_move;

	old_move = player->move;
	player->motion.x += player->move.x * player->dir.x - player->move.y * player->dir.y;
	player->motion.y += player->move.y * player->dir.x + player->move.x * player->dir.y;
	player->motion.x = player->motion.x * 0.85;
	player->motion.y = player->motion.y * 0.85;
	player->pos.x += player->motion.x;
	player->pos.y += player->motion.y;
	player->euler_dir.y += player->motion_dir.y;
	if (player->state & (1 << PLS_JUMP))
	{
		player->pos.z += player->motion.z;
		player->motion.z -= 2.5;
		if (player->motion.z < -45)
		{
			player->state = player->state & ~(1 << PLS_JUMP);
			player->pos.z = 0;
		}
	}
}

void	play_update(t_data *data)
{
	play_dir_update(data);
	play_dir_plane_set(&(data->player));
	play_movement_update(&(data->player));
	play_state_update(&(data->player));
	play_motion(&(data->player));
}
