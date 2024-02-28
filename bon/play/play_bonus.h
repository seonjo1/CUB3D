/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:00:19 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:01:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAY_BONUS_H
# define PLAY_BONUS_H
# include "../cub3d_bonus.h"

void	play_update(t_data *data);
void	play_action_walk_run(t_player *player);
void	play_action_jump(t_player *player, char *transition, char enter);
void	play_action_crouch(t_player *player, char *transition, char enter);
void	play_action_flash(t_player *player, char *transition, char enter);
void	play_action_recall(t_player *player, t_recall *re, char enter);
int		play_target_update(double *target, double goal, double d, double o);
void	play_motion_dir_set(t_data *data);
void	play_motion_dir_get_mouse(t_data *data);
void	play_dir_plane_set(t_player *player);
void	play_state_transition(t_player *player);

#endif
