/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:29:37 by oouklich          #+#    #+#             */
/*   Updated: 2020/05/29 01:01:06 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <game.h>

t_component new_component(t_image *image, int x, int y) {
	t_component	component;

	if (!image) {
		fprintf(stderr, "failed to set image for component\n");
		exit(EXIT_FAILURE);
	}
	component.img = image;
	component.x = x;
	component.y = y;
	return (component);
}

t_components *add_component(t_components *list, t_component *element) {
	t_components *newList = list;
	t_components *tmp = list;

	if (!element)
		return (NULL);
	if (!newList) {
		newList = (t_components*)malloc(sizeof(struct s_components));
		newList->component = element;
		newList->next = NULL;
		return (newList);
	}
	while (list) {
		tmp = list;
		list = list->next;
	}
	tmp->next = (t_components*)malloc(sizeof(struct s_components));
	tmp->next->component = element;
	tmp->next->next = NULL;
	return (newList);
}
