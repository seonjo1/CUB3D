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

void	play_test_lst_print(t_player *player)
{
	t_vec3	*pos;
	t_vec2	*euler_dir;
	int		idx;

	pos = player->recall.pos;
	euler_dir = player->recall.euler_dir;
	idx = player->recall.idx;
	for (int i = 0; i < RECALL_STORE_MAX; i++)
	{
		if (i != 0)
			printf(" ==> ");
		printf("(id:%d, x:%.3f, y:%.3f", (idx + i) % RECALL_STORE_MAX, \
			pos[(idx + i) % RECALL_STORE_MAX].x, pos[(idx + i) % RECALL_STORE_MAX].y);
		printf(", yaw: %.3f)", euler_dir[(idx + i) % RECALL_STORE_MAX].y);
	}
	printf("\n\n");
}

void	play_recall_doing(t_player *player, t_recall *re)
{
	if (re->frame < RECALL_STORE_MAX)
	{
		player->pos = re->pos[re->idx];
		player->euler_dir = re->euler_dir[re->idx];
	}
	else
	{
		player->pos.z = 0;
		player->move.x = 0;
		player->move.y = 0;
		if (re->frame == RECALL_STORE_MAX + 5)
			ft_strlcpy(player->state, "W__", 4);
	}
	re->frame++;
	re->idx--;
	if (re->idx == -1)
		re->idx = RECALL_STORE_MAX - 1;
}

void	play_recall_enter(t_player *player, t_recall *re)
{
	player->keybinds = (player->keybinds & ~(1 << KB_RECALL));
	ft_strlcpy(player->state, "__R", 4);
	re->frame = 0;
	re->cooldown = RECALL_COOLDOWN;
	play_test_lst_print(player);
}

void	play_action_recall(t_player *player, t_recall *re, char enter)
{
	static int	save_freq = 0;

	if (enter == ENTER && re->cooldown < 0)
		play_recall_enter(player, re);
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
