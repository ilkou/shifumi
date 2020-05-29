/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:01:11 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 13:25:27 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

int	inButton(t_component *button, int x, int y) {
	//printf("%d %d %d %d\n", button->x, button->y, button->img->w, button->img->h);
	if (x > button->x && y > button->y
			&& x < button->img->w + button->x && y < button->img->h + button->y)
		return (1);
	return (0);
}

void	handleFrameStart(int x,int y, t_game *g) {
	if (!g->is_ready && inButton(&g->scene.new_game, x, y))
		printf("\n => En attente d'un adversaire... ");
	else if (g->is_ready && inButton(&g->scene.new_game, x, y)) {
		mx_play(g->click_effect, 0);
		g->frame = FRAME_PLAY;
	}
	else if (inButton(&g->scene.quit, x, y)) {
		mx_play(g->click_effect, 0);
		closeGame(g);
	}
	fflush(stdout);
	displayFrame(g);
}

void	handleFramePlay(int x,int y, t_game *g) {
	if (g->is_end == 1)
		return ;
	if (g->is_selecting == S_NONE && inButton(&g->scene.my_rock[ON_SELECT], x, y)) {
		mx_play(g->click_effect, 0);
		write(g->fd[ECRITURE], "rock", 4);
		displayComponent(g, &g->scene.my_rock[ON_SELECT]);
		g->is_selecting = S_ROCK;
	}
	if (g->is_selecting == S_NONE && inButton(&g->scene.my_paper[ON_SELECT], x, y)) {
		mx_play(g->click_effect, 0);
		write(g->fd[ECRITURE], "paper", 5);
		displayComponent(g, &g->scene.my_paper[ON_SELECT]);
		g->is_selecting = S_PAPER;
	}
	if (g->is_selecting == S_NONE && inButton(&g->scene.my_scissors[ON_SELECT], x, y)) {
		mx_play(g->click_effect, 0);
		write(g->fd[ECRITURE], "scissors", 8);
		displayComponent(g, &g->scene.my_scissors[ON_SELECT]);
		g->is_selecting = S_SCISSORS;
	}
}

int	mousePos(int button,int x,int y, t_game *g) {
	if (g->frame == FRAME_START)
		handleFrameStart(x, y, g);
	else if (g->frame == FRAME_PLAY)
		handleFramePlay(x, y, g);
	//printf("Mouse position, button %d at %dx%d.\n", button, x, y);
	return (0);
}

int	mouseMove(int x,int y, t_game *g) {
	//printf("Mouse moving, at %dx%d.\n", x, y);
	return (0);
}

int	keyHandler(int key, t_game *g) {

	//printf("Key in : %d\n",key);
	if (key == K_ESC)
		closeGame(g);
	if (key == K_P)
		mx_resume_music();
	if (key == K_S)
		mx_pause_music();
	if (key == K_R)
		reset(g);
	return (0);
}
