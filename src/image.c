/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:27:34 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/27 17:28:52 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

t_image	*new_image(void *mlx, char *filename) {
	t_image *image;

	if (!(image = (t_image*)malloc(sizeof(t_image))))
		return (NULL);
	if (filename != NULL)
		image->img = mlx_xpm_file_to_image(mlx, filename, &image->w, &image->h);
	else
		image->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!image->img) {
		if (filename != NULL)
			fprintf(stderr, "failed to load %s\n", filename);
		return (NULL);
	}
	return (image);
}
