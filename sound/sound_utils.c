/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:28 by michang           #+#    #+#             */
/*   Updated: 2024/02/28 18:30:29 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sound.h"

int	sound_play_loop(unsigned int sample)
{
	unsigned int	channel;

	channel = BASS_SampleGetChannel(sample, FALSE);
	BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(channel, FALSE);
	return (channel);
}

int	sound_play(unsigned int sample)
{
	unsigned int	channel;

	channel = BASS_SampleGetChannel(sample, FALSE);
	BASS_ChannelPlay(channel, FALSE);
	return (channel);
}

void	sound_stop(unsigned int channel)
{
	BASS_ChannelStop(channel);
}

void	sound_pause(unsigned int channel)
{
	BASS_ChannelPause(channel);
}

void	sound_resume(unsigned int channel)
{
	BASS_ChannelPlay(channel, FALSE);
}
