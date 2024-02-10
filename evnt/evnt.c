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

void	evnt_forward_set(int *kb, long long time, char press)
{
	static long long	press_gap = 0;
	static long long	first_press = 0;
	static long long	last_release = 0;

	if (press == TRUE)
	{
		printf("%lld %lld %lld %lld\n", time, last_release, first_press, press_gap);
		(*kb) |= (1 << KB_FORWARD);
		if (press_gap < 30 && time - last_release < 15)
			(*kb) |= (1 << KB_D_FORWARD);
		else if (first_press == 0)
			first_press = time;
	}
	else
	{
		if (*kb & (1 << KB_D_FORWARD))
			last_release = time - 11;
			last_release = time;
		press_gap = last_release - first_press;
		first_press = 0;
		*kb = *kb & ~(1 << KB_FORWARD);
		*kb = *kb & ~(1 << KB_D_FORWARD);
	}
}

static void	evnt_keybinds_set(int *kb, int keycode, long long time, char press)
{
	if (keycode == KEY_W)
		evnt_forward_set(kb, time, press);
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
		(*kb) = (*kb & ~(1 << KB_FLASH)) | (press << KB_FLASH);
	else if (keycode == KEY_SPACE)
		(*kb) = (*kb & ~(1 << KB_JUMP)) | (press << KB_JUMP);
	else if (keycode == KEY_CTRL)
		(*kb) = (*kb & ~(1 << KB_CROUCH)) | (press << KB_CROUCH);
	else if (keycode == KEY_E)
		(*kb) = (*kb & ~(1 << KB_FLASH)) | (press << KB_FLASH);
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
		evnt_keybinds_set(&(player->keybinds), keycode, player->time, TRUE);
	return (0);
}

int	evnt_keyrelease(int keycode, t_player *player)
{
	evnt_keybinds_set(&(player->keybinds), keycode, player->time, FALSE);
	return (0);
}
