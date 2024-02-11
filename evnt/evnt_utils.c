/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evnt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:22:19 by michang           #+#    #+#             */
/*   Updated: 2024/02/11 18:22:20 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "evnt.h"

static void	evnt_toggle_mouse_cursor(int *kb)
{
	(*kb) ^= (1 << KB_1);
	if (*kb & (1 << KB_1))
		mlx_mouse_hide();
	else
		mlx_mouse_show();
}

static void	evnt_forward_set(int *kb, long long time, char press)
{
	static long long	press_gap = 0;
	static long long	first_press = 0;
	static long long	last_release = 0;

	if (*kb & (1 << KB_CROUCH))
		(*kb) = (*kb & ~(1 << KB_FORWARD)) | (press << KB_FORWARD);
	else if (press == TRUE)
	{
		(*kb) |= (1 << KB_FORWARD);
		if (press_gap < 30 && time - last_release < 15)
			(*kb) |= (1 << KB_D_FORWARD);
		else if (first_press == 0)
			first_press = time;
	}
	else
	{
		last_release = time;
		if (*kb & (1 << KB_D_FORWARD))
			last_release = time - 11;
		press_gap = last_release - first_press;
		first_press = 0;
		(*kb) = (*kb) & ~(1 << KB_FORWARD);
		(*kb) = (*kb) & ~(1 << KB_D_FORWARD);
	}
}

void	evnt_shift_set(int *kb, char press)
{
	static char	is_pressed = FALSE;

	if (press == TRUE && is_pressed == FALSE)
	{
		is_pressed = TRUE;
		(*kb) |= (1 << KB_FLASH);
		return ;
	}
	else if (press == FALSE)
		is_pressed = FALSE;
	(*kb) = (*kb & ~(1 << KB_FLASH));
}

void	evnt_keybinds_set(int *kb, int keycode, long long time, char press)
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
	else if (keycode == KEY_SPACE)
		(*kb) = (*kb & ~(1 << KB_JUMP)) | (press << KB_JUMP);
	else if (keycode == KEY_CTRL)
		(*kb) = (*kb & ~(1 << KB_CROUCH)) | (press << KB_CROUCH);
	else if (keycode == KEY_SHIFT)
		evnt_shift_set(kb, press);
	else if (keycode == KEY_E)
		(*kb) = (*kb & ~(1 << KB_RECALL)) | (press << KB_RECALL);
	else if (keycode == KEY_1 && press == TRUE)
		evnt_toggle_mouse_cursor(kb);
	// printf("keybinds:%d\n", *kb);
}
