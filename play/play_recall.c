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
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
			printf(" ==> ");
		printf("(id:%d, x:%.3f, y:%.3f", (idx + i) % 10, pos[(idx + i) % 10].x, pos[(idx + i) % 10].y);
		printf(", yaw: %.3f)", euler_dir[(idx + i) % 10].y);
	}
	printf("\n\n");
}

void	play_action_recall(t_player *player, t_recall *re, char enter)
{
	static int	save_freq = 0;

	if (enter == ENTER)
	{
		player->keybinds = (player->keybinds & ~(1 << KB_RECALL));
		ft_strlcpy(player->state, "__R", 4);
	}
	else if (enter == RUN)
	{
		if (player->state[2] == 'R')
		{

		}
		else if (++save_freq > 15)
		{
			re->idx++;
			re->pos[re->idx] = player->pos;
			re->euler_dir[re->idx] = player->euler_dir;
			save_freq = 0;
			play_test_lst_print(player);
		}
	}
}
