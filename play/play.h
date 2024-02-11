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
void	play_action_movement(t_player *player);
void	play_action_jump(t_player *player, char *transition, char enter);
void	play_action_crouch(t_player *player, char *transition, char enter);
void	play_action_flash(t_player *player, char *transition, char enter);
int		play_target_update(double *target, double goal, double delta, double offset);

#endif
