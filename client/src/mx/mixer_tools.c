/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <oouklich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:58:34 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/14 04:57:24 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mx_sdl.h>

const char	*g_mx_error_codes[] =
{
	"MX ERROR: SDL_mixer could not initialize! ",
	"MX ERROR: Music could not be added! wrong type of music",
	"MX ERROR: Music could not be loaded! ",
	"MX_ERROR: Wrong volume value!"
};

int			mx_error(enum e_mx_error_codes code, enum e_mx_error_returns ret)
{
	fprintf(stderr, "%s", g_mx_error_codes[code]);
	fprintf(stderr, "%s", Mix_GetError());
	return (ret);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bdup;

	bdup = (unsigned char *)b;
	while (len > 0)
	{
		*bdup = c;
		bdup++;
		len--;
	}
	return (b);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dstdup;
	char			*srcdup;
	size_t			i;

	i = 0;
	dstdup = (char *)dst;
	srcdup = (char *)src;
	while (i < n && src != dst)
	{
		dstdup[i] = srcdup[i];
		i++;
	}
	return (dst);
}

void		*mx_realloc(void **ptr, size_t old, size_t len)
{
	void			*real;

	real = malloc(len);
	ft_memset(real, 0, len);
	if (real)
		ft_memcpy(real, *ptr, old);
	if (*ptr)
		free(*ptr);
	return (real);
}
