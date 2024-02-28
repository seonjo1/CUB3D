/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:07:44 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:01:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_BONUS_H
# define SOUND_BONUS_H
# include "../cub3d_bonus.h"

t_sounds	*sound_init(t_sounds *sounds);
void		sound_clear(t_sounds *sounds);
char		sound_load(unsigned int *s, char *path);
int			sound_play_loop(unsigned int sample);
int			sound_play(unsigned int s);
void		sound_stop(unsigned int channel);
void		sound_pause(unsigned int channel);
void		sound_resume(unsigned int channel);

#endif
