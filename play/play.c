/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:00:08 by michang           #+#    #+#             */
/*   Updated: 2024/02/07 18:00:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "play.h"
#include "../libft_s/libft_s.h"

void	play_dir_update(t_data *data)
{
	static unsigned int	delay = 0;
	int					kb;
	t_intvec2			mouse_pos;

	kb = data->player.keybinds;
	if (kb & (1 << KB_1))
	{
		mlx_mouse_get_pos(data->mlx_win, &(mouse_pos.x), &(mouse_pos.y));
		mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		delay++;
		if (delay >= 5)
		{
			if (mouse_pos.x - WIN_WIDTH / 2 != 0)
				data->player.motion_dir.y = (mouse_pos.x - WIN_WIDTH / 2) / 314.0;
			else
				data->player.motion_dir.y *= 0.795;
			delay = data->player.time;
		}
	}
	else
		delay = 0;
	if (!(kb & (1 << KB_ROTATE_LEFT)) && kb & (1 << KB_ROTATE_RIGHT))
		data->player.motion_dir.y = 0.02;
	else if (!(kb & (1 << KB_ROTATE_RIGHT)) && kb & (1 << KB_ROTATE_LEFT))
		data->player.motion_dir.y = -0.02;
	else
		data->player.motion_dir.y *= 0.795;
}

void	play_dir_plane_set(t_player *player)
{
	double	sn;
	double	cs;

	sn = sin(player->euler_dir.y);
	cs = cos(player->euler_dir.y);
	player->dir = vec2_creat(cs, sn);
	player->plane = vec2_scala_mul(vec2_creat(-sn, cs), tan(player->fov / 2.0));
}

void	play_movement_update(t_player *player)
{
	int	kb;
	
	kb = player->keybinds;
	player->move.x = 0;
	if (!(kb & (1 << KB_FORWARD) && kb & (1 << KB_BACKWARD)))
	{
		if (kb & (1 << KB_FORWARD))
			player->move.x = 1;
		else if (kb & (1 << KB_BACKWARD))
			player->move.x = -1;
	}
	player->move.y = 0;
	if (!(kb & (1 << KB_LEFT) && kb & (1 << KB_RIGHT)))
	{
		if (kb & (1 << KB_LEFT))
			player->move.y = -1;
		else if (kb & (1 << KB_RIGHT))
			player->move.y = 1;
	}
}

int	play_target_update(double *target, double goal, double delta, double offset)
{
	if (*target + offset < goal)
		*target += delta;
	else if (*target - offset > goal)
		*target -= delta;
	else
	{
		*target = goal;
		return (1);
	}
	return (0);
}

void	play_action_jump(t_player *player, char *transition, char enter)
{
	if (enter == ENTER)
	{
		ft_strlcpy(player->state, transition, 4);
		player->motion.z = 45;
	}
	else if (enter == RUN)
	{
		if (player->state[1] == 'J')
		{
			player->pos.z += player->motion.z;
			player->motion.z -= 2.5;
			if (player->motion.z < -45)
			{
				player->state[1] = '_';
				player->pos.z = 0;
			}
		}
	}
}

void	play_action_crouch(t_player *player, char *transition, char enter)
{
	if (enter == ENTER)
		ft_strlcpy(player->state, transition, 4);
	else if (enter == RUN && player->state[1] == 'C')
	{
		play_target_update(&(player->pos.z), -150, 30, 40);
		vec2_normalize(&(player->move), 0.0085 * 0.25);
	}
	else if (enter == RUN && player->state[1] == 'c')
	{
		if (play_target_update(&(player->pos.z), 0, 30, 40))
			ft_strlcpy(player->state, "W__", 4);
	}
}

void	play_transition_by_key_event(t_player *player)
{
	char	*ps;
	int		kb;

	ps = player->state;
	kb = player->keybinds;
	if (!kb)
		return ;
	if (!ft_strncmp(ps, "W__", 4))
	{
		if (kb & (1 << KB_D_FORWARD))
			ft_strlcpy(ps, "R__", 4);
		else if (kb & (1 << KB_CROUCH))
			play_action_crouch(player, "WC_", ENTER);
		else if (kb & (1 << KB_JUMP))
			play_action_jump(player, "WJ_", ENTER);
		else if (kb & (1 << KB_FLASH))
			ft_strlcpy(ps, "W_F", 4);
		else if (kb & (1 << KB_RECALL))
			ft_strlcpy(ps, "__R", 4);
	}
	else if (!ft_strncmp(ps, "R__", 4))
	{
		if (!(kb & (1 << KB_D_FORWARD)))
			ft_strlcpy(ps, "W__", 4);
		else if (kb & (1 << KB_CROUCH))
			play_action_crouch(player, "WC_", ENTER);
		else if (kb & (1 << KB_JUMP))
			play_action_jump(player, "RJ_", ENTER);
		else if (kb & (1 << KB_FLASH))
			ft_strlcpy(ps, "R_F", 4);
		else if (kb & (1 << KB_RECALL))
			ft_strlcpy(ps, "__R", 4);
	}
	else if (!ft_strncmp(ps, "WC_", 4))
	{
		if (!(kb & (1 << KB_CROUCH)))
			ft_strlcpy(ps, "Wc_", 4);
	}
	else if (!ft_strncmp(ps, "WJ_", 4))
	{
		if (kb & (1 << KB_FLASH))
			ft_strlcpy(ps, "WJF", 4);
		else if (kb & (1 << KB_RECALL))
			ft_strlcpy(ps, "__F", 4);
	}
	else if (!ft_strncmp(ps, "RJ_", 4))
	{
		if (!(kb & (1 << KB_D_FORWARD)))
			ft_strlcpy(ps, "WJ_", 4);
		else if (kb & (1 << KB_FLASH))
			ft_strlcpy(ps, "RJF", 4);
		else if (kb & (1 << KB_RECALL))
			ft_strlcpy(ps, "__R", 4);
	}
}

void	play_action_movement(t_player *player)
{
	char	*ps;

	ps = player->state;
	if (ps[0] == 'W')
	{
		if (!(player->move.x || player->move.y) && ps[1] == '_')
			player->pos.z = sin(player->time++ / (double)25.0) * 20;
		else if (ps[1] == '_')
		{
			player->pos.z = sin(player->time / (double)25.0) * 30;
			player->time += 5;
		}
		vec2_normalize(&(player->move), 0.0085);
		play_target_update(&(player->fov), FOV_BASE, 0.015, 0.03);
	}
	else if (ps[0] == 'R')
	{
		vec2_normalize(&(player->move), 0.0085 * 1.5);
		if (ps[1] == '_')
		{
			player->pos.z = sin(player->time / (double)25.0) * 50;
			player->time += 7;
		}
		play_target_update(&(player->fov), FOV_BASE * 1.1, 0.015, 0.03);
	}
}

void	play_motion(t_player *player)
{
	play_action_jump(player, player->state, RUN);
	play_action_crouch(player, "W__", RUN);
	player->motion.x += player->move.x * player->dir.x - player->move.y * player->dir.y;
	player->motion.y += player->move.y * player->dir.x + player->move.x * player->dir.y;
	player->motion.x = player->motion.x * 0.85;
	player->motion.y = player->motion.y * 0.85;
	player->pos.x += player->motion.x;
	player->pos.y += player->motion.y;
	player->euler_dir.y += player->motion_dir.y;
}

void	play_update(t_data *data)
{
	play_transition_by_key_event(&(data->player));
	play_dir_update(data);
	play_dir_plane_set(&(data->player));
	play_movement_update(&(data->player));
	play_action_movement(&(data->player));
	printf("ps:%s\n", data->player.state);
	play_motion(&(data->player));
}
