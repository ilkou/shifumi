/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:14:13 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 14:14:55 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

//Shoutout to eljadi

void	closesocket(int *sock) {
	close(*sock);
	*sock = -1;
}

int	closeGame(t_game *g) {
	write(g->fd[ECRITURE], "exit", 4); /* exit socket thread */
	close(g->fd[ECRITURE]);
	closesocket(&g->sock);
#ifdef __APPLE__
	mx_quit();
#endif
	mlx_destroy_window(g->mlx, g->win);
	printf("See you SOON :)\n");
	exit(EXIT_SUCCESS);
}

void	exitStatus(const char *err, char *perr) {
	fprintf(stderr, "%s", err);
	if (perr)
		perror(perr);
	exit(EXIT_FAILURE);
}
