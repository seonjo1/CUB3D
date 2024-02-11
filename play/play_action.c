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

void	play_action_movement(t_player *player)
{
	char	*ps;

	ps = player->state;
	if (ps[0] == 'W')
	{
		if (!(player->move.x || player->move.y) && ps[1] == '_')
			player->pos.z = sin(player->time++ / (double)25.0) * 20;
		else if (ps[1] == '_')
		{
			player->pos.z = sin(player->time / (double)25.0) * 30;
			player->time += 5;
		}
		vec2_normalize(&(player->move), 0.0085);
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (ps[0] == 'R')
	{
		vec2_normalize(&(player->move), 0.0085 * 1.5);
		if (ps[1] == '_')
		{
			player->pos.z = sin(player->time / (double)25.0) * 50;
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
		player->motion.z = 45;
	}
	else if (enter == RUN)
	{
		if (player->state[1] == 'J')
		{
			player->pos.z += player->motion.z;
			player->motion.z -= 2.5;
			if (player->motion.z < -45)
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
		vec2_normalize(&(player->move), 0.0085 * 0.25);
	}
	else if (enter == RUN && player->state[1] == 'c')
	{
		if (play_target_update(&(player->pos.z), 0, 30, 40))
			ft_strlcpy(player->state, "W__", 4);
	}
}
