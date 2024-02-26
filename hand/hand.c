/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:39:49 by michang           #+#    #+#             */
/*   Updated: 2024/02/14 18:39:49 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hand.h"
#include "../sound/sound.h"
#include "../libft_s/libft_s.h"

int	hand_stop_shot(char set, unsigned int c)
{
	static unsigned int	channel = 0;

	if (set == TRUE)
		channel = c;
	else if (channel)
		sound_stop(channel);
	return (0);
}

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

static void	hand_init_each(t_data *data, void **arr, int max, char *base)
{
	char	*tmp;
	char	*file_name;
	int		i;
	int		w;
	int		h;

	i = 0;
	while (i < max)
	{
		tmp = ft_itoa_s(i);
		file_name = ft_strjoin_s(base, tmp);
		free(tmp);
		tmp = file_name;
		file_name = ft_strjoin_s(file_name, ".xpm");
		free(tmp);
		printf("file:%s load\n", file_name);
		arr[i] = mlx_xpm_file_to_image(data->mlx, file_name, &w, &h);
		if (!arr[i])
			exit(1);
		free(file_name);
		i++;
	}
}

void	hand_init_xpm_imgs(t_data *data)
{
	hand_init_each(data, data->h_res.flash, HN_FLASH, "res/flash/flash_");
	hand_init_each(data, data->h_res.attack, HN_ATTACK, "res/attack/attack_");
	hand_init_each(data, data->h_res.pulse, HN_PULSE, "res/pulse/pulse_");
	hand_init_each(data, data->h_res.recall, HN_RECALL, "res/recall/recall_");
	hand_init_each(data, data->h_res.reload, HN_RELOAD, "res/reload/reload_");
	hand_init_each(data, data->h_res.shot, HN_SHOT, "res/shot/shot_");
	hand_init_each(data, data->h_res.walk, HN_WALK, "res/walk/walk_");
}

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
	t =  HN_RECALL * player->recall.frame / (double) RECALL_STORE_MAX;
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

void	*hand_action_reload(void **arr, t_player *player, int *magazine)
{
	hand_stop_shot(FALSE, 0);
	if (player->reload_frame == 7)
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

void	*hand_update(t_data *data)
{
	static void	*hand = 0;
	static int	magazine = MAX_MAG;
	char		*ps;
	
	ps = data->player.state;
	if (ps[2] == 'R')
		hand = hand_action_recall(data->h_res.recall, &(data->player), &magazine);
	else if (data->player.keybinds & (1 << KB_ATTACK))
		hand = hand_action_attack(data->h_res.attack, &(data->player));
	else if ((data->player.keybinds & (1 << KB_RELOAD) && magazine != MAX_MAG) || magazine == 0)
		hand = hand_action_reload(data->h_res.reload, &(data->player), &magazine);
	else if (ps[2] == 'F')
		hand = hand_action_flash(data->h_res.flash, &(data->player));
	else if (data->player.keybinds & (1 << KB_M_LEFT))
		hand = hand_action_shot(data->h_res.shot, data, &magazine);
	else if (!ft_strncmp(ps, "W__", 4))
		hand = hand_action_walk(&(data->player), data->h_res.walk, 2);
	else if (!ft_strncmp(ps, "R__", 4))
		hand = hand_action_walk(&(data->player), data->h_res.walk, 1);
	else
	{
		hand_stop_shot(FALSE, 0);
		hand_action_walk(&(data->player), data->h_res.walk, 0);
		hand = data->h_res.walk[0];
	}
	return (hand);
}
