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

char	play_check_collision(t_map *map, t_vec2 n_pos)
{
	double	rad;
	double	check_x;
	double	check_y;
	double	angle;

	angle = 0;
	while (angle < 360)
	{
		rad = angle * M_PI / 180.0;
		check_x = n_pos.x + 0.04 * cos(rad);
		check_y = n_pos.y + 0.04 * sin(rad);
		if (!utils_is_in_map(check_x, check_y, map))
			return (1);
		if (map->data[(int)check_y][(int)check_x] == '1')
			return (1);
		angle += 5;
	}
	return (0);
}

void	play_pos_update(t_data *data, t_player *player)
{
	t_vec2	n_pos;

	player->euler_dir.y += player->motion_dir.y;
	player->euler_dir.x = fmin(540, \
		player->euler_dir.x + player->motion_dir.x);
	player->euler_dir.x = fmax(-700, player->euler_dir.x);
	if (data->player.state[0] == '_')
		return ;
	player->motion.x += player->move.x * player->dir.x \
		- player->move.y * player->dir.y;
	player->motion.y += player->move.y * player->dir.x \
		+ player->move.x * player->dir.y;
	player->motion.x = player->motion.x * 0.85;
	player->motion.y = player->motion.y * 0.85;
	n_pos.x = player->pos.x + player->motion.x;
	n_pos.y = player->pos.y + player->motion.y;
	if (!play_check_collision(&(data->map), vec2_creat(n_pos.x, player->pos.y)))
		player->pos.x = n_pos.x;
	if (!play_check_collision(&(data->map), vec2_creat(player->pos.x, n_pos.y)))
		player->pos.y = n_pos.y;
}

void	play_update(t_data *data)
{
	play_state_transition(&(data->player));
	play_motion_dir_get_mouse(data);
	play_motion_dir_set(data);
	play_move_update(&(data->player));
	play_action_walk_run(&(data->player));
	play_action_jump(&(data->player), data->player.state, RUN);
	play_action_crouch(&(data->player), "W__", RUN);
	play_pos_update(data, &(data->player));
	play_dir_plane_set(&(data->player));
}
