/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:39:46 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:01:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAND_BONUS_H
# define HAND_BONUS_H
# include "../cub3d_bonus.h"

void	hand_init_xpm_imgs(t_data *data);
void	*hand_update(t_data *data);
void	*hand_action_shot(void **arr, t_data *data, int *magazine);
int		hand_stop_shot(char set, unsigned int c);
void	*hand_action_walk(t_player *player, void **arr, int delay);
void	*hand_action_recall(void **arr, t_player *player, int *magazine);
void	*hand_action_flash(void **arr, t_player *player);
void	*hand_action_attack(void **arr, t_player *player);
void	*hand_action_reload(void **arr, t_player *player, int *magazine);
int		hand_reset_reload(int *kb, int *rf, char set, unsigned int c);
#endif
