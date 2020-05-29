/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:12:43 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 13:13:00 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	initScore(t_game *g) {
	g->is_end = 0;
	g->my_score = 0;
	g->adv_score = 0;
}

void	initGraphics(t_game *g) {
	printf(" => initialisation d'interface graphique... ");
	if (!(g->mlx = mlx_init()))
		exitStatus(" KO \n", NULL);
	if (!(g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, GAME_TITLE)))
		exitStatus(" KO \n", NULL);
	load_components(g);
	g->frame = FRAME_START;
	g->is_selecting = S_NONE;
	g->is_ready = 0;
	printf("OK\n");
}

void	initNetworking(t_game *g) {
	struct sockaddr_in *addressin;
	struct addrinfo *first_info;
	struct addrinfo hints;
	bzero(&hints, sizeof(struct addrinfo));
 	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((g->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exitStatus(" => établir la connexion avec le serveur...  KO \n", "socket ");
	if (getaddrinfo(g->server_address, PORT_STR, &hints, &first_info) != 0)
		exitStatus(" => établir la connexion avec le serveur... KO \nserver unreachable\n", NULL);
	if (first_info == NULL)
		exitStatus(" => établir la connexion avec le serveur... KO \nserver unreachable\n", NULL);
	addressin=(struct sockaddr_in *)first_info->ai_addr;
	if (connect(g->sock,(struct sockaddr *)addressin,
				(socklen_t) sizeof(struct sockaddr_in)) < 0)
		exitStatus(" => établir la connexion avec le serveur... KO \n", "connect ");
	printf(" => établir la connexion avec le serveur... OK \n");
	fflush(stdout);
	pipe(g->fd);
	socketManager(g);
	/*struct sockaddr_in sin = { 0 };
	struct hostent *hostinfo;
	if ((g->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exitStatus(" KO \n", "socket ");
	if (!(hostinfo = gethostbyname(g->server_address)))
		exitStatus(" KO \nserver unreachable\n", NULL);
	sin.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	if (connect(g->sock, (struct sockaddr *) &sin, sizeof(struct sockaddr)) < 0)
		exitStatus(" KO \n", "connect ");
	*/
}

void	initSounds(t_game *g) {
	if (SDL_Init(SDL_INIT_AUDIO) < 0 || !mx_init()) {
		mx_error(MX_ERROR_init_code, MX_ERROR_init);
		exit(EXIT_FAILURE);
	}
	printf(" => initialisation du lecteur musical... OK \n");
	printf(" les touches P/S pour Activer/Arrêter la musique en arrière-plan\n");
	g->bg_music = mx_push_music("sounds/wish.mp3", MX_MUSIC);
	g->click_effect = mx_push_music("sounds/button.wav", MX_EFFECT);
	mx_play(g->bg_music, -1);
}
