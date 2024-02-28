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
		printf("file:%s load\n", file_name);
		tmp = file_name;
		file_name = ft_strjoin_s(file_name, ".xpm");
		free(tmp);
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
	hand_init_each(data, data->h_res.recall, HN_RECALL, "res/recall/recall_");
	hand_init_each(data, data->h_res.reload, HN_RELOAD, "res/reload/reload_");
	hand_init_each(data, data->h_res.shot, HN_SHOT, "res/shot/shot_");
	hand_init_each(data, data->h_res.walk, HN_WALK, "res/walk/walk_");
}

void	*hand_call_action(t_data *dt)
{
	void		*hand;
	char		*ps;
	static int	magazine = MAX_MAG;

	ps = dt->player.state;
	if (ps[2] == 'R')
		hand = hand_action_recall(dt->h_res.recall, &(dt->player), &magazine);
	else if (dt->player.keybinds & (1 << KB_ATTACK))
		hand = hand_action_attack(dt->h_res.attack, &(dt->player));
	else if ((dt->player.keybinds & (1 << KB_RELOAD) && magazine != MAX_MAG)
		|| magazine == 0)
		hand = hand_action_reload(dt->h_res.reload, &(dt->player), &magazine);
	else if (ps[2] == 'F')
		hand = hand_action_flash(dt->h_res.flash, &(dt->player));
	else if (dt->player.keybinds & (1 << KB_M_LEFT))
		hand = hand_action_shot(dt->h_res.shot, dt, &magazine);
	else if (!ft_strncmp(ps, "W__", 4))
		hand = hand_action_walk(&(dt->player), dt->h_res.walk, 2);
	else if (!ft_strncmp(ps, "R__", 4))
		hand = hand_action_walk(&(dt->player), dt->h_res.walk, 1);
	else
		return (0);
	return (hand);
}

void	*hand_update(t_data *data)
{
	void	*hand;

	hand = hand_call_action(data);
	if (!hand)
	{
		hand_stop_shot(FALSE, 0);
		hand_action_walk(&(data->player), data->h_res.walk, 0);
		hand = data->h_res.walk[0];
	}
	return (hand);
}
