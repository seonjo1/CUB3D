/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_shot_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:36:28 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:04:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hand_bonus.h"
#include "../sound/sound_bonus.h"

int	hand_reset_reload(int *kb, int *rf, char set, unsigned int c)
{
	static unsigned int	channel = 0;

	if (set == TRUE)
		channel = c;
	else
	{
		if (channel)
			sound_stop(channel);
		channel = 0;
		(*rf) = 0;
		(*kb) = (*kb & ~(1 << KB_RELOAD));
	}
	return (0);
}

void	*hand_action_reload(void **arr, t_player *player, int *magazine)
{
	hand_stop_shot(FALSE, 0);
	if (player->reload_frame == 4)
		hand_reset_reload(0, 0, TRUE, sound_play(player->s_res->reload));
	player->reload_frame++;
	if (player->reload_frame >= (HN_RELOAD << 1))
	{
		player->reload_frame = 0;
		*magazine = MAX_MAG;
		player->keybinds = player->keybinds & ~(1 << KB_RELOAD);
	}
	return (arr[player->reload_frame >> 1]);
}

void	*hand_action_shot(void **arr, t_data *data, int *magazine)
{
	static long long	time = 0;
	static int			t = 0;

	if (*magazine > 0)
	{
		if (data->time - 1 != time)
			hand_stop_shot(TRUE, sound_play(data->s_res.gun));
		time = data->time;
		(*magazine)--;
		if (++t == ((HN_SHOT - 1) << 1))
			t = 0;
		return (arr[t >> 1]);
	}
	data->player.keybinds |= (1 << KB_RELOAD);
	return (arr[HN_SHOT - 1]);
}

int	hand_stop_shot(char set, unsigned int c)
{
	static unsigned int	channel = 0;

	if (set == TRUE)
		channel = c;
	else if (channel)
		sound_stop(channel);
	return (0);
}
