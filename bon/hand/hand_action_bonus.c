/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_action_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:35:51 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:04:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hand_bonus.h"
#include "../sound/sound_bonus.h"

void	*hand_action_walk(t_player *player, void **arr, int delay)
{
	static int	chennel[2] = {0, 0};
	static int	cnt = 0;
	static int	t = 0;

	if (chennel[0] == 0)
	{
		chennel[0] = sound_play_loop(player->s_res->walk);
		chennel[1] = sound_play_loop(player->s_res->run);
	}
	hand_stop_shot(FALSE, 0);
	sound_pause(chennel[0]);
	sound_pause(chennel[1]);
	if (!(player->move.x || player->move.y) || delay == 0)
		return (arr[t]);
	else if (delay == 2)
		sound_resume(chennel[0]);
	else if (delay == 1)
		sound_resume(chennel[1]);
	if (++cnt > delay)
	{
		cnt = 0;
		if (++t == HN_WALK)
			t = 0;
	}
	return (arr[t]);
}

void	*hand_action_recall(void **arr, t_player *player, int *magazine)
{
	int	t;

	hand_reset_reload(&(player->keybinds), &(player->reload_frame), FALSE, 0);
	hand_stop_shot(FALSE, 0);
	if (player->recall.frame == 2)
		sound_play(player->s_res->recall);
	t = HN_RECALL * player->recall.frame / (double) RECALL_STORE_MAX;
	if (t == HN_RECALL - 1)
		*magazine = MAX_MAG;
	return (arr[t]);
}

void	*hand_action_flash(void **arr, t_player *player)
{
	int	t;

	hand_stop_shot(FALSE, 0);
	t = player->flash_frame - 1;
	if (player->flash_frame >= HN_FLASH)
		t = HN_FLASH - 1;
	return (arr[t]);
}

void	*hand_action_attack(void **arr, t_player *player)
{
	static int	t = 0;

	hand_reset_reload(&(player->keybinds), &(player->reload_frame), FALSE, 0);
	hand_stop_shot(FALSE, 0);
	if (t == 0)
		sound_play(player->s_res->attack);
	if (++t == (HN_ATTACK << 1))
	{
		player->keybinds = (player->keybinds & ~(1 << KB_ATTACK));
		t = 0;
		return (arr[HN_ATTACK - 1]);
	}
	return (arr[(t - 1) >> 1]);
}
