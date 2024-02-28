   /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evnt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:11:02 by michang           #+#    #+#             */
/*   Updated: 2024/02/08 14:11:03 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evnt.h"

int	evnt_leave(int keycode, int tmp)
{
	keycode = tmp;
	exit(0);
	return (0);
}

int	evnt_mousepress(int keycode, int x, int y, t_data *data)
{
	int	*kb;

	printf("keycode:%d\n", keycode);
	kb = &(data->player.keybinds);
	if (keycode == MOUSE_RIGHT)
		evnt_x_set(&(data->player.keybinds), 1, KB_FLASH, 0);
	if (keycode == MOUSE_LEFT || keycode == MOUSE_OTHER)
		(*kb) |= (1 << KB_M_LEFT);
	if (keycode == MOUSE_UP && data->mini.ratio < 40)
		data->mini.ratio *= 1.1;
	if (keycode == MOUSE_DOWN && data->mini.ratio > 1)
		data->mini.ratio *= 0.9;
	return (x + y);
}

int	evnt_mouserelease(int keycode, int x, int y, t_player *player)
{
	int	*kb;

	kb = &(player->keybinds);
	if (keycode == MOUSE_RIGHT)
		evnt_x_set(&(player->keybinds), 0, KB_FLASH, 0);
	if (keycode == MOUSE_LEFT || keycode == MOUSE_OTHER)
		(*kb) = (*kb & ~(1 << KB_M_LEFT));
	return (x + y);
}

int	evnt_keypress(int keycode, t_player *player)
{
	if (keycode == KEY_ESC)
		exit(0);
	else
		evnt_keybinds_set(&(player->keybinds), keycode, player->time, TRUE);
	return (0);
}

int	evnt_keyrelease(int keycode, t_player *player)
{
	evnt_keybinds_set(&(player->keybinds), keycode, player->time, FALSE);
	return (0);
}
