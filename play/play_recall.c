/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_recall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:53:01 by michang           #+#    #+#             */
/*   Updated: 2024/02/11 20:53:02 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play.h"

void	play_recall_doing(t_player *player, t_recall *re)
{
	if (re->frame < RECALL_STORE_MAX)
	{
		if (re->frame < RECALL_STORE_MAX * 3 / 4)
			player->fov += 0.01;
		else
			player->fov -= 0.03;
		player->pos = re->pos[re->idx];
		player->euler_dir = re->euler_dir[re->idx];
	}
	else
	{
		player->fov = FOV_BASE;
		player->pos.z = Z_BASE;
		player->motion.x = 0;
		player->motion.y = 0;
		if (re->frame == RECALL_STORE_MAX + 5)
			ft_strlcpy(player->state, "W__", 4);
	}
	re->frame++;
	re->idx--;
	if (re->idx == -1)
		re->idx = RECALL_STORE_MAX - 1;
}

void	play_action_recall(t_player *player, t_recall *re, char enter)
{
	static int	save_freq = 0;

	if (enter == ENTER && re->cooldown < 0)
	{
		player->keybinds = (player->keybinds & ~(1 << KB_RECALL));
		ft_strlcpy(player->state, "__R", 4);
		re->frame = 0;
		re->cooldown = RECALL_COOLDOWN;
	}
	else if (enter == RUN)
	{
		re->cooldown--;
		if (player->state[2] == 'R')
			play_recall_doing(player, re);
		else if (++save_freq > (150 / RECALL_STORE_MAX))
		{
			re->idx = (re->idx + 1) % RECALL_STORE_MAX;
			re->pos[re->idx] = player->pos;
			re->euler_dir[re->idx] = player->euler_dir;
			save_freq = 0;
		}
	}
}
