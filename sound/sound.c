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

void	sound_init(t_sounds *sounds)
{
	int	done;

	done = 1;
	done &= sound_load(sounds->attack, "./res/sound/attack.wav");
	done &= sound_load(sounds->flash[0], "./res/sound/flash_0.wav");
	done &= sound_load(sounds->flash[1], "./res/sound/flash_1.wav");
	done &= sound_load(sounds->flash[2], "./res/sound/flash_0.wav");
	done &= sound_load(sounds->gun, "./res/sound/gun.wav");
	done &= sound_load(sounds->recall, "./res/sound/recall.wav");
	done &= sound_load(sounds->reload, "./res/sound/reload.wav");
	if (!done)
		exit(1);
}

void	sound_clear(t_sounds *sounds)
{
	if (sounds->attack)
		BASS_StreamFree(sounds->attack);
	if (sounds->flash[0])
		BASS_StreamFree(sounds->flash[0]);
	if (sounds->flash[1])
		BASS_StreamFree(sounds->flash[0]);
	if (sounds->flash[2])
		BASS_StreamFree(sounds->flash[2]);
	if (sounds->gun)
		BASS_StreamFree(sounds->gun);
	if (sounds->recall)
		BASS_StreamFree(sounds->recall);
	if (sounds->reload)
		BASS_StreamFree(sounds->reload);
	BASS_Free();
}

char	sound_load(uint32_t *s, char *path)
{
	static char	loaded;

	loaded |= BASS_Init(-1, 48000, 0, 0, 0);
	if (!loaded || *s)
		return (FALSE);
	*s = BASS_StreamCreateFile(FALSE, path, 0, 0, 0);
	return (TRUE);
}

void	sound_play_alt(uint32_t s, char play, char loop)
{
	if (!s)
		return ;
	if (loop)
		BASS_ChannelFlags(s,
			BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(s, 0);
	else
		BASS_ChannelPause(s);
}

void	sound_play(uint32_t s)
{
	if (!s)
		return ;
	BASS_ChannelStop(s);
	BASS_ChannelSetPosition(s, 0, 0);
	BASS_ChannelPlay(s, 0);
}
