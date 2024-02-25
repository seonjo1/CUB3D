/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:07:50 by michang           #+#    #+#             */
/*   Updated: 2024/02/25 16:07:51 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"

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
	if (!done)
		exit(1);
	return (s_res);
}

void	sound_clear(t_sounds *s_res)
{
	if (s_res->attack)
		BASS_StreamFree(s_res->attack);
	if (s_res->flash[0])
		BASS_StreamFree(s_res->flash[0]);
	if (s_res->flash[1])
		BASS_StreamFree(s_res->flash[1]);
	if (s_res->flash[2])
		BASS_StreamFree(s_res->flash[2]);
	if (s_res->gun)
		BASS_StreamFree(s_res->gun);
	if (s_res->recall)
		BASS_StreamFree(s_res->recall);
	if (s_res->reload)
		BASS_StreamFree(s_res->reload);
	BASS_Free();
}

char sound_load(unsigned int *sample, char *path) {
    static char loaded;

    loaded |= BASS_Init(-1, 48000, 0, 0, 0);
    if (!loaded || *sample)
        return FALSE;
    *sample = BASS_SampleLoad(FALSE, path, 0, 0, 3, 0);
    return (*sample != 0);
}

// void	sound_play_alt(unsigned int sound, char play, char loop)
// {
// 	if (!sound)
// 		return ;
// 	if (loop)
// 		BASS_ChannelFlags(sound, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
// 	if (play)
// 		BASS_ChannelPlay(sound, 0);
// 	else
// 		BASS_ChannelPause(sound);
// }

void sound_play(unsigned int sample) {
	unsigned int channel;
	
	channel = BASS_SampleGetChannel(sample, FALSE);
	BASS_ChannelPlay(channel, FALSE);
}
