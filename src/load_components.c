/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 00:32:21 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/30 10:14:28 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	load_components(t_game *g) {
	t_scene *scene = &g->scene;

	scene->bg = new_component(new_image(g->mlx, "img/bg.xpm"), 0, 0);
	scene->bg2 = new_component(new_image(g->mlx, "img/bg2.xpm"), 0, 0);
	scene->logo = new_component(new_image(g->mlx, "img/logo.xpm"), 405, 60);
	scene->rights = new_component(new_image(g->mlx, "img/rights.xpm"), 385, 633);
	scene->random = new_component(new_image(g->mlx, "img/random.xpm"), 20, 403);
	scene->solo = new_component(new_image(g->mlx, "img/solo.xpm"), 20, 480);
	scene->quit = new_component(new_image(g->mlx, "img/quit.xpm"), 20, 557);
	scene->my_empty = new_component(new_image(g->mlx, "img/empty2.xpm"), 240, 77);
	scene->adv_empty = new_component(new_image(g->mlx, "img/empty3.xpm"), 240, 350);
	scene->my_rock[ON_SELECT] = new_component(new_image(g->mlx, "img/pi-b.xpm"), 614, 80);
	scene->my_rock[ON_WIN] = new_component(new_image(g->mlx, "img/pi-v.xpm"), 614, 80);
	scene->my_rock[ON_LOSE] = new_component(new_image(g->mlx, "img/pi-r.xpm"), 614, 80);
	scene->my_paper[ON_SELECT] = new_component(new_image(g->mlx, "img/pa-b.xpm"), 243, 80);
	scene->my_paper[ON_WIN] = new_component(new_image(g->mlx, "img/pa-v.xpm"), 243, 80);
	scene->my_paper[ON_LOSE] = new_component(new_image(g->mlx, "img/pa-r.xpm"), 243, 80);
	scene->my_scissors[ON_SELECT] = new_component(new_image(g->mlx, "img/ci-b.xpm"), 426, 80);
	scene->my_scissors[ON_WIN] = new_component(new_image(g->mlx, "img/ci-v.xpm"), 426, 80);
	scene->my_scissors[ON_LOSE] = new_component(new_image(g->mlx, "img/ci-r.xpm"), 426, 80);
	scene->adv_rock[ON_SELECT] = new_component(new_image(g->mlx, "img/pi-b.xpm"), 614, 353);
	scene->adv_rock[ON_WIN] = new_component(new_image(g->mlx, "img/pi-v.xpm"), 614, 353);
	scene->adv_rock[ON_LOSE] = new_component(new_image(g->mlx, "img/pi-r.xpm"), 614, 353);
	scene->adv_paper[ON_SELECT] = new_component(new_image(g->mlx, "img/pa-b.xpm"), 243, 353);
	scene->adv_paper[ON_WIN] = new_component(new_image(g->mlx, "img/pa-v.xpm"), 243, 353);
	scene->adv_paper[ON_LOSE] = new_component(new_image(g->mlx, "img/pa-r.xpm"), 243, 353);
	scene->adv_scissors[ON_SELECT] = new_component(new_image(g->mlx, "img/ci-b.xpm"), 426, 353);
	scene->adv_scissors[ON_WIN] = new_component(new_image(g->mlx, "img/ci-v.xpm"), 426, 353);
	scene->adv_scissors[ON_LOSE] = new_component(new_image(g->mlx, "img/ci-r.xpm"), 426, 353);
}
