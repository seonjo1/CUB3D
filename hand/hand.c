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

int	hand_reset_reload(int *kb, int *rf)
{
	(*rf) = 0;
	(*kb) = (*kb & ~(1 << KB_RELOAD));
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
	static int	cnt = 0;
	static int	t = 0;

	if (!(player->move.x || player->move.y))
		return (arr[t]);
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

	hand_reset_reload(&(player->keybinds), &(player->reload_frame));
	if (player->recall.frame >= HN_RECALL << 1)
	{
		t = HN_RECALL - 1;
		*magazine = 50;
	}
	else
		t = (player->recall.frame >> 1);
	return (arr[t]);
}

void	*hand_action_flash(void **arr, t_player *player)
{
	int	t;

	t = player->flash_frame - 1;
	if (player->flash_frame >= HN_FLASH)
		t = HN_FLASH - 1;
	return (arr[t]);
}

void	*hand_action_shot(void **arr, int *kb, int *magazine)
{
	static int	t = 0;

	if (*magazine >= 0)
	{
		(*magazine)--;
		if (++t == ((HN_SHOT - 1) << 1))
			t = 0;
		return (arr[t >> 1]);
	}
	*kb |= (1 << KB_RELOAD);
	return (arr[HN_SHOT - 1]);
}

void	*hand_action_attack(void **arr,  t_player *player)
{
	static int	t = 0;

	hand_reset_reload(&(player->keybinds), &(player->reload_frame));
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

void	*hand_action_reload(void **arr, int *kb, int *rf, int *magazine)
{
	(*rf)++;
	if (*rf >= (HN_RELOAD << 1))
	{
		(*rf) = 0;
		*magazine = 50;
		(*kb) = (*kb & ~(1 << KB_RELOAD));
	}
	return (arr[(*rf) >> 1]);
}

void	*hand_update(t_data *data)
{
	static void	*hand;
	char		*ps;
	static int	magazine = 50;
	
	ps = data->player.state;
	if (ps[2] == 'R')
		hand = hand_action_recall(data->h_res.recall, &(data->player), &magazine);
	else if (data->player.keybinds & (1 << KB_ATTACK))
		hand = hand_action_attack(data->h_res.attack, &(data->player));
	else if (data->player.keybinds & (1 << KB_RELOAD) && magazine != 50)
		hand = hand_action_reload(data->h_res.reload, &(data->player.keybinds), &(data->player.reload_frame), &magazine);
	else if (ps[2] == 'F')
		hand = hand_action_flash(data->h_res.flash, &(data->player));
	else if (data->player.keybinds & (1 << KB_M_LEFT))
		hand = hand_action_shot(data->h_res.shot, &(data->player.keybinds), &magazine);
	else if (!ft_strncmp(ps, "W__", 4))
		hand = hand_action_walk(&(data->player), data->h_res.walk, 3);
	else if (!ft_strncmp(ps, "R__", 4))
		hand = hand_action_walk(&(data->player), data->h_res.walk, 1);
	else
		hand = data->h_res.walk[0];
	return (hand);
}
