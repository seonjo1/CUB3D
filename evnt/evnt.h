/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evnt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:11:06 by michang           #+#    #+#             */
/*   Updated: 2024/02/08 14:11:06 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVNT_H
# define EVNT_H
# include "../cub3d.h"

int		evnt_keypress(int keycode, t_player *player);
int		evnt_keyrelease(int keycode, t_player *player);
int		evnt_mousepress(int keycode, int x, int y, t_player *player);
int		evnt_mouserelease(int keycode, int x, int y, t_player *player);
int		evnt_leave(int keycode, int tmp);
void	evnt_keybinds_set(int *kb, int keycode, long long time, char press);
void	evnt_shift_set(int *kb, char press);

#endif
