/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:07:44 by michang           #+#    #+#             */
/*   Updated: 2024/02/25 16:07:45 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H
# include "../cub3d.h"

void	sound_init(t_sounds *sounds);
void	sound_clear(t_sounds *sounds);
char	sound_load(unsigned int *s, char *path);
void	sound_play_alt(unsigned int s, char play, char loop);
void	sound_play(unsigned int s);

#endif
