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

static void	evnt_mouse_cursor(int *kb)
{
	(*kb) ^= (1 << KB_1);
	if (*kb & (1 << KB_1))
		mlx_mouse_hide();
	else
		mlx_mouse_show();
}

static void	evnt_keybinds_set(int *kb, int keycode, char press)
{
	if (keycode == KEY_W)
		(*kb) = (*kb & ~(1 << KB_FORWARD)) | (press << KB_FORWARD);
	else if (keycode == KEY_S)
		(*kb) = (*kb & ~(1 << KB_BACKWARD)) | (press << KB_BACKWARD);
	else if (keycode == KEY_A)
		(*kb) = (*kb & ~(1 << KB_LEFT)) | (press << KB_LEFT);
	else if (keycode == KEY_D)
		(*kb) = (*kb & ~(1 << KB_RIGHT)) | (press << KB_RIGHT);
	else if (keycode == KEY_LEFT)
		(*kb) = (*kb & ~(1 << KB_ROTATE_LEFT)) | (press << KB_ROTATE_LEFT);
	else if (keycode == KEY_RIGHT)
		(*kb) = (*kb & ~(1 << KB_ROTATE_RIGHT)) | (press << KB_ROTATE_RIGHT);
	else if (keycode == KEY_SHIFT)
		(*kb) = (*kb & ~(1 << KB_SHITF)) | (press << KB_SHITF);
	else if (keycode == KEY_1 && press == TRUE)
		evnt_mouse_cursor(kb);
	// printf("keybinds:%d\n", *kb);
}

int	evnt_leave(int keycode, int tmp)
{
	keycode = tmp;
	exit(0);
	return (0);
}

int	evnt_keypress(int keycode, t_player *player)
{
	// printf("keycode:%d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	else
		evnt_keybinds_set(&(player->keybinds), keycode, TRUE);
	return (0);
}

int	evnt_keyrelease(int keycode, t_player *player)
{
	evnt_keybinds_set(&(player->keybinds), keycode, FALSE);
	return (0);
}
