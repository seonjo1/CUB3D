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
		player->pos.z = sin(player->time / (double)25.0) * 8;
		player->time += 1;
	}
	else if (!(kb & (1 << KB_SHITF)))
	{
		player->state = PLS_WALK;
		vec2_normalize(&(player->move), 0.0085);
		player->pos.z = sin(player->time / (double)25.0) * 12.5;
		player->time += 5;
	}
	else if (kb & (1 << KB_SHITF))
	{
		player->state = PLS_RUN;
		vec2_normalize(&(player->move), 0.0085 * 1.5);
		player->pos.z = sin(player->time / (double)25.0) * 15;
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
}

void	play_key_dir_update(t_player *player)
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

void	play_dir_plane_set(t_player *player)
{
	double	sn;
	double	cs;

	sn = sin(player->euler_dir.y);
	cs = cos(player->euler_dir.y);
	player->dir = vec2_creat(cs, sn);
	player->plane = vec2_scala_mul(vec2_creat(-sn, cs), 0.66);
}

void	play_motion(t_player *player)
{
	t_vec2	old_move;

	old_move = player->move;
	player->motion.x += player->move.x * player->dir.x - player->move.y * player->dir.y;
	player->motion.y += player->move.y * player->dir.x + player->move.x * player->dir.y;
	player->motion = vec2_scala_mul(player->motion, 0.85);
	player->pos.x += player->motion.x;
	player->pos.y += player->motion.y;
	player->euler_dir.y += player->motion_dir.y;
}

void	play_mouse_update(t_data *data)
{
	int			kb;
	t_intvec2	mouse_pos;

	kb = data->player.keybinds;
	if (kb & (1 << KB_1))
	{
		mlx_mouse_get_pos(data->mlx_win, &(mouse_pos.x), &(mouse_pos.y));
		mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		if (mouse_pos.x - WIN_WIDTH / 2 != 0)
		{
			data->player.motion_dir.y = (mouse_pos.x - WIN_WIDTH / 2) / (double)314;
		}
		else
			data->player.motion_dir.y *= 0.795;
	}
}

void	play_update(t_data *data)
{
	play_mouse_update(data);
	play_dir_plane_set(&(data->player));
	play_key_dir_update(&(data->player));
	play_movement_update(&(data->player));
	play_state_update(&(data->player));
	play_motion(&(data->player));
}
