/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:00:19 by michang           #+#    #+#             */
/*   Updated: 2024/02/07 18:00:20 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAY_H
# define PLAY_H
# include "../cub3d.h"

void	play_update(t_data *data);
void	play_action_walk_run(t_player *player);
void	play_action_jump(t_player *player, char *transition, char enter);
void	play_action_crouch(t_player *player, char *transition, char enter);
int		play_target_update(double *target, double goal, double d, double o);
void	play_motion_dir_set(t_data *data);
void	play_motion_dir_get_mouse(t_data *data);
void	play_dir_plane_set(t_player *player);
void	play_state_transition(t_player *player);

#endif
