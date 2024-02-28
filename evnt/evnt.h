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
int		evnt_mousepress(int keycode, int x, int y, t_data *data);
int		evnt_mouserelease(int keycode, int x, int y, t_player *player);
int		evnt_leave(int keycode, int tmp);
void	evnt_keybinds_set(int *kb, int keycode, long time, char press);
void	evnt_x_set(int *kb, char press, int t_kb, int num);
void	evnt_toggle_mouse_cursor(int *kb);
void	evnt_forward_set(int *kb, long long time, char press);
void	evnt_attack_set(int *kb, char press);
void	evnt_reload_set(int *kb, char press);
void	evnt_x_set(int *kb, char press, int t_kb, int num);

#endif
