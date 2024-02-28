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
#include "../libft_s/libft_s.h"

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
