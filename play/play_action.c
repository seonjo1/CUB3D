/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:42:45 by michang           #+#    #+#             */
/*   Updated: 2024/02/11 16:42:46 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play.h"
#include "../sound/sound.h"
#include "../libft_s/libft_s.h"

void	play_action_movement(t_player *player)
{
	char	*ps;

	ps = player->state;
	if (ps[0] == 'W' && ps[2] == '_')
	{
		if (!(player->move.x || player->move.y) && ps[1] == '_')
			player->motion.z = sin(player->time++ / (double)25.0) * 10;
		else if (ps[1] == '_')
		{
			player->motion.z = sin(player->time / (double)25.0) * 15;
			player->time += 5;
		}
		player->move = vec2_normalize(player->move, 0.0085);
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (ps[0] == 'R' && ps[2] == '_')
	{
		player->move = vec2_normalize(player->move, 0.0085 * 1.5);
		if (ps[1] == '_')
		{
			player->motion.z = sin(player->time / (double)25.0) * 20;
			player->time += 7;
		}
		play_target_update(&(player->fov), FOV_BASE * 1.1, 0.015, 0.03);
	}
}

void	play_action_jump(t_player *player, char *transition, char enter)
{
	if (enter == ENTER)
	{
		ft_strlcpy(player->state, transition, 4);
		player->motion_dir.z = 45;
	}
	else if (enter == RUN)
	{
		if (player->state[1] == 'J')
		{
			play_target_update(&(player->motion.z), 0, 2, 4);
			player->pos.z += player->motion_dir.z;
			player->motion_dir.z -= 2.5;
			if (player->motion_dir.z < -45)
			{
				player->state[1] = '_';
				player->pos.z = 0;
			}
		}
	}
}

void	play_action_crouch(t_player *player, char *transition, char enter)
{
	if (enter == ENTER)
		ft_strlcpy(player->state, transition, 4);
	else if (enter == RUN && player->state[1] == 'C')
	{
		play_target_update(&(player->pos.z), -150, 30, 40);
		player->move = vec2_normalize(player->move, 0.0085 * 0.25);
	}
	else if (enter == RUN && player->state[1] == 'c')
	{
		if (play_target_update(&(player->pos.z), 0, 30, 40))
			ft_strlcpy(player->state, "W__", 4);
	}
}

void	play_action_flash(t_player *player, char *transition, char enter)
{
	static t_vec2		flash_dir;

	if (enter == ENTER)
	{
		player->keybinds = (player->keybinds & ~(1 << KB_FLASH));
		ft_strlcpy(player->state, transition, 4);
		flash_dir = player->move;
		if (!(player->move.x || player->move.y))
			flash_dir = vec2_creat(1, 0);
		player->flash_frame = 0;
		flash_dir = vec2_normalize(flash_dir, 0.0085 * 1450);
		sound_play(player->s_res->flash[abs((int)(player->dir.x * 100)) % 3]);
	}
	else if (enter == RUN)
	{
		if (player->state[2] == 'F')
		{
			flash_dir = vec2_scala_mul(flash_dir, 0.075);
			player->move = flash_dir;
			if (player->flash_frame == HN_FLASH)
				player->state[2] = '_';
			player->flash_frame++;
		}
	}
}
