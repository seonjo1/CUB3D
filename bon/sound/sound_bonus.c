/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:07:50 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 22:04:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound_bonus.h"

char	sound_load(unsigned int *sample, char *path)
{
	static char	loaded;

	loaded |= BASS_Init(-1, 48000, 0, 0, 0);
	if (!loaded || *sample)
		return (FALSE);
	*sample = BASS_SampleLoad(FALSE, path, 0, 0, 3, 0);
	if (!(*sample))
		return (0);
	return (1);
}

t_sounds	*sound_init(t_sounds *s_res)
{
	int	done;

	done = 1;
	done &= sound_load(&(s_res->attack), "./res/sound/attack.wav");
	done &= sound_load(&(s_res->flash[0]), "./res/sound/flash_0.wav");
	done &= sound_load(&(s_res->flash[1]), "./res/sound/flash_1.wav");
	done &= sound_load(&(s_res->flash[2]), "./res/sound/flash_2.wav");
	done &= sound_load(&(s_res->gun), "./res/sound/gun.wav");
	done &= sound_load(&(s_res->recall), "./res/sound/recall.wav");
	done &= sound_load(&(s_res->reload), "./res/sound/reload.wav");
	done &= sound_load(&(s_res->walk), "./res/sound/stone.wav");
	done &= sound_load(&(s_res->run), "./res/sound/run.wav");
	done &= sound_load(&(s_res->landing), "./res/sound/landing.wav");
	done &= sound_load(&(s_res->bgm), "./res/sound/bgm.mp3");
	if (!done)
		exit(1);
	sound_play_loop(s_res->bgm);
	return (s_res);
}
