/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_action_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:42:45 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:04:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play_bonus.h"
#include "../sound/sound_bonus.h"
#include "../libft_s/libft_s_bonus.h"

void	play_action_walk_run(t_player *player)
{
	char	*ps;

	ps = player->state;
	if (ps[0] == 'W' && ps[2] == '_')
	{
		if (!(player->move.x || player->move.y) && ps[1] == '_')
			player->euler_dir.x += sin(player->time++ / (double)25.0) * 0.5;
		else if (ps[1] == '_')
		{
			player->euler_dir.x += sin(player->time / (double)25.0);
			player->time += 6;
		}
		player->move = vec2_normalize(player->move, 0.0085);
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (ps[0] == 'R' && ps[2] == '_')
	{
		player->move = vec2_normalize(player->move, 0.0085 * 1.5);
		if (ps[1] == '_')
		{
			player->euler_dir.x += sin(player->time / (double)25.0) * 2;
			player->time += 7;
		}
		play_target_update(&(player->fov), FOV_BASE * 1.01, 0.015, 0.03);
	}
}

void	play_action_jump(t_player *player, char *transition, char enter)
{
	if (enter == ENTER)
	{
		ft_strlcpy(player->state, transition, 4);
		player->motion_dir.z = 40;
	}
	else if (enter == RUN)
	{
		if (player->state[1] == 'J')
		{
			play_target_update(&(player->motion.z), 0, 2, 4);
			player->pos.z += player->motion_dir.z;
			player->motion_dir.z -= 2.5;
			if (player->motion_dir.z < -40)
			{
				player->state[1] = '_';
				player->pos.z = Z_BASE;
				sound_play(player->s_res->landing);
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
		play_target_update(&(player->pos.z), 50, 30, 40);
		player->move = vec2_normalize(player->move, 0.0085 * 0.25);
	}
	else if (enter == RUN && player->state[1] == 'c')
	{
		if (play_target_update(&(player->pos.z), Z_BASE, 30, 40))
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
		player->motion.x = 0;
		player->motion.y = 0;
		if (!(player->move.x || player->move.y))
			flash_dir = vec2_creat(1, 0);
		player->flash_frame = 0;
		flash_dir = vec2_normalize(flash_dir, 0.0085 * 110);
		sound_play(player->s_res->flash[abs((int)(player->dir.x * 100)) % 3]);
	}
	else if (enter == RUN && player->state[2] == 'F')
	{
		player->move = flash_dir;
		flash_dir = vec2_scala_mul(flash_dir, 0.075);
		if (player->flash_frame == HN_FLASH)
			player->state[2] = '_';
		player->flash_frame++;
	}
}
