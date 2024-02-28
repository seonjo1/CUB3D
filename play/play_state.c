/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:13:52 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 18:13:53 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play.h"

static void	play_state_transition_2(t_player *player, char *ps, int kb)
{
	if (!ft_strncmp(ps, "W__", 4))
	{
		if (kb & (1 << KB_D_FORWARD))
			ft_strlcpy(ps, "R__", 4);
		else if (kb & (1 << KB_CROUCH))
			play_action_crouch(player, "WC_", ENTER);
		else if (kb & (1 << KB_JUMP))
			play_action_jump(player, "WJ_", ENTER);
		else if (kb & (1 << KB_FLASH) && !(kb & (1 << KB_ATTACK)))
			play_action_flash(player, "W_F", ENTER);
		else if (kb & (1 << KB_RECALL) && !(kb & (1 << KB_ATTACK)))
			play_action_recall(player, &(player->recall), ENTER);
	}
	else if (!ft_strncmp(ps, "RJ_", 4))
	{
		if (!(kb & (1 << KB_D_FORWARD)))
			ft_strlcpy(ps, "WJ_", 4);
		else if (kb & (1 << KB_FLASH) && !(kb & (1 << KB_ATTACK)))
			play_action_flash(player, "RJF", ENTER);
		else if (kb & (1 << KB_RECALL) && !(kb & (1 << KB_ATTACK)))
			play_action_recall(player, &(player->recall), ENTER);
	}
}

static void	play_state_transition_1(t_player *player, char *ps, int kb)
{
	if (!ft_strncmp(ps, "R__", 4))
	{
		if (!(kb & (1 << KB_D_FORWARD)))
			ft_strlcpy(ps, "W__", 4);
		else if (kb & (1 << KB_CROUCH))
			play_action_crouch(player, "WC_", ENTER);
		else if (kb & (1 << KB_JUMP))
			play_action_jump(player, "RJ_", ENTER);
		else if (kb & (1 << KB_FLASH) && !(kb & (1 << KB_ATTACK)))
			play_action_flash(player, "R_F", ENTER);
		else if (kb & (1 << KB_RECALL) && !(kb & (1 << KB_ATTACK)))
			play_action_recall(player, &(player->recall), ENTER);
	}
	else if (!ft_strncmp(ps, "WC_", 4))
	{
		if (!(kb & (1 << KB_CROUCH)))
			ft_strlcpy(ps, "Wc_", 4);
	}
	else if (!ft_strncmp(ps, "WJ_", 4))
	{
		if (kb & (1 << KB_FLASH) && !(kb & (1 << KB_ATTACK)))
			play_action_flash(player, "WJF", ENTER);
		else if (kb & (1 << KB_RECALL) && !(kb & (1 << KB_ATTACK)))
			play_action_recall(player, &(player->recall), ENTER);
	}
}

void	play_state_transition(t_player *player)
{
	char	*ps;
	int		kb;

	ps = player->state;
	kb = player->keybinds;
	if (!kb)
		return ;
	play_state_transition_1(player, ps, kb);
	play_state_transition_2(player, ps, kb);
}
