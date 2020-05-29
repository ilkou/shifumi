/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <oouklich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 00:44:07 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 13:21:06 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mx_sdl.h>

int						mx_volume(int id, int volume)
{
	t_mx_playlist			*plst;

	plst = mx_get_playlist();
	if (plst->length > id && id > -1)
	{
		if (plst->list[id].type == MX_EFFECT)
			Mix_VolumeChunk(plst->list[id].sound.e, volume);
		else
			Mix_VolumeMusic(volume);
	}
	else
		fprintf(stderr, "MX_ERROR: sound not found\n");
	if (volume < 0 || volume > MIX_MAX_VOLUME)
		return (mx_error(MX_ERROR_volume_code, MX_ERROR_volume));
	return (1);
}

void					mx_play(int id, int loops)
{
	t_mx_playlist			*plst;

	plst = mx_get_playlist();
	if (plst->length > id && id > -1)
	{
		if (plst->list[id].type == MX_EFFECT)
		{
			//Mix_HaltChannel(-1);
			Mix_PlayChannel(-1, plst->list[id].sound.e, loops);
		}
		else
			Mix_PlayMusic(plst->list[id].sound.m, loops);
	}
	else
		fprintf(stderr, "MX_ERROR: sound not found\n");

}

void					mx_stop(int id)
{
	t_mx_playlist			*plst;

	plst = mx_get_playlist();
	if (plst->length > id && id > -1)
	{
		if (plst->list[id].type == MX_EFFECT)
			Mix_HaltChannel(-1);
		else
			Mix_HaltMusic();
	}
	else
		fprintf(stderr, "MX_ERROR: sound not found\n");
}

void					mx_pause_music() {
	Mix_PauseMusic();
}

void					mx_resume_music() {
	Mix_ResumeMusic();
}
