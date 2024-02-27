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
		mlx_mouse_move(data->mlx_win, (WIN_WIDTH >> 1), (WIN_HEIGHT >> 1));
		delay++;
		if (delay >= 5)
		{
			if (mouse_pos.x - (WIN_WIDTH >> 1) != 0)
				data->player.motion_dir.y = (mouse_pos.x - (WIN_WIDTH >> 1)) / 314.0;
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
	if (!(kb & (1 << KB_ROTATE_UP)) && kb & (1 << KB_ROTATE_DOWN))
		data->player.motion_dir.x = 8;
	else if (!(kb & (1 << KB_ROTATE_DOWN)) && kb & (1 << KB_ROTATE_UP))
		data->player.motion_dir.x = -8;
	else
		data->player.motion_dir.x *= 0.795;
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

void	play_move_update(t_player *player)
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
		else if (kb & (1 << KB_FLASH) && !(kb & (1 << KB_ATTACK)))
			play_action_flash(player, "W_F", ENTER);
		else if (kb & (1 << KB_RECALL) && !(kb & (1 << KB_ATTACK)))
			play_action_recall(player, &(player->recall), ENTER);
	}
	else if (!ft_strncmp(ps, "R__", 4))
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

char	play_check_collision(t_map *map, t_vec2 next_pos)
{
	double	rad;
	double	checkX;
	double	checkY;
	double	angle;

	angle = 0;
	while (angle < 360)
	{
		rad = angle * M_PI / 180.0;
		checkX = next_pos.x + 0.02 * cos(rad);
		checkY = next_pos.y + 0.02 * sin(rad);
		if (!utils_is_in_map(checkX, checkY, map))
			return (1);
		if (map->data[(int)checkY][(int)checkX] == '1')
			return (1);
		angle += 5;
	}
	return (0);
}

void	play_motion(t_data *data, t_player *player)
{
	t_vec2	next_pos;

	play_action_movement(player);
	play_action_jump(player, player->state, RUN);
	play_action_crouch(player, "W__", RUN);
	play_action_flash(player, "___", RUN);
	if (player->state[0] != '_')
	{
		player->motion.x += player->move.x * player->dir.x - player->move.y * player->dir.y;
		player->motion.y += player->move.y * player->dir.x + player->move.x * player->dir.y;
		player->motion.x = player->motion.x * 0.85;
		player->motion.y = player->motion.y * 0.85;
		next_pos.x = player->pos.x + player->motion.x;
		next_pos.y = player->pos.y + player->motion.y;
		if (!play_check_collision(&(data->map), vec2_creat(next_pos.x, player->pos.y)))
			player->pos.x = next_pos.x;
		if (!play_check_collision(&(data->map), vec2_creat(player->pos.x, next_pos.y)))
			player->pos.y = next_pos.y;
		player->euler_dir.y += player->motion_dir.y;
		player->euler_dir.x += player->motion_dir.x;
	}
	play_action_recall(player, &(player->recall), RUN);
}

void	play_update(t_data *data)
{
	play_transition_by_key_event(&(data->player));
	play_dir_update(data);
	play_dir_plane_set(&(data->player));
	play_move_update(&(data->player));
	// printf("ps:%s\n", data->player.state);
	printf("pitch:%f\n", data->player.euler_dir.x);
	play_motion(data, &(data->player));
}
