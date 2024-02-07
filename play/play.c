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

void	play_state_update(t_player *player)
{
	int	kb;

	kb = player->keybinds;
	if (!(player->move.x || player->move.y))
	{
		player->state = PLS_IDLE;
		player->pos.z = cos(player->time / (double)25.0) * 8;
		player->time += 1;
	}
	else if (!(kb & (1 << KB_SHITF)))
	{
		player->state = PLS_WALK;
		vec2_normalize(&(player->move), 0.0085);
		player->pos.z = cos(player->time / (double)25.0) * 12.5;
		player->time += 5;
	}
	else if (kb & (1 << KB_SHITF))
	{
		player->state = PLS_RUN;
		vec2_normalize(&(player->move), 0.0085 * 1.5);
		player->pos.z = cos(player->time / (double)25.0) * 15;
		player->time += 7;
	}
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
	play_state_update(player);
}

void	play_dir_update(t_player *player)
{
	int	kb;

	kb = player->keybinds;
	if (!(kb & (1 << KB_ROTATE_LEFT)) && kb & (1 << KB_ROTATE_RIGHT))
		player->motion_dir.y = 0.02;
	else if (!(kb & (1 << KB_ROTATE_RIGHT)) && kb & (1 << KB_ROTATE_LEFT))
		player->motion_dir.y = -0.02;
	else
		player->motion_dir.y *= 0.795;
	// printf("kb:%d, motion_diry:%.2f\n", kb, player->motion_dir.y);
}

void	play_motion(t_player *player)
{
	t_vec2	old_move;
	t_vec2	old_dir;
	t_vec2	old_plane;

	old_move = player->move;
	player->motion.x += player->move.x * player->dir.x - player->move.y * player->dir.y;
	player->motion.y += player->move.y * player->dir.x + player->move.x * player->dir.y;
	player->motion = vec2_scala_mul(player->motion, 0.85);
	player->pos.x += player->motion.x;
	player->pos.y += player->motion.y;
	// player->pos = vec2_add(player->pos, player->motion);
	old_dir = player->dir;
	player->dir.x = old_dir.x * cos(player->motion_dir.y) - old_dir.y * sin(player->motion_dir.y);
	player->dir.y = old_dir.x * sin(player->motion_dir.y) + old_dir.y * cos(player->motion_dir.y);
	old_plane = player->plane;
	player->plane.x = old_plane.x * cos(player->motion_dir.y) - old_plane.y * sin(player->motion_dir.y);
	player->plane.y = old_plane.x * sin(player->motion_dir.y) + old_plane.y * cos(player->motion_dir.y);
	// printf("dirx:%.2f diry:%.2f\n", player->dir.x, player->dir.y);
	// handle_keys(player, vars->bonus);
	// player->motion_yaw *= 0.914;
	// player->motion_pitch *= 0.82;
	
	// update_render(player, vars, vars->bonus);
	// player->yaw += player->motion_yaw;
}

void	play_update(t_data *data)
{
	play_movement_update(&(data->player));
	play_dir_update(&(data->player));
	play_motion(&(data->player));
}
