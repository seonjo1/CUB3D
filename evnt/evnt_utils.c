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
		if (press_gap < 50 && time - last_release < 30)
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

void	evnt_x_set(int *kb, char press, int t_kb, int num)
{
	static char	is_pressed[3];

	if (press == TRUE && is_pressed[num] == FALSE)
	{
		is_pressed[num] = TRUE;
		(*kb) |= (1 << t_kb);
		return ;
	}
	else if (press == FALSE)
		is_pressed[num] = FALSE;
	(*kb) = (*kb & ~(1 << t_kb));
}

void	evnt_reload_set(int *kb, char press)
{
	static char	is_pressed = FALSE;

	if (press == TRUE && is_pressed == FALSE && !(*kb & (1 << KB_RELOAD)))
	{
		(*kb) |= (press << KB_RELOAD);
		is_pressed = TRUE;
	}
	else if (press == FALSE)
		is_pressed = FALSE;
}

void	evnt_attack_set(int *kb, char press)
{
	static char	is_pressed = FALSE;

	if (press == TRUE && is_pressed == FALSE && !(*kb & (1 << KB_LEFT)))
	{
		(*kb) |= (press << KB_ATTACK);
		is_pressed = TRUE;
	}
	else if (press == FALSE)
		is_pressed = FALSE;
}
