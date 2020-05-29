/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <oouklich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:32:29 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/14 04:57:03 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mx_sdl.h>

/*
 * Initialize the mixer API.
 *	SDL must be initialized with SDL_INIT_AUDIO before this call.
 *	frequency
 *Output sampling frequency in samples per second (Hz).
 *we use MIX_DEFAULT_FREQUENCY(22050) since that is a good value for most games.
 *quality of sound in general :)
 *	format
 *Output sample format.
 *	channels
 *Number of sound channels in output.
 *Set to 2 for stereo, 1 for mono. This has nothing to do with mixing channels.
 *	chunksize
 *Bytes used per output sample.
 */

int						mx_init(void)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
				MIX_DEFAULT_CHANNELS, 1024) < 0)
		return (mx_error(MX_ERROR_init_code, MX_ERROR_init));
	return (1);
}

t_mx_playlist					*mx_get_playlist(void)
{
	static t_mx_playlist	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(struct s_mx_playlist));
		lst->length = 0;
		lst->list = malloc(sizeof(struct s_mx_sound));
	}
	return (lst);
}

int						mx_push_music(const char *path, enum e_mx_type mx)
{
	t_mx_playlist			*plst;
	union u_mx_sound		new;

	plst = mx_get_playlist();
	if (mx == MX_MUSIC)
		new.m = Mix_LoadMUS(path);
	else if (mx == MX_EFFECT)
		new.e = Mix_LoadWAV(path);
	else
		return (mx_error(MX_ERROR_wrong_type_code, MX_ERROR_wrong_type));
	if ((mx == MX_MUSIC && new.m == NULL) || (mx == MX_EFFECT && new.e == NULL))
		return (mx_error(MX_ERROR_load_fail_code, MX_ERROR_load_fail));
	plst->list = mx_realloc((void*)&plst->list,
			plst->length * sizeof(struct s_mx_sound),
			(plst->length + 1) * sizeof(struct s_mx_sound));
	plst->list[plst->length].sound = new;
	plst->list[plst->length].type = mx;
	plst->length++;
	return (plst->length - 1);
}

int						mx_quit(void)
{
	t_mx_playlist			*plst;
	static int			i = -1;

	plst = mx_get_playlist();
	if (plst->list)
	{
		while (++i < plst->length)
		{
			if (plst->list[i].type == MX_EFFECT)
				Mix_FreeChunk(plst->list[i].sound.e);
			else
				Mix_FreeMusic(plst->list[i].sound.m);
		}
		free(plst->list);
	}
	Mix_CloseAudio();
	return (1);
}
/*
 * Pour arrêter la musique, utilisez la fonction Mix_PauseMusic(); .
 * Et pour la reprendre au même endroit, Mix_ResumeMusic(); .
 * 
 * Pour revenir au début, Mix_RewindMusic(); (ne marche pas avec les .mid,
 * car c'est un format un peu à part).
 *
 * Pour régler le volume : Mix_VolumeMusic(); .
 * Pour lui, il y a un paramètre : le volume !
 * Il va de 0 à 128 (ou MIX_MAX_VOLUME , un define qui est le son maximum).
 * On peut donc mettre le volume à moitié :
 *
 * Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
 *
 * Pour arrêter la musique, utilisez la fonction Mix_HaltMusic(); .
 *
 * Pour savoir si la musique est en pause,
 * on vérifie si Mix_PausedMusic() est égal à 1.
 *
 * Pour savoir si la musique est en train de jouer, on vérifie
 * si Mix_PlayingMusic() est égal à 1.
*/
