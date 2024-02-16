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

int	evnt_mousepress(int keycode, int x, int y, t_player *player)
{
	int	*kb;

	printf("keycode:%d\n", keycode);
	kb = &(player->keybinds);
	if (keycode == MOUSE_RIGHT)
		evnt_shift_set(&(player->keybinds), TRUE);
	if (keycode == MOUSE_LEFT || keycode == MOUSE_OTHER)
		(*kb) |= (1 << KB_M_LEFT);
	return (x + y);
}

int	evnt_mouserelease(int keycode, int x, int y, t_player *player)
{
	int	*kb;

	kb = &(player->keybinds);
	if (keycode == MOUSE_RIGHT)
		evnt_shift_set(&(player->keybinds), FALSE);
	if (keycode == MOUSE_LEFT || keycode == MOUSE_OTHER)
		(*kb) = (*kb & ~(1 << KB_M_LEFT));
	return (x + y);
}

int	evnt_keypress(int keycode, t_player *player)
{
	// printf("keycode: %d %p\n", keycode, &(player->keybinds));
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
