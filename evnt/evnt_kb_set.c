/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evnt_kb_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:28:46 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 17:28:47 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evnt.h"

static void	evnt_keybinds_set_skill(int *kb, int keycode, char press)
{
	if (keycode == KEY_SHIFT)
		evnt_x_set(kb, press, KB_FLASH, 0);
	else if (keycode == KEY_E)
		evnt_x_set(kb, press, KB_RECALL, 1);
	else if (keycode == KEY_1 && press == TRUE)
		evnt_toggle_mouse_cursor(kb);
	else if (keycode == KEY_V)
		evnt_attack_set(kb, press);
	else if (keycode == KEY_R)
		evnt_reload_set(kb, press);
}

void	evnt_keybinds_set(int *kb, int keycode, long time, char press)
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
	else if (keycode == KEY_UP)
		(*kb) = (*kb & ~(1 << KB_ROTATE_UP)) | (press << KB_ROTATE_UP);
	else if (keycode == KEY_DOWN)
		(*kb) = (*kb & ~(1 << KB_ROTATE_DOWN)) | (press << KB_ROTATE_DOWN);
	else if (keycode == KEY_SPACE)
		(*kb) = (*kb & ~(1 << KB_JUMP)) | (press << KB_JUMP);
	else if (keycode == KEY_CTRL)
		(*kb) = (*kb & ~(1 << KB_CROUCH)) | (press << KB_CROUCH);
	else
		evnt_keybinds_set_skill(kb, keycode, press);
}
