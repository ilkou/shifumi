/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 03:39:29 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 03:48:44 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

# define MAX_SCORE 5

void	displayComponent(t_game *g, t_component *component) {
	mlx_put_image_to_window(g->mlx, g->win, component->img->img,
				component->x, component->y);
}

void	displayResult(t_game *g, int rslt, int adv) {
	if (adv == S_ROCK)
		displayComponent(g, &g->scene.adv_rock[rslt == R_WIN ? ON_LOSE : (rslt == R_LOSE ? ON_WIN : ON_SELECT)]);
	else if (adv == S_PAPER)
		displayComponent(g, &g->scene.adv_paper[rslt == R_WIN ? ON_LOSE : (rslt == R_LOSE ? ON_WIN : ON_SELECT)]);
	else if (adv == S_SCISSORS)
		displayComponent(g, &g->scene.adv_scissors[rslt == R_WIN ? ON_LOSE : (rslt == R_LOSE ? ON_WIN : ON_SELECT)]);
	if (g->is_selecting == S_ROCK)
		displayComponent(g, &g->scene.my_rock[rslt == R_WIN ? ON_WIN : (rslt == R_LOSE ? ON_LOSE : ON_SELECT)]);
	else if (g->is_selecting == S_PAPER)
		displayComponent(g, &g->scene.my_paper[rslt == R_WIN ? ON_WIN : (rslt == R_LOSE ? ON_LOSE : ON_SELECT)]);
	else if (g->is_selecting == S_SCISSORS)
		displayComponent(g, &g->scene.my_scissors[rslt == R_WIN ? ON_WIN : (rslt == R_LOSE ? ON_LOSE : ON_SELECT)]);
	sleep(2);
	g->is_selecting = S_NONE;
	displayFrame(g);
	if (g->my_score == MAX_SCORE)
		mlx_string_put(g->mlx, g->win, 450, 40, 0x00FF00, "Tu as gagne !");
	else if (g->adv_score == MAX_SCORE)
		mlx_string_put(g->mlx, g->win, 450, 40, 0xFFFF00, "Tu as perdu");
	if (g->my_score == MAX_SCORE || g->adv_score == MAX_SCORE) {
		mlx_string_put(g->mlx, g->win, 450, 55, 0xFFFFFF, "Cliquez sur (R) pour rejouer");
		g->is_end = 1;
	}
}

void	displayStart(t_game *g) {
	t_scene *scene = &g->scene;

	displayComponent(g, &scene->bg);
	displayComponent(g, &scene->logo);
	displayComponent(g, &scene->rights);
	displayComponent(g, &scene->new_game);
	displayComponent(g, &scene->quit);
}

void	displayPlay(t_game *g) {
	t_scene *scene = &g->scene;

	displayComponent(g, &scene->my_empty);
	displayComponent(g, &scene->adv_empty);
	mlx_string_put(g->mlx, g->win, 100, 140, 0xFFFFFF, ft_strjoin("Moi: ", ft_itoa(g->my_score), 1));
	mlx_string_put(g->mlx, g->win, 850, 440, 0xFFFFFF, ft_strjoin("Adversaire: ", ft_itoa(g->adv_score), 1));
}

void	displayFrame(t_game *g) {
	mlx_clear_window(g->mlx, g->win);
	if (g->frame == FRAME_START)
		displayStart(g);
	if (g->frame == FRAME_PLAY)
		displayPlay(g);
}
