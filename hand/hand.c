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

void	hand_action_walk(t_player *player)
{
	
}

void	hand_state_update(t_player *player)
{
	char		*ps;
	t_h_state	*hs;

	ps = player->state;
	hs = &(player->h_state);
	if (ft_strncmp(ps, "W__", 4))
		*hs = HS_WALK;
	else if (ft_strncmp(ps, "R__", 4))
		*hs = HS_RUN;
	else if (ft_strncmp(ps, "WC_", 4))
		*hs = HS_NONE;
	else if (ps[1] == 'J')
		*hs = HS_NONE;
	else if (ps[2] == 'F')
		*hs = HS_FLASH;
	else if (ps[2] == 'R')
		*hs = HS_RECALL;
}

void	hand_update(t_data *data)
{
	hand_state_update(&(data->player));
}
